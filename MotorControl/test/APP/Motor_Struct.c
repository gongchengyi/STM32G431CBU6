#include "stm32g4xx.h"                  // Device header
#include "Motor_Struct.h"


Motor_App_t m_app;
void m_app_Init(void)
{
	m_app.UART_Cmd.State=STOP;
	m_app.UART_Cmd.SpdRef=0;
	m_app.UART_Cmd.PosRef=0;
	
	m_app.UART_RxBuff.UartRxComplete=0;
	m_app.UART_RxBuff.DataDecodingState=0;
}//初始化结构体变量
