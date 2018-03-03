#include "12864.h"

uchar goon=0;//double整数坐标中间值



 uchar jiong1[]={/*--  文字:  囧  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0xFE,0x82,0x42,0xA2,0x9E,0x8A,0x82,0x86,0x8A,0xB2,0x62,0x02,0xFE,0x00,0x00,
0x00,0x7F,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x7F,0x00,0x00};

 uchar  lei1[]={/*--  文字:  畾  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x80,0x80,0x80,0xBF,0xA5,0xA5,0xA5,0x3F,0xA5,0xA5,0xA5,0xBF,0x80,0x80,0x80,0x00,
0x7F,0x24,0x24,0x3F,0x24,0x24,0x7F,0x00,0x7F,0x24,0x24,0x3F,0x24,0x24,0x7F,0x00};


 const uchar ASCALL[]=              // ASCII
{
			          
	0x00,0x00,0x00,0x00,0x00, // - -
	0x00,0x00,0x5F,0x00,0x00, // -!-
	0x00,0x07,0x00,0x07,0x00, // -"-
	0x14,0x7F,0x14,0x7F,0x14, // -#-
	0x24,0x2E,0x7B,0x2A,0x12, // -$-
	0x23,0x13,0x08,0x64,0x62, // -%-
	0x36,0x49,0x56,0x20,0x50, // -&-
	0x00,0x04,0x03,0x01,0x00, // -'-
	0x00,0x1C,0x22,0x41,0x00, // -(-
	0x00,0x41,0x22,0x1C,0x00, // -)-
	0x22,0x14,0x7F,0x14,0x22, // -*-
	0x08,0x08,0x7F,0x08,0x08, // -+-
	0x40,0x30,0x10,0x00,0x00, // -,-
	0x08,0x08,0x08,0x08,0x08, // ---
	0x00,0x60,0x60,0x00,0x00, // -.-
	0x20,0x10,0x08,0x04,0x02, // -/-
	0x3E,0x51,0x49,0x45,0x3E, // -0-
	0x00,0x42,0x7F,0x40,0x00, // -1-
	0x62,0x51,0x49,0x49,0x46, // -2-
	0x21,0x41,0x49,0x4D,0x33, // -3-
	0x18,0x14,0x12,0x7F,0x10, // -4-
	0x27,0x45,0x45,0x45,0x39, // -5-
	0x3C,0x4A,0x49,0x49,0x31, // -6-
	0x01,0x71,0x09,0x05,0x03, // -7-
	0x36,0x49,0x49,0x49,0x36, // -8-
	0x46,0x49,0x49,0x29,0x1E, // -9-
	0x00,0x36,0x36,0x00,0x00, // -:-
	0x40,0x36,0x36,0x00,0x00, // -;-
	0x08,0x14,0x22,0x41,0x00, // -<-
	0x14,0x14,0x14,0x14,0x14, // -=-
	0x00,0x41,0x22,0x14,0x08, // ->-
	0x02,0x01,0x59,0x05,0x02, // -?-
	0x3E,0x41,0x5D,0x55,0x5E, // -@-
	0x7C,0x12,0x11,0x12,0x7C, // -A-
	0x7F,0x49,0x49,0x49,0x36, // -B-
	0x3E,0x41,0x41,0x41,0x22, // -C-
	0x7F,0x41,0x41,0x41,0x3E, // -D-
	0x7F,0x49,0x49,0x49,0x41, // -E-
	0x7F,0x09,0x09,0x09,0x01, // -F-
	0x3E,0x41,0x51,0x51,0x72, // -G-
	0x7F,0x08,0x08,0x08,0x7F, // -H-
	0x00,0x41,0x7F,0x41,0x00, // -I-
	0x20,0x40,0x41,0x3F,0x01, // -J-
	0x7F,0x08,0x14,0x22,0x41, // -K-
	0x7F,0x40,0x40,0x40,0x40, // -L-
	0x7F,0x02,0x0C,0x02,0x7F, // -M-
	0x7F,0x04,0x08,0x10,0x7F, // -N-
	0x3E,0x41,0x41,0x41,0x3E, // -O-
	0x7F,0x09,0x09,0x09,0x06, // -P-
	0x3E,0x41,0x51,0x21,0x5E, // -Q-
	0x7F,0x09,0x19,0x29,0x46, // -R-
	0x26,0x49,0x49,0x49,0x32, // -S-
	0x01,0x01,0x7F,0x01,0x01, // -T-
	0x3F,0x40,0x40,0x40,0x3F, // -U-
	0x1F,0x20,0x40,0x20,0x1F, // -V-
	0x7F,0x20,0x18,0x20,0x7F, // -W-
	0x63,0x14,0x08,0x14,0x63, // -X-
	0x03,0x04,0x78,0x04,0x03, // -Y-
	0x61,0x51,0x49,0x45,0x43, // -Z-
	0x7F,0x7F,0x41,0x41,0x00, // -[-
	0x02,0x04,0x08,0x10,0x20, // -\-
	0x00,0x41,0x41,0x7F,0x7F, // -]-
	0x04,0x02,0x7F,0x02,0x04, // -^-
	0x08,0x1C,0x2A,0x08,0x08, // -_-
	0x00,0x00,0x01,0x02,0x04, // -`-
	0x24,0x54,0x54,0x38,0x40, // -a-
	0x7F,0x28,0x44,0x44,0x38, // -b-
	0x38,0x44,0x44,0x44,0x08, // -c-
	0x38,0x44,0x44,0x28,0x7F, // -d-
	0x38,0x54,0x54,0x54,0x08, // -e-
	0x08,0x7E,0x09,0x09,0x02, // -f-
	0x98,0xA4,0xA4,0xA4,0x78, // -g-
	0x7F,0x08,0x04,0x04,0x78, // -h-
	0x00,0x00,0x79,0x00,0x00, // -i-
	0x00,0x80,0x88,0x79,0x00, // -j-
	0x7F,0x10,0x28,0x44,0x40, // -k-
	0x00,0x41,0x7F,0x40,0x00, // -l-
	0x78,0x04,0x78,0x04,0x78, // -m-
	0x04,0x78,0x04,0x04,0x78, // -n-
	0x38,0x44,0x44,0x44,0x38, // -o-
	0xFC,0x24,0x24,0x24,0x18, // -p-
	0x18,0x24,0x24,0x24,0xFC, // -q-
	0x04,0x78,0x04,0x04,0x08, // -r-
	0x48,0x54,0x54,0x54,0x24, // -s-
	0x04,0x3F,0x44,0x44,0x24, // -t-
	0x3C,0x40,0x40,0x3C,0x40, // -u-
	0x1C,0x20,0x40,0x20,0x1C, // -v-
	0x3C,0x40,0x3C,0x40,0x3C, // -w-
	0x44,0x28,0x10,0x28,0x44, // -x-
	0x9C,0xA0,0xA0,0x90,0x7C, // -y-
	0x44,0x64,0x54,0x4C,0x44, // -z-
	0x08,0x36,0x41,0x00,0x00, // -{-
	0x00,0x00,0x77,0x00,0x00, // -|-
	0x00,0x00,0x41,0x36,0x08, // -}-
	0x06,0x09,0x09,0x06,0x00, // -°-
	0x08,0x04,0x08,0x10,0x08, // -~-
	0x55,0x2A,0x55,0x2A,0x55, // --

};


void LCD12864_BSP_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
    
  /* Enable the clock of LCD12864 */ 
  RCC_APB2PeriphClockCmd(LCD12864_CLOCK, ENABLE);
    
  /* Configure LCD12864 SCLK,SDA,RS,RESET,CS,LEDA and ROM CS,SCK,IN in Output PushPull mode */
	GPIO_InitStructure.GPIO_Pin   = LCD12864_CS;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_LCD12864_CS, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin   = LCD12864_RST;
	GPIO_Init(GPIO_LCD12864_RST, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin   = LCD12864_RS;
	GPIO_Init(GPIO_LCD12864_RS, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin   = LCD12864_SID;
	GPIO_Init(GPIO_LCD12864_SID, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = LCD12864_SCLK;
	GPIO_Init(GPIO_LCD12864_SCLK, &GPIO_InitStructure);
    
  GPIO_InitStructure.GPIO_Pin   = LCD12864_LED;
	GPIO_Init(GPIO_LCD12864_LED, &GPIO_InitStructure);
}
/*写指令到LCD模块*/
void transfer_command_lcd(int data1)   
{
  char i;
  J12864_RS_0();
  for(i=0;i<8;i++)
  {
    J12864_SCLK_0();
    if(data1&0x80) J12864_SID_1();
    else J12864_SID_0(); 
    J12864_SCLK_1();
    data1<<=1;
  }
}

/*写数据到LCD模块*/
void transfer_data_lcd(int data1)
{
  char i;
  J12864_RS_1();
  for(i=0;i<8;i++)
  {
    J12864_SCLK_0();
    if(data1&0x80) J12864_SID_1();
    else J12864_SID_0(); 
     J12864_SCLK_1();
    data1<<=1;
  }
}

//延时
void delay(int n_ms)               
{
 int j,k;
 for(j=0;j<n_ms;j++)
 for(k=0;k<110;k++);
}

/*LCD模块初始化*/
void initial_lcd()
{
	J12864_CS1_0();
//	J12864_ROMCS_1(); 
	J12864_RST_0();        /*低电平复位*/
	delay(20);
	J12864_RST_1();		    /*复位完毕*/
	delay(20);        
	transfer_command_lcd(0xe2);	 /*软复位*/
	delay(5);
	transfer_command_lcd(0x2c);  /*升压步聚1*/
	delay(5);	
	transfer_command_lcd(0x2e);  /*升压步聚2*/
	delay(5);
	transfer_command_lcd(0x2f);  /*升压步聚3*/
	delay(5);
	transfer_command_lcd(0x23);  /*粗调对比度，可设置范围0x20～0x27*/
	transfer_command_lcd(0x81);  /*微调对比度*/
	transfer_command_lcd(0x2f);  /*0x28,微调对比度的值，可设置范围0x00～0x3f*/
	transfer_command_lcd(0xa2);  /*1/9偏压比（bias）*/
//	transfer_command_lcd(0xc8);  /*行扫描顺序：从上到下*/
	transfer_command_lcd(0xc0);
//	transfer_command_lcd(0xa0);  /*列扫描顺序：从左到右*/  
	transfer_command_lcd(0xa1);  
	transfer_command_lcd(0x40);  /*起始行：第一行开始*/
	transfer_command_lcd(0xaf);  /*开显示*/
	J12864_CS1_1();
	J12864_LIGHT_ON();
}

void lcd_address(uint page,uint column)
{
	column=column-0x01;
	transfer_command_lcd(0xb0+page-1);   /*设置页地址*/
	transfer_command_lcd(0x10+(column>>4&0x0f));	/*设置列地址的高4位*/
	transfer_command_lcd(column&0x0f);	/*设置列地址的低4位*/	
}

/*全屏清屏*/
void clear_screen()
{
	unsigned char i,j;
	J12864_CS1_0();
	for(i=0;i<9;i++)
	{
		transfer_command_lcd(0xb0+i);
		transfer_command_lcd(0x10);
		transfer_command_lcd(0x00);
		for(j=0;j<132;j++)
		{
		  	transfer_data_lcd(0x00);
		}
	}
 	J12864_CS1_1();
}
/*显示128x64点阵图像*/
void display_128x64(uchar *dp)
{
	uint i,j;
	J12864_CS1_0();
	for(j=0;j<8;j++)
	{
		lcd_address(j+1,1);
		for (i=0;i<128;i++)
		{	
			transfer_data_lcd(*dp);					/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
			dp++;
		}
	}
	J12864_CS1_1();
}

//*显示16x16点阵图像、汉字、生僻字或16x16点阵的其他图标*/
void display_graphic_16x16(uint page,uint column,uchar *dp)
{
	uint i,j;
 	J12864_CS1_0();
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<16;i++)
		{
			transfer_data_lcd(*dp);					/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
			dp++;
		}
	}
	J12864_CS1_1();
}
/*显示8x16点阵图像、ASCII, 或8x16点阵的自造字符、其他图标*/
void display_graphic_8x16(uint page,uchar column,uchar *dp)
{
	uint i,j;
	J12864_CS1_0();
	for(j=0;j<2;j++)
	{
		lcd_address(page+j,column);
		for (i=0;i<8;i++)
		{
			transfer_data_lcd(*dp);					/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
			dp++;
		}
	}
	J12864_CS1_1();
}
/*显示5*7点阵图像、ASCII, 或5x7点阵的自造字符、其他图标*/
void display_graphic_5x7(uint page,uchar column,uchar *dp)
{
	uint col_cnt;
	uchar page_address;
	uchar column_address_L,column_address_H;
	page_address = 0xb0+page-1;
	
	J12864_CS1_0();
	
	column_address_L =(column&0x0f)-1;
	column_address_H =((column>>4)&0x0f)+0x10;
	
	transfer_command_lcd(page_address); 		/*Set Page Address*/
	transfer_command_lcd(column_address_H);	/*Set MSB of column Address*/
	transfer_command_lcd(column_address_L);	/*Set LSB of column Address*/
	
	for (col_cnt=0;col_cnt<6;col_cnt++)
	{	
		transfer_data_lcd(*dp);
		dp++;
	}
	J12864_CS1_1();
}


/********************************
    显示字符
    x   x=1-8行坐标
    y   y=1-123列坐标
*********************************/
void J12864_led_ASCALL(uint x,uint y,uchar c)
{
  uint i;
  J12864_CS1_0();
 
    lcd_address(x,y);
    for (i=0;i<5;i++)
    {	
      transfer_data_lcd(*(ASCALL+5*(c-' ')+i));				/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
      //dp++;
    }
  J12864_CS1_1();
}

/********************************
    显示字符串
    x   x=1-8行坐标
    y   y=1-123列坐标
*********************************/
void J12864_led_ASCALLS(uint x,uint y,uchar *string)
{
	unsigned char i=0;
	while(*(string+i))
	{
                J12864_led_ASCALL(x,y+i*5,*(string+i));
		i++;
	}
}

/*******************************
    显示整数
    x   x=1-8行坐标
    y   y=1-123列坐标
********************************/
void J12864_led_int(uint x,uint y,uint dat)
{
	unsigned char i=0,j=0;
	char string[10]={0};
	for(i=0;dat>0;i++)
	{
		string[i]=dat%10;
		dat/=10;
	}
	if(i==0)
	{
		J12864_led_ASCALL(x,y+i*5,'0');
                goon=y+i*5;
		return;
	}
	else
	{ 
                
		for(i--;;)
		{
			
			J12864_led_ASCALL(x,y+j*5,'0'+string[i]);
                        goon=y+j*5;
                        j++;
                       
			if(i>0)
                          i--;
			else
                          return;
		}
	}
}


/*******************************
  _x=1-8  清行
********************************/
void J12864_Clear_Line(uchar _X)
{
  unsigned char j;
  J12864_CS1_0();  
  transfer_command_lcd(0xb0+(_X-1));
  transfer_command_lcd(0x10);
  transfer_command_lcd(0x00);
  for(j=0;j<132;j++)
  {
    transfer_data_lcd(0x00);
  }
  
  J12864_CS1_1();
}

/********************************** 
    显示小数(1位)
    x   x=1-8行坐标
    y   y=1-123列坐标
		z		是否进位
**********************************/
void J12864_led_double1(uint x,uint y,double dat,u8 z)
{
	unsigned int dec;
	unsigned int inte;
	unsigned int inte_1=0;//计算位数用
	u8 inte_weishu=1;	//整数位数
	
	
	if(z)//进位，四舍五入
	{
		dec = (uint)(dat * 100);
		dec %= 100;
		dec %= 10;
		if(dec>=5)	{dat += 0.1;}
	}
	
	inte = (int)dat;
	dec = (uint)(dat * 10);
	dec %= 10;
	
	inte_1 = inte;//计算整数位数
	while(inte_1>=10)	{inte_weishu++;inte_1/=10;}
	
	J12864_led_int(x,y,inte);
	J12864_led_ASCALL(x,y+5*inte_weishu,'.');
	J12864_led_int(x,y+5*inte_weishu+5,dec);
}
/********************************** 
    显示小数(2位)
    x   x=1-8行坐标
    y   y=1-123列坐标
**********************************/
void J12864_led_double2(uint x,uint y,double dat,u8 z)
{
	unsigned int dec;
	unsigned int inte;
	unsigned int inte_1=0;//计算位数用
	u8 inte_weishu=1;	//整数位数
	
	if(z)
	{
		dec = (uint)(dat * 1000);
		dec %= 1000;
		dec %= 10;
		if(dec>=5)	{dat += 0.01;}
	}
	
	inte = (int)dat;
	dec = (uint)(dat * 100);
	dec %= 100;
	
	inte_1 = inte;//计算整数位数
	while(inte_1>=10)	{inte_weishu++;inte_1/=10;}
	
	J12864_led_int(x,y,inte);
	J12864_led_ASCALL(x,y+5*inte_weishu,'.');
	if(dec<10){J12864_led_ASCALL(x,y+5*inte_weishu+5,'0');J12864_led_int(x,y+5*inte_weishu+10,dec);}
	else			{J12864_led_int(x,y+5*inte_weishu+5,dec);}
}
/********************************** 
    显示小数(3位)
    x   x=1-8行坐标
    y   y=1-123列坐标
**********************************/
void J12864_led_double3(uint x,uint y,double dat,u8 z)
{
	unsigned int dec;
	unsigned int inte;
	unsigned int inte_1=0;//计算位数用
	u8 inte_weishu=1;	//整数位数
	
	if(z)
	{
		dec = (uint)(dat * 10000);
		dec %= 10000;
		dec %= 10;
		if(dec>=5)	{dat += 0.001;}
	}
	
	inte = (int)dat;
	dec = (uint)(dat * 1000);
	dec %= 1000;
	
	inte_1 = inte;//计算整数位数
	while(inte_1>=10)	{inte_weishu++;inte_1/=10;}
	
	J12864_led_int(x,y,inte);
	J12864_led_ASCALL(x,y+5*inte_weishu,'.');
	if(dec<10)				{J12864_led_ASCALLS(x,y+5*inte_weishu+5,"00");J12864_led_int(x,y+5*inte_weishu+15,dec);}
	else if(dec<100)	{J12864_led_ASCALL(x,y+5*inte_weishu+5,'0');J12864_led_int(x,y+5*inte_weishu+10,dec);}
	else							{J12864_led_int(x,y+5*inte_weishu+5,dec);}
}
/********************************** 
    显示小数(4位)
    x   x=1-8行坐标
    y   y=1-123列坐标
**********************************/
void J12864_led_double4(uint x,uint y,double dat,u8 z)
{
	unsigned int dec;
	unsigned int inte;
	unsigned int inte_1=0;//计算位数用
	u8 inte_weishu=1;	//整数位数
	
	if(z)
	{
		dec = (uint)(dat * 100000);
		dec %= 100000;
		dec %= 10;
		if(dec>=5)	{dat += 0.0001;}
	}
	
	inte = (int)dat;
	dec = (uint)(dat * 10000);
	dec %= 10000;
	
	inte_1 = inte;//计算整数位数
	while(inte_1>=10)	{inte_weishu++;inte_1/=10;}
	
	J12864_led_int(x,y,inte);
	J12864_led_ASCALL(x,y+5*inte_weishu,'.');
	if(dec<10)				{J12864_led_ASCALLS(x,y+5*inte_weishu+5,"000");J12864_led_int(x,y+5*inte_weishu+20,dec);}
	else if(dec<100)	{J12864_led_ASCALLS(x,y+5*inte_weishu+5,"00");J12864_led_int(x,y+5*inte_weishu+15,dec);}
	else if(dec<1000)	{J12864_led_ASCALL(x,y+5*inte_weishu+5,'0');J12864_led_int(x,y+5*inte_weishu+10,dec);}
	else							{J12864_led_int(x,y+5*inte_weishu+5,dec);}
}


/********************************** 
    显示小数(1位，带正负号)
    x   x=1-8行坐标
    y   y=1-123列坐标
		z		是否进位
**********************************/
void J12864_double1(uint x,uint y,double dat,u8 z)
{
	if(dat > 0)			{J12864_led_ASCALL(x,y,'+');J12864_led_double1(x,y+5,dat,z);}
	else if(dat < 0){J12864_led_ASCALL(x,y,'-');J12864_led_double1(x,y+5,-dat,z);}
	else						{J12864_led_double1(x,y,dat,z);}
}
/********************************** 
    显示小数(2位，带正负号)
    x   x=1-8行坐标
    y   y=1-123列坐标
		z		是否进位
**********************************/
void J12864_double2(uint x,uint y,double dat,u8 z)
{
	if(dat > 0)			{J12864_led_ASCALL(x,y,'+');J12864_led_double2(x,y+5,dat,z);}
	else if(dat < 0){J12864_led_ASCALL(x,y,'-');J12864_led_double2(x,y+5,-dat,z);}
	else						{J12864_led_double2(x,y,dat,z);}
}
/********************************** 
    显示小数(3位，带正负号)
    x   x=1-8行坐标
    y   y=1-123列坐标
		z		是否进位
**********************************/
void J12864_double3(uint x,uint y,double dat,u8 z)
{
	if(dat > 0)			{J12864_led_ASCALL(x,y,'+');J12864_led_double3(x,y+5,dat,z);}
	else if(dat < 0){J12864_led_ASCALL(x,y,'-');J12864_led_double3(x,y+5,-dat,z);}
	else						{J12864_led_double3(x,y,dat,z);}
}
/********************************** 
    显示小数(4位，带正负号)
    x   x=1-8行坐标
    y   y=1-123列坐标
		z		是否进位
**********************************/
void J12864_double4(uint x,uint y,double dat,u8 z)
{
	if(dat > 0)			{J12864_led_ASCALL(x,y,'+');J12864_led_double4(x,y+5,dat,z);}
	else if(dat < 0){J12864_led_ASCALL(x,y,'-');J12864_led_double4(x,y+5,-dat,z);}
	else						{J12864_led_double4(x,y,dat,z);}
}



/********************************** 
    显示小数
    x   x=1-8行坐标
    y   y=1-123列坐标
**********************************/
void J12864_led_double(uint x,uint y,double dat,uint point_n)
{
	int i = 0;
	int double_int = 0;
	int double_point = 0;
//	int double_length = 0;
	int data_length = 0;
	int temp = 0;
	int extern_length = 0;
	u32 base = 1;
	
	if ((dat - 0) < EPSILON)
	{
		dat = 0 - dat;
		data_length++;
		double_int = -(int)dat;
	}
	else
	{
		double_int = (int)dat;
	}

	J12864_led_int(x,y,double_int);
	
	J12864_led_ASCALL(x,goon+5,'.'); 

	for (i = 0; i < point_n; i++)
	{
		base = base * 10;
	}

	double_point = (int)((dat - double_int) * base);
	temp = double_point;

	while(temp < (base / 10))
	{
		J12864_led_ASCALL(x,goon+10+extern_length*5,'0');
		temp = temp * 10;		
		if(extern_length >= (point_n - 1) )
		{
			break;
		}	
		extern_length++;
//		if(extern_length >= (point_n - 1) )
//		{
//			break;
//		}	
	}

	J12864_led_int(x,goon+10+extern_length*5,double_point);
  goon=0;

}

void point(uchar x,uchar y)  //x:1~128   y:0~63 (1,0)左下角
{
  J12864_CS1_0();
  lcd_address(8-y/8,x);
  transfer_data_lcd(0x80>>(y%8));
  J12864_CS1_1();
}


//12864初始化
void LCD12864_init(void)
{
	LCD12864_BSP_Init();
	initial_lcd();
	clear_screen();
}

