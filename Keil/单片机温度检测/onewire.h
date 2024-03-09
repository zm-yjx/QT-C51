#ifndef  __OneWire_H__
#define  __Onewire_H__

unsigned char OneWire_Init(void);
void onewire_sendbit(unsigned char Bit);
unsigned char onewire_receiveBit(void);
void onewire_sendByte(unsigned char Byte);
unsigned char onewire_reciveByte(void);


#endif