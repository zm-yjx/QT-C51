#include<REGX52.H>

sbit OneWire_DQ=P3^7;

unsigned char OneWire_Init(void)
{
	unsigned char i;
	unsigned char ACKBit;
	OneWire_DQ=1;
	OneWire_DQ=0;
	i = 247;while(--i);  //delay 500us
	OneWire_DQ=1;
	i = 32;while(--i);  //delay 70us
	ACKBit=OneWire_DQ;
	i = 247;while(--i); //delay 500us
	return ACKBit;
}

void onewire_sendbit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ=0;
	i = 4;while(--i); //delay 10us
	OneWire_DQ = Bit;
	i = 24;while(--i); //delay 50us
	OneWire_DQ=1;
}

unsigned char onewire_receiveBit(void)
{
	unsigned char i;
	unsigned char Bit;
	OneWire_DQ=0;
	i = 2;while(--i);              	//delay 5us
	OneWire_DQ=1;
	i = 2;while(--i);              //delay 5us
	Bit=OneWire_DQ;
	i = 24;while(--i);             //delay 50us
	return Bit;
}

void onewire_sendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		onewire_sendbit(Byte&(0x01<<i));
	}
}

unsigned char onewire_reciveByte(void)
{
	unsigned char i;
	unsigned char Byte=0x00;
	for(i=0;i<8;i++)
	{
		if(onewire_receiveBit())
		{
			Byte|=(0x01<<i);
		}
	}
	return Byte;
}