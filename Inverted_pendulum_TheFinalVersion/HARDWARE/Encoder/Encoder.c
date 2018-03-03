/******************** (C) COPYRIGHT 2015 WYChen********************************
* File Name          : encoder.c
* Author             : WYChen
* Version            : V1.0.0
* Date               : 06/24/2015
* Description        : The operation of Incremental_Encoder.
*                      This file provides all functions to operate Encoder.
*******************************************************************************/
#include "encoder.h"

//A相 --> PB6 
//B相 --> PB7
//Z相 --> 未用



/**********************************************************
*函数：TIM3_Mode_Config(void)
*功能：化定时器3编码器模式配置
*参数：无
*返回：无
*备注：无
**********************************************************/
void TIM4_Mode_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
/*----------------------------------------------------------------*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
	
  GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA.06,07 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;						//  浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);

/*----------------------------------------------------------------*/	

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能TIM4
	TIM_DeInit(TIM4);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
  TIM_TimeBaseStructure.TIM_Period =Encoder_BM*4-1;
  TIM_TimeBaseStructure.TIM_Prescaler =0;	    //设置预分频:
  TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//设置时钟分频系数:不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*初始化TIM3定时器 */
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	/*--------------编码配置---------------------编码模式------------------*/
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
  
	
 // Clear all pending interrupts
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   //使能中断
  //Reset counter
  TIM4->CNT =10000;				//  初始值赋予10000
	
	
	TIM_Cmd(TIM4, ENABLE);   //使能定时器3
}


/**********************************************************
*函数：TIM3_Init(void)
*功能：初始化定时器3
*参数：无
*返回：无
*备注：无
**********************************************************/
void TIM4_Init(void)
{
  TIM4_Mode_Config();
}


/**********************************************************
*函数：update_angle(void)
*功能：处理编码器数据得到角度值
*参数：无
*返回：角度值
*备注：Encoder_BM=360; 分辨率0.25度,返回整数
**********************************************************/
volatile s16 update_angle(void)
{
	volatile s16  angle=0;
	volatile s16  getangle=0;
	
	angle = TIM_GetCounter(TIM4);
	
	//处理角度
	while(angle >=  Encoder_BM*2)		{angle -= Encoder_BM*4;}
	while(angle <= -Encoder_BM*2)		{angle += Encoder_BM*4;}
	
		getangle = angle*360/(Encoder_BM*4);
	
	return getangle;
}
/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
			int Encoder_TIM;    
			 switch(TIMX)
			 {
				 case 2:  Encoder_TIM= (short)TIM2 -> CNT; break;
				 case 3:  Encoder_TIM= (short)TIM3 -> CNT; break;	
				 case 4:  Encoder_TIM= (short)TIM4 -> CNT; break;	
				 default:  Encoder_TIM=0;
			 }
			return Encoder_TIM;
}
void TIM4_IRQHandler(void)
{   
    if(TIM4->SR&0x0001)//  溢出中断
    {
        ;
    }   
    TIM4->SR&=~(1<<0);// 清除中断标志位
}
