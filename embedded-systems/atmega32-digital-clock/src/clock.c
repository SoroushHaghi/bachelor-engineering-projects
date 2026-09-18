#include <io.h>
#include <mega32.h>
#include <delay.h>
flash char num [10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

int d=5;

void display(int,int,int);
void main(void)
{
  int h=0,m=0,s=0;
  int o=0;
  int jahat = +1;
  DDRA=0xFF;
  PORTA=0x00;
  DDRC=0xFF;
  PORTC=0xFF;
  DDRB=0x00;
  PORTB=0x00;

  while (1)
  {
    for(o=0;o<20;o++)
    {
      if(PINB.3==1)
      {
        jahat*=-1;
        while(PINB.3==1){}
      }

      switch (jahat)
      {
        case 1:
        {
          if(PINB.0==1) { h++; if(h==24)h=0; while(PINB.0==1){} }
          else if(PINB.1==1) { m++; if(m==60)m=0; while(PINB.1==1){} }
          else if(PINB.2==1) { s++; if(s==60)s=0; while(PINB.2==1){} }
        }
        case -1:
        {
          if(PINB.0==1) { h--; if(h==-1)h=23; while(PINB.0==1){} }
          else if(PINB.1==1) { m--; if(m==-1)m=59; while(PINB.1==1){} }
          else if(PINB.2==1) { s--; if(s==-1)s=59; while(PINB.2==1){} }
        }
      }
      display(h,m,s);
    }

    s++;
    if(s==60)
    {
      s=0; m++;
      if(m==60)
      {
        m=0; h++;
        if(h==24) h=0;
      }
    }
  }
}

void display (int h,int m,int s)
{
  int q,w,x,y,i,j;
  q=h/10; w=h%10; x=m/10; y=m%10; i=s/10; j=s%10;

  PORTC.7=0; PORTA=num[j]; delay_ms(d); PORTC.7=1;
  PORTC.6=0; PORTA=num[i]; delay_ms(d); PORTC.6=1;
  PORTC.5=0; PORTA=0x80; delay_ms(d); PORTC.5=1;
  PORTC.4=0; PORTA=num[y]; delay_ms(d); PORTC.4=1;
  PORTC.3=0; PORTA=num[x]; delay_ms(d); PORTC.3=1;
  PORTC.2=0; PORTA=0x80; delay_ms(d); PORTC.2=1;
  PORTC.1=0; PORTA=num[w]; delay_ms(d); PORTC.1=1;
  PORTC.0=0; PORTA=num[q]; delay_ms(d); PORTC.0=1;
}
