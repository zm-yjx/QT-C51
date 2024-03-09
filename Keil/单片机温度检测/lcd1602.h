#ifndef __LCD1602_H__
#define __LCD1602_H__

void LCD_Init(void);
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char);
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned int Length);


#endif