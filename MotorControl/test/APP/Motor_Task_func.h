#ifndef __MOTOR_TASK_FUNC
#define __MOTOR_TASK_FUNC

void FOC_LowFrequencyTask(void);
void HighFrequencyTask(void);
void BSP_Init(void);
void Motor_StartTSK(void);
void Motor_StopTSK(void);
void LED_LowFreqToggle(void);
void LED_MediumFreqToggle(void);
float Get_Vbus(void);

#endif
