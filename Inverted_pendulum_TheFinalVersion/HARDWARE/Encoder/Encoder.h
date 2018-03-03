/******************** (C) COPYRIGHT 2015 WYChen********************************
* File Name          : encoder.h
* Author             : WYChen
* Version            : V1.0.0
* Date               : 06/24/2015
* Description        : The operation of Incremental_Encoder.
*                      This file provides all functions to operate Encoder.
*******************************************************************************/
#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f10x.h"

#define Encoder_BM  390	//编码器每圈脉冲数

void TIM4_Init(void);
void TIM4_Mode_Config(void);
volatile s16 update_angle(void);
int Read_Encoder(u8 TIMX);


#endif

/*****************************使用示例*************************************
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"	
#include "12864.h"
#include "Encoder.h"
#include "timer.h"

volatile s16 encoder_num;

int main()
{
	double a=0;
	
	uart_init(9600);	 									//串口初始化为9600
	delay_init();
  LCD12864_init();//12864初始化
	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	TIM3_Init();
	Timerx_Init(1000,72);//定时器2初始化,10Khz的计数频率,计数到1ms 

	while(1)
	{
		encoder_num = update_angle();
		if(encoder_num >= 0)
		{
			J12864_led_double(1,1,encoder_num,0);
			J12864_led_double(2,1,0,0);
		}
		else
		{
			J12864_led_double(1,1,0,0);
			J12864_led_double(2,1,-encoder_num,0);
		}
		delay_ms(50);
 }
}
**************************************************************************/



