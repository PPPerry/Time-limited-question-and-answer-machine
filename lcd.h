#ifndef _LCD_H
#define _LCD_H

#include <reg52.h>

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

void delay(u16 ms);
void write_com(u8 com);
void write_data(u8 datas);
void lcdinit();
void write_exact(u8 num,u8 com,u8 str[]);
void writetf();
extern u8 t;
extern u8 f;
sbit lcden=P2^7; 
sbit lcdrs=P2^6; 
sbit lcdrw=P2^5;



#endif