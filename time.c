#include "time.h"

void timeinit()
{
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL1=(65536-50000)%256;	//50msʱ11.0592MHz��NΪ45872,12MHz��NΪ50000
	EA=1;  //���ж�	
	ET0=1; //������ʱ��0�ж�
	
}
