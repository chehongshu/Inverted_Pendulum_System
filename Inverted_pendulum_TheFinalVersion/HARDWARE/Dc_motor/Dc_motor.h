#ifndef __Dc_motor_H
#define __Dc_motor_H	 
#include "sys.h"
/***********************************
*L298N    直流电机
*  EN   PWM    speed 
*		L_EN  PB0     E_EN   PB1
*   IN1  PB12      IN2    PB13         方向  LEFT
*   IN3  PB14      IN4      PB15       方向  RIGHT
************************************/


//  Left     IN1   IN2
#define  L_IN_1     PBout(14)
#define  L_IN_2     PBout(15)

//  Right     IN1   IN2
#define  R_IN_1     PBout(12)
#define  R_IN_2     PBout(13)


void Dc_motor_Init(void) ;//IO初始化



/******************Left    motor******************/
void L_motor_forward(void)	;   //   顺时针
void L_motor_backward(void);	   //   逆时针


/******************Right   motor******************/
void R_motor_forward(void)	 ;  //   顺时针
void R_motor_backward(void)	 ;  //   逆时针

#endif
