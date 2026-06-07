#include "stm32g4xx.h"                  // Device header
#include "usart.h"
#include "Motor_Struct.h"
#include "Motor_Comm_func.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "doubleloop.h"

//串口与上位机通信接口
uint8_t uart_debug_buff[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x80,0x7F};
/*根据VOFA通信协议特定帧尾才能打印数据*/
	
void Motor_Load_UART_Tx_Buff(void)
{

	float temp_f[7];
	temp_f[0]=m_app.FOCVars.Ia;
	temp_f[1]=m_app.FOCVars.Ib;
	temp_f[2]=m_app.FOCVars.Ic;
	temp_f[3]=rtU.SpeedRef;
	temp_f[4]=SpeedFd;
	temp_f[5]=rtU.Encoder_Theta;
	temp_f[6]=0;
	memcpy(uart_debug_buff,(uint8_t*)&temp_f,sizeof(temp_f));
	HAL_UART_Transmit_DMA(&huart3,(uint8_t*)&uart_debug_buff,32);
}//单片机发送数据,上位机打印

/*需要对上位机下发指令进行字符拆分得到的数字字符串转换为float类型写入单片机*/
typedef enum
{
	SPLIT_OK=0,//成功分割
	SPLIT_NULL_PARAM,//参数为空
	SPLIT_NO_DELIMITER//未找到分隔符
}SplitResult;

/**
 * @brief 按分隔符将字符串拆分为左右两部分（修改原字符串！）
 * @param str: 输入字符串（必须可写，会被修改！）
 * @param delimiter: 分隔符字符
 * @param left: 输出，指向左半部分（以'\0'结尾）
 * @param right: 输出，指向右半部分
 * @return SplitResult: 分割结果
 */
uint8_t split_string(char *str,char delimiter,char **left,char **right)
{
	if(str==NULL||left==NULL||right==NULL)
	{
		return SPLIT_NULL_PARAM;
	}
	*left=str;
	*right=NULL;
	for(;*str!='\0';str++)
	{
		if(*str==delimiter)
		{
			*str='\0';
			*right=str+1;
			return SPLIT_OK;
		}
	}
		return SPLIT_NO_DELIMITER;
}
	

/**
 * @brief 安全高效的字符串转浮点数
 * @param str: 输入字符串
 * @return 转换后的浮点数（输入为NULL时返回0.0f）
 */
float my_strtof(const char *str) 
{
    if (str == NULL) return 0.0f;  // 空指针检查

    float result = 0.0f;
    float sign = 1.0f;
    float fraction = 1.0f;
    int exponent = 0;
    int exp_sign = 1;
    
    // 状态机枚举（更清晰）
    typedef enum {
        STATE_INTEGER,  // 解析整数部分
        STATE_FRACTION, // 解析小数部分
        STATE_EXPONENT  // 解析指数部分
    } ParseState;
    ParseState state = STATE_INTEGER;

    // 1. 跳过前导空白（用标准库isspace，更简洁）
    while (isspace((unsigned char)*str)) {
        str++;
    }

    // 2. 处理符号位
    if (*str == '-') {
        sign = -1.0f;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // 3. 状态机解析（switch-case更清晰）
    while (*str != '\0') {
        switch (state) {
            case STATE_INTEGER:
                if (isdigit((unsigned char)*str)) {
                    result = result * 10.0f + (*str - '0');
                } else if (*str == '.') {
                    state = STATE_FRACTION;  // 切换到小数状态
                } else if (*str == 'e' || *str == 'E') {
                    state = STATE_EXPONENT;   // 切换到指数状态
                    str++;
                    // 处理指数符号
                    if (*str == '-') { exp_sign = -1; str++; }
                    else if (*str == '+') { str++; }
                    continue;
                } else {
                    goto end_parse;  // 无效字符，结束解析
                }
                break;

            case STATE_FRACTION:
                if (isdigit((unsigned char)*str)) {
                    fraction /= 10.0f;
                    result += (*str - '0') * fraction;
                } else if (*str == 'e' || *str == 'E') {
                    state = STATE_EXPONENT;   // 切换到指数状态
                    str++;
                    // 处理指数符号
                    if (*str == '-') { exp_sign = -1; str++; }
                    else if (*str == '+') { str++; }
                    continue;
                } else {
                    goto end_parse;  // 无效字符，结束解析
                }
                break;

            case STATE_EXPONENT:
                if (isdigit((unsigned char)*str)) {
                    exponent = exponent * 10 + (*str - '0');
                } else {
                    goto end_parse;  // 无效字符，结束解析
                }
                break;
        }
        str++;
    }

end_parse:
    // 4. 计算指数部分（用powf代替循环，高效且精度高）
    if (state == STATE_EXPONENT && exponent > 0) 
		{
        float power = powf(10.0f, (float)(exp_sign * exponent));
        result *= power;
    }

    return sign * result;
}
void Motor_UART_Rx_Data_Decoding(void)
{
	char *Frame_Header;
	char *Frame_Data;
	float strtof;
	if(m_app.UART_RxBuff.DataDecodingState==1)
	{
		if(split_string((char *)m_app.UART_RxBuff.UartRxBuffer,'=',&Frame_Header,&Frame_Data)==SPLIT_OK)
		{
			strtof=my_strtof(Frame_Data);
			if(m_app.UART_RxBuff.UartRxBuffer[0]=='P'&&m_app.UART_RxBuff.UartRxBuffer[1]=='1')
			{
				if((uint8_t)strtof==1)
				{
					m_app.UART_Cmd.State=START;
				}
				else
				{
					m_app.UART_Cmd.State=STOP;
				}
			}
			if(m_app.UART_RxBuff.UartRxBuffer[0]=='P'&&m_app.UART_RxBuff.UartRxBuffer[1]=='2')
			{
				m_app.UART_Cmd.SpdRef=(int16_t)strtof;
			}
			// 解码完成，清空标志位 + 清空串口接收缓冲区
			m_app.UART_RxBuff.DataDecodingState = 0;
			memset(m_app.UART_RxBuff.UartRxBuffer, 0 , 256);
		}
	}
}
