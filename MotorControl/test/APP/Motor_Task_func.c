#include "stm32g4xx.h"                  // Device header
#include "string.h"
#include "Motor_Task_func.h"
#include "adc.h"
#include "tim.h"
#include "opamp.h"
#include "dac.h"
#include "gpio.h"
#include "comp.h"
#include <math.h>
#include "Motor_Comm_func.h"
#include "Motor_Struct.h"
#include "usart.h"
#include "doubleloop.h"
void FOC_LowFrequencyTask(void)//systemtick 1KHZ执行一次
{
	static uint8_t MotorState=0;//定义电机状态的局部变量
	Motor_Load_UART_Tx_Buff();//串口通信传送定义数据至VOFA上位机
	Motor_UART_Rx_Data_Decoding();//串口通信接收上位机指令并解码
	if(MotorState!=m_app.UART_Cmd.State)//只有在电机当前状态与上位机指令不同时电机才会更改状态
	{
		if(m_app.UART_Cmd.State==START)
		{
			Motor_StartTSK();
		}
		else
			{
				Motor_StopTSK();
			}
	MotorState=m_app.UART_Cmd.State;//只有电机状态改变才将上位机指令赋值给电机状态变量
	}
	if(__HAL_TIM_GET_FLAG(&htim1,TIM_FLAG_BREAK)==1)
	{
		m_app.UART_Cmd.State=FAULT;
		__HAL_TIM_CLEAR_FLAG(&htim1,TIM_FLAG_BREAK);
	}//过流保护标志位查看电机是否故障
	m_app.FOCVars.VBus=Get_Vbus();
	rtU.Udc=m_app.FOCVars.VBus;
	rtU.SpeedRef=m_app.UART_Cmd.SpdRef;
	LED_LowFreqToggle();
	LED_MediumFreqToggle();
}

void FOC_HighFrequencyTask(void)
{

	static uint8_t cnt=0;
	static uint8_t OffsetCalibration=0;
	static uint16_t IaU16,IbU16,IcU16;
	if(OffsetCalibration==0)
	{
		m_app.FOCVars.IaOffset += hadc1.Instance->JDR1;
		m_app.FOCVars.IbOffset += hadc2.Instance->JDR1;
		m_app.FOCVars.IcOffset += hadc1.Instance->JDR2;
		cnt++;
		if(cnt>=10)
		{
			OffsetCalibration = 1;
			m_app.FOCVars.IaOffset = m_app.FOCVars.IaOffset / 10;
			m_app.FOCVars.IbOffset = m_app.FOCVars.IbOffset / 10;
			m_app.FOCVars.IcOffset = m_app.FOCVars.IcOffset / 10;
		}
	}//上电取10次采样均值
		else
		{
		IaU16 = hadc1.Instance->JDR1;
		IbU16 = hadc2.Instance->JDR1;
		IcU16 = hadc1.Instance->JDR2;
		m_app.FOCVars.Ia = (IaU16 - m_app.FOCVars.IaOffset) * 0.02197265625f;
		m_app.FOCVars.Ib = (IbU16 - m_app.FOCVars.IbOffset) * 0.02197265625f;
		m_app.FOCVars.Ic = (IcU16 - m_app.FOCVars.IcOffset) * 0.02197265625f;
		//直接操作寄存器速度更快
		m_app.Encoder.Encoder_cnt=__HAL_TIM_GET_COUNTER(&htim4);
		m_app.Encoder.Theta=4*(2*PI*m_app.Encoder.Encoder_cnt/4096);
		rtU.ia=m_app.FOCVars.Ia;
		rtU.ib=m_app.FOCVars.Ib;
		rtU.ic=m_app.FOCVars.Ic;
		doubleloop_step();
			if(Motor_state==2)
			{
				__HAL_TIM_SET_COUNTER(&htim4,0);
			}
		TIM1->CCR1=rtY.Tabc[0];
		TIM1->CCR2=rtY.Tabc[1];
		TIM1->CCR3=rtY.Tabc[2];
		TIM1->CCR5=rtY.Tabc[2];
		}
		
}

