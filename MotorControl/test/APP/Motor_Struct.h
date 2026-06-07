#ifndef __MOTOR_STRUCT_H
#define __MOTOR_STRUCT_H

#define UART_BUFFER_SIZE 256
#define PI 3.14159265358979f

typedef enum
{
	STOP=0x00u,//停止
	START=0x01u,//启动
	FAULT=0x03u,//错误
}Motor_State_t;//电机状态类型，状态为无符号数

typedef struct
{
	Motor_State_t State;//电机状态变量
	int16_t SpdRef;//参考转速
	float PosRef;//参考位置
	float SpdKp;//速度环P参数
	float SpdKi;//速度环I参数
	float CurrKp;//电流环P参数
	float CurrKi;//电流环I参数
	uint8_t CtlMode;//控制模式
}UART_Cmd_t;//串口指令接收

typedef struct
{
	float Ia;//A相电流
	float Ib;//B相电流
	float Ic;//C相电流
	float Iq_Ref;//q轴参考电流
	float Iq;//q轴实际电流
	float Id;//d轴实际电流
	float VBus;//总线电压
	float EIAngle;//转子电角度
	float Position;//电机位置
	int16_t Speed;//电机速度
	uint16_t IaOffset;//A相电流偏置
	uint16_t IbOffset;//B相电流偏置
	uint16_t IcOffset;//C相电流偏置
}FOCVars_t;//FOC相关参数类型

typedef struct
{
	uint16_t Encoder_cnt;
	float Theta;
}Encoder_t;

typedef struct
{
	uint8_t UartRxBuffer[UART_BUFFER_SIZE];//串口接收数据
	uint8_t UartRxComplete;//串口接收完成标志位
	uint8_t DataDecodingState;//数据解码状态
}UART_RxBuff_t;//串口接受数据帧

typedef struct
{

	UART_Cmd_t UART_Cmd;
	FOCVars_t FOCVars;
	UART_RxBuff_t UART_RxBuff;
	Encoder_t Encoder;
}Motor_App_t;//电机结构体总体

void m_app_Init(void);
extern Motor_App_t m_app;

#endif
