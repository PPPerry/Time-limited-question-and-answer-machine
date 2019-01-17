#include <stdlib.h>
#include <reg52.h>
#include "lcd.h"
#include "key.h"
#include "time.h"
//12.8第一次更新： 定时器开启提前 删去两个timestart
//12.8第二次更新： 避免出现长按按键超过3s的bug
//12.8第三次更新： 三位数选项
//12.8第四次更新： 时间限制选项
u8 code result1[]="true :-)";
u8 code result2[]="false :-(";
u8 code result3[]="time out!!!";
u8 code mode1[]="MODE SELECT";
u8 code mode2[]="TIME SELECT";
u8 code over11[]="YOU WIN!!!";
u8 code over12[]="CONGRATULATIONS!";
u8 code over21[]="Game over";
u8 code over22[]="...";
u8 timenum,p,r,limittime,t,f;

void delay(u16 ms)
{
	int x,y;
	for(x=ms;x>0;x--)
		{
			for(y=110;y>0;y--);
		}
}

void timestart()  //定时器重装初值
{	
	TH0=(65536-50000)/256;
	TL1=(65536-50000)%256; 
	timenum=0;
	
}
/*void randnum(char*str) //随机计算式产生函数
{
	u16 n;
	for(n=0;n<5;n++)
	{
		if(n==2)         //随机加减号
		{
			if(timenum%2)
			*(str+n)='+';
			else
			*(str+n)='-';
		}
		else if(n==0||n==3)            //保证个位数不为0
		{
			do
			{
			srand((u16)timenum);
			*(str+n)=rand()%9;
			}while(*(str+n)==0);
		}
		else
		{
		srand((u16)timenum);
		*(str+n)=rand()%9;
		}
	}
	*(str+5)='=';
}*/

u8 keyboard(u8 key) //键盘对应符号
{
	switch(key)
	{
		case 2:return '1';
		case 3:return '2';
		case 4:return '3';
		case 9:return '-';
		case 6:return '4';
		case 7:return '5';
		case 8:return '6';
		case 10:return '7';
		case 11:return '8';
		case 12:return '9';
		case 15:return '0';
	  default:return ' ';
	}
}


