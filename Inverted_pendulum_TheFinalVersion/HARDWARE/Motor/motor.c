#include "motor.h"

//===  有电桥。===//

/****************启摆  使用*****************/// 0 -- 7200
void motor_Anticlockwise(float right_duty)   //====右转
{
					TIM_SetCompare3(TIM3, right_duty);//输入占空比
					GPIO_SetBits(GPIOA,GPIO_Pin_5);
}

void motor_Clockwise(float contray_duty)    //====左转
{
					TIM_SetCompare3(TIM3, contray_duty);
					GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

/**************除启摆外使用*****************/
void motor_pwm(float duty)     //0 -- 7200
{
					if(duty>=0)
					{
							GPIO_SetBits(GPIOA,GPIO_Pin_5);//====电机反转，逆时针
//							GPIO_SetBits(GPIOA,GPIO_Pin_4);
							TIM_SetCompare3(TIM3, duty);
					}
					else
					{
//					  	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
							GPIO_ResetBits(GPIOA,GPIO_Pin_5);//====电机正转，顺时针
							TIM_SetCompare3(TIM3, (0-duty));
					}
	
}

void motor_stop(void)    //电机停止
{
					TIM_SetCompare3(TIM3, 0);
}


void Motor_BSP_Init(void)  // 继电器的  配置
{
					GPIO_InitTypeDef GPIO_InitStructure;
						
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
						
					GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 
					GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
					GPIO_Init(GPIOA, &GPIO_InitStructure);
					
//					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//					GPIO_Init(GPIOA, &GPIO_InitStructure);
//					
//					GPIO_SetBits(GPIOB,GPIO_Pin_1);//继电器初始化拉高
}
