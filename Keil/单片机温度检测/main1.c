#include <regx52.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LCD1602.h"
#include "ds18b20.h"

unsigned char To[]="END";//��������λ������Ϣ

unsigned int n,flag;//���巢�ͽ�����־λ

unsigned char receiveData;//���ö�ȡ�������ݵı���
unsigned char AA[]="?!";

int key=0;//�����־λ���ã�Ԥ�����ݷ���¼��
char numkey[4];//Ԥ��������λ��
char lownum[4];//����¶�
char highnum[4];//����¶�

sbit buzzer = P1^5;//���������IO��

int res;//����
int res2;//����
float T;//��ŵ�Ƭ����ȡ�¶�����

int i,j;
int i1,j1;//����ѭ������

void delay_1ms(int c){ 
	char a,b;
	for(;c>0;c--)
	{ 
		for(b=199;b>0;b--) 
		{ 
			for(a=1;a>0;a--);
		}
	}
}//��ʱ����

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
}//����ͨ�ź�������

void Usart() interrupt 4
{		
    RI=0;
		receiveData=SBUF;//���ַ���ʽ��������
		SBUF=receiveData; 
		while(!TI);		  
		TI=0;
		if(receiveData!='H'||receiveData!='L')
		{
			 numkey[key]=receiveData;
		}
	 
		key++;//��	
		
		if(receiveData=='H'||receiveData=='L')//�����ܵ���λ���������ݺ��������ַ�ʱ�������ݷ��࡮H���Ǹ��£���L���ǵ���
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

					res2=atof(lownum);//���õ�������ͳһ��ʽ���бȽ�
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
						}//������
																									
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
					}//�����쳣�ж�					
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
					res=atof(highnum);//���õ�������ͳһ��ʽ���бȽ�
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
							}//������		
							
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
					}//�����쳣�ж�				
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
                SBUF=To[i];//�������ݵ���λ��					
                while(!TI);//�ȴ����ݷ������	   
                TI=0;
		    }
			  //ES=1;	   
			}		
}//����ͨѶ����(�жϺ���)

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
		UsartConfiguration();//���ô���ͨ�ŵ��жϺ���	
	}//��ѭ������ִ�иó����
}