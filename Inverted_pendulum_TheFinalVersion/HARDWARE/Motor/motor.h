#ifndef _motor_H
#define _motor_H
#include "stm32f10x.h"

	
void motor_Anticlockwise(float right_duty);     //电机逆时针转
void motor_Clockwise(float contray_duty); 			//电机顺时针转
void motor_stop(void);                //电机停止
void Motor_BSP_Init(void);   
void motor_pwm(float duty);//电机转

#endif
