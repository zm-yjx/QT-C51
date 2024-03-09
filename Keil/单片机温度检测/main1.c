#include <regx52.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LCD1602.h"
#include "ds18b20.h"

unsigned char To[]="END";//反馈给上位机的信息

unsigned int n,flag;//定义发送结束标志位

unsigned char receiveData;//设置读取串口数据的变量
unsigned char AA[]="?!";

int key=0;//定义标志位放置，预防数据反复录入
char numkey[4];//预放置数据位置
char lownum[4];//最低温度
char highnum[4];//最高温度

sbit buzzer = P1^5;//定义蜂鸣器IO口

int res;//高温
int res2;//低温
float T;//存放单片机读取温度数据

int i,j;
int i1,j1;//定义循环参数

void delay_1ms(int c){ 
	char a,b;
	for(;c>0;c--)
	{ 
		for(b=199;b>0;b--) 
		{ 
			for(a=1;a>0;a--);
		}
	}
}//延时函数

void UsartConfiguration()
{
	SCON=0X50;			
	TMOD=0X20;			
	PCON=0X80;			
	TH1=0XF3;		    
	TL1=0XF3;
	//REN=1;
	ES=1;						
	EA=1;						
	TR1=1;					    
}//串口通信函数配置

void Usart() interrupt 4
{		
    RI=0;
		receiveData=SBUF;//以字符形式接受数据
		SBUF=receiveData; 
		while(!TI);		  
		TI=0;
		if(receiveData!='H'||receiveData!='L')
		{
			 numkey[key]=receiveData;
		}
	 
		key++;//！	
		
		if(receiveData=='H'||receiveData=='L')//当接受到上位机发送数据含有特殊字符时进行数据分类‘H’是高温，‘L’是低温
		{			
			if(receiveData=='L')
			{
				for(i=0;i<4;i++)
				{
					lownum[i]='\0';
				}
				j=key-1;
				for(i=0;i<key-1;i++)
				{
					lownum[i]=numkey[key-1-j];			
					j--;
				}
				for(i=0;i<4;i++)
				{
					numkey[i]='\0';
				}
				
				key=0;

					res2=atof(lownum);//将得到的数据统一格式进行比较
					if(res2>T)
					{
						LCD_ShowChar(2,1,'e');
						LCD_ShowChar(2,2,'r');
						LCD_ShowChar(2,3,'r');
						LCD_ShowChar(2,4,'o');
						LCD_ShowChar(2,5,'r');
						LCD_ShowChar(2,6,'!');
						delay_1ms(1000);
						
						for(i=0;i<10;i++)
						{
							buzzer=1;
							delay_1ms(5000);
							buzzer=0;
						}//蜂鸣器
																									
					}
					else
					{
						LCD_ShowChar(2,1,'n');
						LCD_ShowChar(2,2,'o');
						LCD_ShowChar(2,3,'r');
						LCD_ShowChar(2,4,'m');
						LCD_ShowChar(2,5,'a');
						LCD_ShowChar(2,6,'l');
						LCD_ShowChar(2,7,'!');
						delay_1ms(1000);
					}//低温异常判断					
			}		
			else if(receiveData=='H')
			{
				for(i=0;i<4;i++)
				{
					highnum[i]='\0';
				}
				j=key-1;
				for(i=0;i<key-1;i++)
				{
					highnum[i]=numkey[key-1-j];
					j--;
				}
				for(i=0;i<4;i++)
				{
					numkey[i]='\0';
				}
				key=0;
					res=atof(highnum);//将得到的数据统一格式进行比较
					if(res<T)
					{
						LCD_ShowChar(2,1,'e');
						LCD_ShowChar(2,2,'r');
						LCD_ShowChar(2,3,'r');
						LCD_ShowChar(2,4,'o');
						LCD_ShowChar(2,5,'r');
						LCD_ShowChar(2,6,'!');
						delay_1ms(1000);
													
							for(i=0;i<10;i++)
							{
								buzzer=1;
								delay_1ms(5000);
								buzzer=0;
							}//蜂鸣器		
							
					}
					else
					{
						LCD_ShowChar(2,1,'n');
						LCD_ShowChar(2,2,'o');
						LCD_ShowChar(2,3,'r');
						LCD_ShowChar(2,4,'m');
						LCD_ShowChar(2,5,'a');
						LCD_ShowChar(2,6,'l');
						LCD_ShowChar(2,7,'!');
						delay_1ms(1000);
					}//高温异常判断				
			}		
		}	
			  	
	if(receiveData=='H'||receiveData=='L')	
			{
			SBUF=AA[1];
			while(!TI);		 
			TI=0;			 			
				for(i=0;i<9;i++)
				{
                ES=0;          
                SBUF=To[i];//返回数据到上位机					
                while(!TI);//等待数据发送完成	   
                TI=0;
		    }
			  //ES=1;	   
			}		
}//串口通讯函数(中断函数)

void main()
{
  LCD_Init();
	LCD_ShowChar(1,1,'T');
	LCD_ShowChar(1,2,'e');
	LCD_ShowChar(1,3,'m');
	LCD_ShowChar(1,4,'p');
	LCD_ShowChar(1,5,':');
	while(1)
	{		
		DS18B20_ConverT();
		T=DS18B20_readT();		
		if(T<0)
		{
		 LCD_ShowChar(1,6,'-');
		 T=-T;
		}
		else
		{
		 LCD_ShowChar(1,6,'+');
		}
		LCD_ShowNum(1,7,T,3);
		LCD_ShowChar(1,10,'.');
		LCD_ShowNum(1,11,(unsigned long)(T*10000)%10000,2);
		UsartConfiguration();//调用串口通信的中断函数	
	}//死循环持续执行该程序段
}