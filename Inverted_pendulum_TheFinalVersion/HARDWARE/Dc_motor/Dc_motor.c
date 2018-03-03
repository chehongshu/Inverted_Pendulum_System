#include "Dc_motor.h"
#include "sys.h" 
#include "delay.h"

/***********************************
*L298N    直流电机
*  EN   PWM    speed 
*		L_EN  PB0     E_EN   PB1
*   IN1  PB12      IN2    PB13         方向  LEFT
*   IN3  PB14      IN4      PB15       方向  RIGHT
************************************/

//电机初始化函数
void Dc_motor_Init(void) //IO初始化
{ 
		GPIO_InitTypeDef 			GPIO_InitStructure;
		//初始化IN1-->GPIOA.0,IN2-->GPIOA.11 推免输出
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA时钟 ( 需要更改)

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成推免输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB0  B1


		       L_IN_1 = 0;
	         L_IN_2 = 0;
	
					 R_IN_1 = 0;
	         R_IN_2 = 0;
	
}


/******************Left    motor******************/
void L_motor_forward(void)	   //   顺时针
{	 
           L_IN_1 = 0;
	         L_IN_2 = 1;
	
}
void L_motor_backward(void)	   //   逆时针
{	 
           L_IN_1 = 1;
	         L_IN_2 = 0;
}


/******************Right   motor******************/
void R_motor_forward(void)	   //   顺时针
{	 
           R_IN_1 = 0;
	         R_IN_2 = 1;
}
void R_motor_backward(void)	   //   逆时针
{	 
           R_IN_1 = 1;
	         R_IN_2 = 0;
}