void BSP_Init(void)
{
	HAL_OPAMP_Start(&hopamp1);
	HAL_OPAMP_Start(&hopamp2);
	HAL_OPAMP_Start(&hopamp3);//开启运放
	HAL_ADCEx_Calibration_Start( &hadc1, ADC_SINGLE_ENDED);
	HAL_ADCEx_Calibration_Start( &hadc2, ADC_SINGLE_ENDED);//ADC校准
	__HAL_ADC_CLEAR_FLAG(&hadc1, ADC_FLAG_JEOC);
	__HAL_ADC_CLEAR_FLAG(&hadc1, ADC_FLAG_EOC);
	__HAL_ADC_CLEAR_FLAG(&hadc2, ADC_FLAG_JEOC);//清除ADC转换完成标志位
	HAL_ADCEx_InjectedStart_IT(&hadc1);
	HAL_ADCEx_InjectedStart(&hadc2);//只用开启一个ADC中断，因为这两个ADC有相同的触发源
	HAL_TIM_Base_Start(&htim1);
	HAL_ADC_Start(&hadc2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);//ADC采样触发源启动
	__HAL_UART_CLEAR_FLAG(&huart3,UART_CLEAR_IDLEF);//清除串口通信中断挂起标志位
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3,m_app.UART_RxBuff.UartRxBuffer,14);//串口空闲中断
	HAL_DAC_SetValue(&hdac3,DAC_CHANNEL_1,DAC_ALIGN_12B_R,2958);//DAC设置过流比较保护超过20A，刹车保护
	HAL_DAC_Start(&hdac3,DAC_CHANNEL_1);
	HAL_COMP_Start(&hcomp1);//启动DAC比较
	HAL_TIM_Base_Start(&htim4);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
	rtU.SpeedRef=1500;
}
void Motor_StartTSK(void)
{
	rtU.Motor_OnOff=0;
	memset(&rtDW,0,sizeof(rtDW));
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);
}//开启PWM
void Motor_StopTSK(void)
{
	rtU.Motor_OnOff=1;
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);
}//关闭PWM

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if(hadc==&hadc1)
	{
		FOC_HighFrequencyTask();
	}
		
}//PWM4作为触发信号，每10KHZ采样一次，对应电流环执行频率
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==Button3_Pin)
	{
		if(m_app.UART_Cmd.State == STOP)
    {
      m_app.UART_Cmd.State = START;
    }
    else if(m_app.UART_Cmd.State == START)
    {
      m_app.UART_Cmd.State = STOP;
    }
  }
	
}//按键3也可以控制电机启停
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3,m_app.UART_RxBuff.UartRxBuffer,14);
	m_app.UART_RxBuff.DataDecodingState=1;
}//串口通信空闲中断回调
void LED_LowFreqToggle(void)//放进FOC低频任务中测试低频任务是否正常运行
{
	static uint16_t LED_Cnt=0;
	LED_Cnt++;
	if(LED_Cnt>=500)
	{
		LED_Cnt=0;
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);//LED1电平每0.5翻转
	}
}
void LED_MediumFreqToggle(void)
{
	static uint16_t LED_Cnt = 0;
	if(m_app.UART_Cmd.State == START)
	{
		LED_Cnt++;
		if(LED_Cnt >= 250)
		{
			LED_Cnt = 0;
			HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		}
	}//电机正常运行时电机LED每0.25S电平翻转
	else if(m_app.UART_Cmd.State == FAULT)
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
	}//电机过流保护时LED常亮
	else
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
	}//电机停止时LED熄灭
}
float Get_Vbus(void)//母线电压获取
{
	uint16_t VbusU16=0;
	float Vbus=0;
	VbusU16=HAL_ADC_GetValue(&hadc2);
	Vbus=VbusU16*3.3f/4096*26;
	return Vbus;
}

