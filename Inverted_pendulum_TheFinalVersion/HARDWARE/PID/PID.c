#include "PID.h"

/*
				位置式 PID 
*/

int Position_Zero=10000;            //编码器的脉冲计数
float Balance_KP=340,Balance_KD=2600,Position_KP=6.5,Position_KD=320;  //PID系数   350 2500 6.5 210
int ZHONGZHI;
//==== 用于串口调试   USMART
void Set_PID_Angle(int Kp,int Kd)
{
				Balance_KP  =  Kp;

				Balance_KD  =  Kd;
}
void Set_PID_Location(int Kp,int Kd)
{
	      Position_KP  =  Kp/10.0;

				Position_KD  =  Kd/10.0;
}

/**************************************************************************
函数功能：倾角PD控制
入口参数：角度
返回  值：倾角控制PWM
作    者：平衡小车之家
**************************************************************************/
int balance(float Angle)
{  
	
			 float Bias;                       //倾角偏差
			 static float Last_Bias,D_Bias;    //PID相关变量
			 int balance;                      //PWM返回值 
			 Bias=Angle-ZHONGZHI;              //求出平衡的角度中值 和机械相关
			 D_Bias=Bias-Last_Bias;            //求出偏差的微分 进行微分控制
			 balance=-Balance_KP*Bias-D_Bias*Balance_KD;   //===计算倾角控制的电机PWM  PD控制
			 Last_Bias=Bias;                   //保持上一次的偏差
			 return balance;
	
}

/**************************************************************************
函数功能：位置PD控制 
入口参数：编码器
返回  值：位置控制PWM
作    者：平衡小车之家
**************************************************************************/
int Position(int Encoder)
{  
   static float Position_PWM,Last_Position,Position_Bias,Position_Differential;
	 static float Position_Least;
								Position_Least =Encoder-Position_Zero;             //===
								Position_Bias *=0.8;		   
								Position_Bias += Position_Least*0.2;	             //===一阶低通滤波器  
	  Position_Differential=Position_Bias-Last_Position;
	  Last_Position=Position_Bias;
		Position_PWM=Position_Bias*Position_KP+Position_Differential*Position_KD; //===速度控制	
	  return Position_PWM;
}

