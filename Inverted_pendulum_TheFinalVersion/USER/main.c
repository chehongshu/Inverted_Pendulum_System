#include "stm32f10x.h"
#include "string.h"
#include "delay.h"
#include "usart.h"	
#include "sys.h"
#include "timer.h"
#include "key.h"
#include "motor.h"
#include "adc.h"
#include "encoder.h"
#include "PID.h"
#include "pwm.h"
#include "usart.h"
#include "usmart.h"
/*****************************
anthor: Che_hongshu
***********************/
int KEY_MODE;//====   按键标志
int FUNCTION_1;//===  启摆
int KEY_RESET; //===  复位
extern int   Draw_circle_FLAG;  //=== 画圈   顺时针
extern int 	 Draw_circle_FLAG_opposite;// 画圆   逆时针
extern int   ZHONGZHI;//=== 中值即 倒立的值
extern int   Angle;
extern int   Position_Zero;

int main()
{
/*****************初始化区*************************/

			int key;


			delay_init();                        //==== 延时初始化
	    uart_init(9600);					        //==== 串口初始化
		  usmart_dev.init(72);           //===    单片机   的主频  72M    USMART 调试用
			Adc_Init();													//====  ADC初始化
			TIM3_PWM_Init(7200-1,0);						//====Timer3的PWM初始化 arr=7200   fenpin = 0   10KHZ 的 PWM   
		  Motor_BSP_Init();              //====  直流电机初始化
			Timer5_Init(49,7199);			  //====Timer5初始化,1Khz的计数频率,计数到5ms 
			TIM4_Init();												//==== 编码器的初始化
			Set_PID_Angle(0,0);  
	    Set_PID_Location(0,0);
      KEY_Init();													//====  按键初始化
	
			while(1)
			{
									
				
							//**********   key****************/
   								 key = KEY_Scan(1);		
									 switch(key)
										{	
											
																	case KEY1_PRES:
																		
																	      ZHONGZHI  = Angle;			//=== 中值 按键设定  即  倒立点的  角度传感器的值
																						break;
																	case KEY2_PRES:
																				
																	       KEY_MODE = 1;     			//===启摆功能
																						break;
																	case KEY3_PRES:				
																        Draw_circle_FLAG = 1;		//=== 转圈功能（可以保持不倒下） 即感觉位置环的target
																						break;
																	case KEY4_PRES:
																		    Draw_circle_FLAG_opposite  = 1;	   //=== 转圈功能（可以保持不倒下） 即感觉位置环的target
																				   break;
																	case KEY5_PRES:
																							KEY_RESET = 1;
																	         break;
																		  
										}
													 if(KEY_MODE == 1)
													 {
																				FUNCTION_1 = 1;
													 }	
													 if(KEY_RESET == 1)
													 {
																			Draw_circle_FLAG = 0;
														          Draw_circle_FLAG_opposite = 0;
																			FUNCTION_1 = 0;
																			KEY_MODE   = 0;
														 
																			KEY_RESET  = 0;
													 }
											

			}
}	
