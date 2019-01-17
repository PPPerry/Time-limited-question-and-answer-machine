#ifndef _KEY_H
#define _KEY_H

#include <reg52.h>

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned int
#endif

void delay(u16 ms);
void display(u8 key);
extern u8 timenum;
extern u8 r;
extern u8 limittime;
void timestart();
extern u8 t;
extern u8 f;

u8 keyscan();

#endif