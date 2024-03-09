#include <REGX52.H>

sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;
#define LCD_DataPort P0


void LCD_Delay()  //12MHZ,1ms
{
	unsigned char i,j;
	
	i=2;
	j=239;
	do
	{
		while(--j);
	}while(--i);
}

void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_DataPort=Command;
	LCD_E=1;
	LCD_Delay();
	LCD_E=0;
	LCD_Delay();
}
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_DataPort=Data;
	LCD_E=1;
	LCD_Delay();
	LCD_E=0;
	LCD_Delay();
}

void LCD_Init(void)//chushihua
{
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}

void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else
	{
		LCD_WriteCommand(0x80|(Column-1)+0x40);
	}
}

void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}
int LCD_Pow(int x,int y)
{
	unsigned char i;
	int result=1;
	for(i=0;i<y;i++)
	{
		result*=x;
	}
	return result;
}
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned int Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData(0x30+Number/LCD_Pow(10,i-1)%10);
	}
}