void main()
{
	u8 key;
	u8 cal[12];
	u16 n;
	int answer;
	r=1;  				//记录是否超时的状态参数
	TR0=1;   //开启定时器
	


	while(1)        
	{
	t=0;f=0;
	lcdinit();
	write_exact(11,0x00,mode1);
	key=keyscan();	//矩阵键盘，返回值为按下的按键
	if(key==1)  		//开机键，模式为2位数
	{
    lcdinit();
		
		write_exact(11,0x00,mode2);
		timeinit(); 
		limittime=' ';
		while(limittime==' ') //时间限制
		{key=keyscan();limittime=keyboard(key);}
		
		while(1)
		{
		lcdinit();
		if(f==5){write_exact(9,0x00,over21);write_exact(3,0x40,over22);timestart();while(timenum!=60);break;}
		if(t==5){write_exact(10,0x00,over11);write_exact(16,0x40,over12);timestart();while(timenum!=60);break;}
		r=1;
		key=' ';
		cal[6]=' ';
	  cal[7]=' ';	
	  cal[8]=' ';
		
		  
		for(n=0;n<5;n++)
		{
		if(n==2)         //随机加减号
		{
			if((p-'0')%2)
			cal[n]='+';
			else
			cal[n]='-';
		}
		else if(n==0||n==3)            //保证十位数不为0
		{
			
			srand((p-'0')+n);
			cal[n]='1'+rand()%8;
	
		}
		else
		{
		srand((p-'0')+2*n);
		cal[n]='0'+rand()%9;
		}
	}
	cal[5]='=';
		if(cal[2]=='+')
			answer=(cal[0]-'0')*10+(cal[1]-'0')+(cal[3]-'0')*10+(cal[4]-'0'); //算出正确答案
		else if(cal[2]=='-')
			answer=(cal[0]-'0')*10+(cal[1]-'0')-(cal[3]-'0')*10-(cal[4]-'0');
		
		if((answer<0&&answer>-10)||(answer>=10&&answer<=99))			//判断位数
			{cal[8]=0;}           																	//置为0后下面代码的while判断就可以跳过
		else if(answer>=0&&answer<10)
			{cal[7]=0;cal[8]=0;}																		//三位数或负两位数不需置0
		
		write_exact(6,0x00,cal);
		writetf();
		timestart();
		if(cal[6]==' ')  //输入
			{
				while(key==' ')
				{
					key=keyscan();
					if(!r)break;
					if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
					}else{
					if(timenum==(limittime-t-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				}
				if(r!=0&&key!=' ')
				{
					cal[6]=keyboard(key);
					write_com(0x80+0x06);
					write_data('0'+(cal[6]-'0'));
				}
			  
			}
		key=' ';
		
		if(r==0)continue;
		if(cal[7]==' ')
			{
				while(key==' ')
				{
					key=keyscan();
					if(!r)break;
					if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
					}else{
					if(timenum==(limittime-t-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				}
				if(r!=0&&key!=' ')
				{
					cal[7]=keyboard(key);
					write_com(0x80+0x07);
					write_data('0'+(cal[7]-'0'));
				}
			  
			}
			key=' ';
			
		if(r==0)continue;
		if(cal[8]==' ')
			{
				while(key==' ')
				{
					key=keyscan();
					if(!r)break;
					if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
					}else{
					if(timenum==(limittime-t-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				}
				if(r!=0&&key!=' ')
				{
					cal[8]=keyboard(key);
					write_com(0x80+0x08);
					write_data('0'+(cal[8]-'0'));
				}
			  
			}//完成输入
		if(r) //未超时,开始判断正误
			{
				timestart();	
				if(answer<=-10)			
			    {
						if(cal[6]=='-'&&((cal[7]-'0')*10+(cal[8]-'0'))==-answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}           																	
		      else if(answer<0&&answer>-10)
			    {
						if(cal[6]=='-'&&(cal[7]-'0')==-answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}																		
					else if(answer>=0&&answer<10)
					{
						if((cal[6]-'0')==answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}
					else if(answer>=10&&answer<=99)
					{
						if(((cal[6]-'0')*10+(cal[7]-'0'))==answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}
					else if(answer>=100)
					{
						if((cal[6]-'0')*100+(cal[7]-'0')*10+(cal[8]-'0')==answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}
			}
		  

		}
	}
		if(key==5)  		//开机键,模式为3位数
	{
    lcdinit();
		write_exact(11,0x00,mode2);
		timeinit(); 
		limittime=' ';
		while(limittime==' ') //时间限制
		{key=keyscan();limittime=keyboard(key);}
		
		while(1)
		{
		lcdinit();
		if(f==5){write_exact(9,0x00,over21);write_exact(3,0x40,over22);timestart();while(timenum!=40);break;}
		if(t==5){write_exact(10,0x00,over11);write_exact(16,0x40,over12);timestart();while(timenum!=40);break;}
		r=1;
		key=' ';
		cal[8]=' ';
	  cal[9]=' ';	
	  cal[10]=' ';
		cal[11]=' ';
		
		  
		for(n=0;n<7;n++)
		{
		if(n==3)         //随机加减号
		{
			if((p-'0')%2)
			cal[n]='+';
			else
			cal[n]='-';
		}
		else if(n==0||n==4)            //保证百位数不为0
		{
			
			srand((p-'0')+n);
			cal[n]='1'+rand()%8;
			
		}
		else
		{
		srand((p-'0')+2*n);
		cal[n]='0'+rand()%9;
		}
	}
	cal[7]='=';
		if(cal[3]=='+')
			answer=(cal[0]-'0')*100+(cal[1]-'0')*10+(cal[2]-'0')+(cal[4]-'0')*100+(cal[5]-'0')*10+(cal[6]-'0'); //算出正确答案
		else if(cal[3]=='-')
			answer=(cal[0]-'0')*100+(cal[1]-'0')*10+(cal[3]-'0')-(cal[4]-'0')*100-(cal[5]-'0')*10-(cal[6]-'0');
		
		if((answer<0&&answer>-10)||(answer>=10&&answer<=99))			//判断位数
			{cal[10]=0;cal[11]=0;}           												//置为0后下面代码的while判断就可以跳过
		else if(answer>=0&&answer<10)
			{cal[9]=0;cal[10]=0;cal[11]=0;}													
		else if((answer>=100&&answer<1000)||(answer>-100&&answer<=-10))
			{cal[11]=0;}
		
		write_exact(8,0x00,cal);
		writetf();
		timestart();
		if(cal[8]==' ')  //输入
			{
				while(key==' ')
				{
					key=keyscan();
					if(!r)break;
					if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
					}else{
					if(timenum==(limittime-t-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				}
				if(r!=0&&key!=' ')
				{
					cal[8]=keyboard(key);
					write_com(0x80+0x08);
					write_data('0'+(cal[8]-'0'));
				}
			  
			}
		key=' ';
		
		if(r==0)continue;
		if(cal[9]==' ')
			{
				while(key==' ')
				{
					key=keyscan();
					if(!r)break;
					if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
					}else{
					if(timenum==(limittime-t-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				}
				if(r!=0&&key!=' ')
				{
					cal[9]=keyboard(key);
					write_com(0x80+0x09);
					write_data('0'+(cal[9]-'0'));
				}
			  
			}
			key=' ';
			
		if(r==0)continue;
		if(cal[10]==' ')
			{
				while(key==' ')
				{
					key=keyscan();
					if(!r)break;
					if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
					}else{
					if(timenum==(limittime-t-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				}
				if(r!=0&&key!=' ')
				{
					cal[10]=keyboard(key);
					write_com(0x80+0x0A);
					write_data('0'+(cal[10]-'0'));
				}
			}
			key=' ';
			
		if(r==0)continue;
		if(cal[11]==' ')
			{
				while(key==' ')
				{
					key=keyscan();
					if(!r)break;
					if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
					}else{
					if(timenum==(limittime-t-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result3);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				}
				if(r!=0&&key!=' ')
				{
					cal[11]=keyboard(key);
					write_com(0x80+0x0B);
					write_data('0'+(cal[11]-'0'));
				}
			
			}//完成输入
		if(r) //未超时,开始判断正误
			{
				timestart();	
				if(answer<=-100)			
			    {
						if(cal[8]=='-'&&((cal[9]-'0')*100+(cal[10]-'0')*10+(cal[11]-'0'))==-answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}           																	
		      else if(answer<=-10&&answer>-100)
			    {
						if(cal[8]=='-'&&((cal[9]-'0')*10+(cal[10]-'0'))==-answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}																		
					else if(answer<0&&answer>-10)
					{
						if(cal[8]=='-'&&(cal[9]-'0')==-answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}
					else if(answer>=0&&answer<=9)
					{
						if((cal[8])==answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}
					else if(answer>=10&&answer<100)
					{
						if((cal[8]-'0')*10+(cal[9]-'0')==answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}
					else if(answer>=100&&answer<1000)
					{
						if((cal[8]-'0')*100+(cal[9]-'0')*10+(cal[10]-'0')==answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}
					else if(answer>=1000)
					{
						if((cal[8]-'0')*1000+(cal[9]-'0')*100+(cal[10]-'0')*10+(cal[11]-'0')==answer){write_exact(8,0x40,result1);t++;while(timenum!=40);}
						else{write_exact(9,0x40,result2);f++;while(timenum!=40);}
					}
			}
		}
		}
	}	
	}
	
	



void Time0()interrupt 1
{
	TH0=(65536-50000)/256;
	TL1=(65536-50000)%256;
	timenum++;
	p++;if(p==100)p++;
}