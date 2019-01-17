#include "time.h"

void timeinit()
{
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL1=(65536-50000)%256;	//50ms时11.0592MHz的N为45872,12MHz的N为50000
	EA=1;  //总中断	
	ET0=1; //允许定时器0中断
	
}

