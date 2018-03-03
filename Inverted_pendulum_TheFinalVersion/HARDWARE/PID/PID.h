#ifndef __PID_H
#define __PID_H
#include "stm32f10x.h"


#define uint8 unsigned char 
#define uint16 unsigned int
#define uint32 unsigned long int




/****************º¯ÊıÉùÃ÷****************/
void Set_PID_Angle(int Kp,int Kd);
void Set_PID_Location(int Kp,int Kd);
int balance(float Angle);
int Position(int Encoder);
#endif 

