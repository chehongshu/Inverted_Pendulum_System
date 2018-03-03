#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
 
/*********************************
*  four keys
*  
*******************************/
 
///  读取io的值
#define KEY1   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键0
#define KEY2   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键1
#define KEY3   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)//读取按键2 
#define KEY4   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)//读取按键2   未用到
#define KEY5   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)//读取按键2   未用到

#define KEY1_PRES	   1		  //KEY1  
#define KEY2_PRES	   2	  	//KEY2 
#define KEY3_PRES	   3		  //KEY3
#define KEY4_PRES    4		  //KEY4
#define KEY5_PRES    5		  //KEY5

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					    
#endif
