#include "timer.h"
#include "adc.h"
#include "motor.h"
#include "PID.h"
#include "encoder.h"

/////        扫描使用。

//通用定时器中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器5!
void Timer5_Init(u16 arr,u16 psc)
{
				TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
				NVIC_InitTypeDef NVIC_InitStructure;

				RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //时钟使能

				TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
				TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
				TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
				TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
				TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
		 
				  TIM_ITConfig(  //使能或者失能指定的TIM中断
					TIM5, //TIM5
					TIM_IT_Update ,
					ENABLE  //使能
					);
					NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5中断
					NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
					NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
					NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
					NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

					TIM_Cmd(TIM5, ENABLE);  //使能TIMx外设
									 
}

///  Set_PID_Angle(340,2600);
///  Set_PID_Location(65,3200);
extern int Position_Zero;   //===编码器的脉冲计数 目标值
int  	  Angle;  					 	       //===角度 
int      LAST_Angle;				 //=== 上一次的角度
int    	Angle_PWM; 			   //=== 角度的PWM
int		  Encoder;               //=== 编码器的值
int 			Encoder_PWM;		 //=== 编码器算出来的PWM
int			PWM_VALUE;       //=== PWM最后的值
int 			XIAN_FU=3100;    //=== 限幅
int 			Encoder_Last;			 //=== 上一次的编码器的值 
int		  Speed;									 //===  速度
int      delay_25ms;					 //=== 延时25ms
//int      delay_10ms;				 //=== 延时10ms
int      QB_FLAG;						 //=== 启摆的标志位
extern int FUNCTION_1;
extern int ZHONGZHI;		  //===  中值
int      QB_STOP_ANG = 70;  //===  启摆范围的角度 为70度  即在 下方 140度 启用启摆

int    Position_TARGET = 1120;   //===  转圈的 最终 编码器的值
int    count = 0;															//===  计数		
int    Draw_circle_FLAG;							//===  画圆的标志位   顺时针
int    Draw_circle_FLAG_opposite;   	//===  画圆的标志位    逆时针
/******************** TIM5  中断    函数*************************/
void TIM5_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
					TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
					//   扫描部分。  5ms一次扫描
							/******************  转圈功能，在起摆倒立之后使用*********************/
			
															  if(Draw_circle_FLAG==1) //===摆杆顺时针运动
																{
																			Position_Zero++; 
																				count++;	
																			if(count==Position_TARGET) 	Draw_circle_FLAG=0,count=0;
																}	
																
																
																if(Draw_circle_FLAG_opposite == 1)//===摆杆逆时针运动
																{
																			Position_Zero--; 
																				count++;	
																			if(count==Position_TARGET) 	Draw_circle_FLAG_opposite=0,count=0;
																	
																}														

						/****************** PD控制  角度环  位置环********************/
															LAST_Angle = Angle;//=== 上一次的角度值，用于起摆
															Angle = Angle_Get();//===  角度更新
															Encoder = Read_Encoder(4);//=== 位置更新
					           	if((Angle > (ZHONGZHI-QB_STOP_ANG))&&(Angle<(ZHONGZHI+QB_STOP_ANG)))
											{
																						Angle_PWM =balance(Angle);            //===角度PD控制	
																									delay_25ms++;
																					 if(delay_25ms == 5)
																					 {
																									Encoder_PWM=Position(Encoder);
																									//==== 对编码器限幅
																								  if(Encoder_PWM>2000){ Encoder_PWM = 2000;}
																									if(Encoder_PWM<-2000){Encoder_PWM = -2000;}
																									delay_25ms = 0;
																					 }
																				 					PWM_VALUE=Angle_PWM-Encoder_PWM;        //===计算电机最终PWM
																					 //=== 对最终的PWM限幅
																						if(PWM_VALUE>XIAN_FU) PWM_VALUE = XIAN_FU;
																						if(PWM_VALUE< -XIAN_FU) PWM_VALUE = -XIAN_FU;

																
																						motor_pwm(PWM_VALUE);
																						// ===  更利于倒立
																						if((Angle>=(ZHONGZHI-1))&&(Angle<=(ZHONGZHI+1)))
																						{
																												motor_stop();
																						}
															}
											         /********************用于165倒立***********************/
																if(FUNCTION_1 == 0)
																{
																							if((Angle>(ZHONGZHI+15))||(Angle<(ZHONGZHI-15)))
																							{
																													motor_stop();
																							}
																}		
																if(FUNCTION_1 == 1)
																{	
																					//====   我的编码器有问题所以这样处理
																	         //==== 角度处理 只要满足 最下面那个点的角度 左右分别为  一边加  一边减即可 在起摆范围内
																								if((Angle>0 )&&(Angle<ZHONGZHI-QB_STOP_ANG))
																								{
																										 Angle += 360;
																								}
																			/******************************  起摆功能*********************************/					
																								if((Angle > (ZHONGZHI-QB_STOP_ANG))&&(Angle<(ZHONGZHI+QB_STOP_ANG)))
																									{
																															if(QB_FLAG == 0)
																															{
																																	 TIM4->CNT =Position_Zero;	
																																	 QB_FLAG = 1;
																															}
																									}else
																									{
																															  QB_FLAG = 0;
																																Encoder_PWM = 0;
																																Angle_PWM = 0;
																																PWM_VALUE = 0;
																															if(LAST_Angle>Angle)
																															{
																																					motor_Anticlockwise(1800);         
																															}
																															else
																															{
																																					 motor_Clockwise(1800);	
																															} 
																									}
																									
																		}
					 
	

		}
}
		

