#include <REGX52.H>
#include "OneWire.h"
#define DS18B20_SKIP_ROM              0xCC
#define DS18B20_CONVERT_T              0x44
#define DS18B20_READ_SCRATCHPAD              0xBE

void DS18B20_ConverT(void)
{
	OneWire_Init();
	onewire_sendByte(DS18B20_SKIP_ROM);
	onewire_sendByte(DS18B20_CONVERT_T);
}

float DS18B20_readT(void)
{
	unsigned char TLSB,TMSB;
	int Temp;
	float T;
	OneWire_Init();
	onewire_sendByte(DS18B20_SKIP_ROM);
	onewire_sendByte(DS18B20_READ_SCRATCHPAD);
	TLSB=onewire_reciveByte();
	TMSB=onewire_reciveByte();
	Temp=(TMSB<<8)|TLSB;
	T=Temp/16.0;
	return T;
}

