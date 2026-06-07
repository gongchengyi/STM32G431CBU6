#ifndef __MOTOR_COMM_FUNC_H
#define __MOTOR_COMM_FUNC_H

void Motor_Load_UART_Tx_Buff(void);
uint8_t split_string(char *str,char delimiter,char **left,char **right);
float my_strtof(const char *str) ;
void Motor_UART_Rx_Data_Decoding(void);
#endif
