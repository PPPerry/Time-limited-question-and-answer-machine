#include "key.h"
#include "lcd.h"
u8 code result4[]="time out!!!";
u8 keyscan()
{
	u8 temp,key=' ';
	P1=0xfe;
	temp=P1;
	temp=temp&0xf0;
	if(temp!=0xf0)
	{
		delay(10);
		temp=P1;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			temp=P1;
			switch(temp)
			{
				case 0xee: key=1;break;
				case 0xde: key=2;break;
				case 0xbe: key=3;break;
				case 0x7e: key=4;break;
			}
			while(temp!=0xf0)
			{
				if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result4);
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
						write_exact(11,0x40,result4);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				
				temp=P1;
				temp=temp&0xf0;
			}
		}
	}
	P1=0xfd;
	temp=P1;
	temp=temp&0xf0;
	if(temp!=0xf0)
	{
		delay(10);
		temp=P1;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			temp=P1;
			switch(temp)
			{
				case 0xed: key=5;break;
				case 0xdd: key=6;break;
				case 0xbd: key=7;break;
				case 0x7d: key=8;break;
			}
			while(temp!=0xf0)
			{
				if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result4);
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
						write_exact(11,0x40,result4);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				temp=P1;
				temp=temp&0xf0;
			}
		}
	}
	P1=0xfb;
	temp=P1;
	temp=temp&0xf0;
	if(temp!=0xf0)
	{
		delay(10);
		temp=P1;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			temp=P1;
			switch(temp)
			{
				case 0xeb: key=9;break;
				case 0xdb: key=10;break;
				case 0xbb: key=11;break;
				case 0x7b: key=12;break;
			}
			while(temp!=0xf0)
			{
				if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result4);
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
						write_exact(11,0x40,result4);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				temp=P1;
				temp=temp&0xf0;
			}
		}
	}
P1=0xf7;
	temp=P1;
	temp=temp&0xf0;
	if(temp!=0xf0)
	{
		delay(10);
		temp=P1;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			temp=P1;
			switch(temp)
			{
				case 0xe7: key=13;break;
				case 0xd7: key=14;break;
				case 0xb7: key=15;break;
				case 0x77: key=16;break;
			}
			while(temp!=0xf0)
			{
				if(limittime>3&&(limittime-t-'0')<3){
						if(timenum==(limittime-'0')*20)
					{
						timenum=0;
						write_exact(11,0x40,result4);
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
						write_exact(11,0x40,result4);
						while(timenum!=40);
						timestart();
						r=0;
						f++;
						break;
					}
				  }
				temp=P1;
				temp=temp&0xf0;
			}
		}
		
	}
	return key;
}