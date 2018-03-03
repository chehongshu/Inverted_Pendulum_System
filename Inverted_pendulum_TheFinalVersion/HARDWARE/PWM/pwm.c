#include "pwm.h"
#include "stm32f10x.h"



//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
				GPIO_InitTypeDef GPIO_InitStructure;
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
				TIM_OCInitTypeDef  TIM_OCInitStructure;
				//Step2, 使能外设时钟 TIM2 TIM3 GPIOA
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
				//Step3, 初始化要用到的GPIO
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				//Step4, 重设为缺省值
				TIM_DeInit(TIM3); //重设为缺省值
				//Step5, TIM1时钟配置
			
				TIM_TimeBaseStructure.TIM_Prescaler = psc; //预分频(时钟分频)
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
				TIM_TimeBaseStructure.TIM_Period = arr;//装载值 
				TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割
				TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;  //周期计数器值 不用管
				TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
				//Step6, Configuration in PWM mode
				TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     //PWM模式一
				TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //正向通道有效  
				TIM_OCInitStructure.TIM_Pulse = 0; //TIM_Pulse/TIM_Period=duty_cycle
				TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   //输出极性
				TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset; //空闲状态下为非工作状态

				TIM_OC3Init(TIM3,&TIM_OCInitStructure);
			
				//Step7,  TIM3 counter enable开计数器
				TIM_Cmd(TIM3,ENABLE);
		

				TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  
			 
				TIM_ARRPreloadConfig(TIM3, ENABLE);	//??ARR?????? 
				//Step8,  TIM2 TIM3 Main Output Enable 使能TIM3的外设主输出  必须的
				TIM_CtrlPWMOutputs(TIM3,ENABLE);
   
}
