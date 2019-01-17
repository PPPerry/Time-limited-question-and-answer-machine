#include "lcd.h"

void write_com(u8 com)
{
	lcdrs=0;
	lcdrw=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
	
}

void write_data(u8 datas)
{
	lcdrs=1;
	lcdrw=0;
	P0=datas;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;

}

void lcdinit()
{
	lcden=0;
	write_com(0x38); 
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}

void write_exact(u8 num,u8 address,u8 str[])//写入字符个数，首地址，字符串
{
	u8 i;
	write_com(0x80+address);
	for(i=0;i<num;i++)
	{
		write_data(str[i]);
		delay(5);
	}
}
void writetf()
{
	u8 tf[4];
	tf[0]='T';
	tf[1]=t+'0';
	tf[2]='F';
	tf[3]=f+'0';
	write_exact(4,0x0C,tf);
	
}
