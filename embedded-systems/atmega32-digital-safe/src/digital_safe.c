#include <mega32.h>
#include <alcd.h>

flash char Pattern[4] = {0x01, 0x02, 0x04, 0x08};
flash char key[4][4]={'7','8','9','/',
                     '4','5','6','*',
                     '1','2','3','-',
                     'C','0','=','+'};
char check[4]={'='};
char mainpass[4]={' '};
char yourpass[4]={' '};
char userpass[4]={' '};
int i;
char ch;
int checkpass;

void firstpass (void);
void checkpassword(void);
void yourpassword(void);

interrupt [EXT_INT1] void ext_int1_isr(void)
{
   int i, column = -1;
   char ch;

   for (i=0; i<4; i++)
   {
       PORTD = Pattern[i];

       if (PIND.4 == 1) { column = 0; break; }
       else if (PIND.5 == 1) { column = 1; break; }
       else if (PIND.6 == 1) { column = 2; break; }
       else if (PIND.7 == 1) { column = 3; break; }
   }

   if (column != 0)
   {
     ch = key[i][column];
   }
}

void main(void)
{
  DDRA=0x00;
  PORTA=0x00;
  DDRB=0x81;
  PORTB=0x00;
  DDRD=0x0F;
  PORTD=0xF0;

  GICR|=(1<<INT1);
  MCUCR=(1<<ISC11) | (1<<ISC10) | (0<<ISC01) | (0<<ISC00);
  MCUCSR=(0<<ISC2);
  GIFR=(1<<INTF1) | (0<<INTF0) | (0<<INTF2);

  lcd_init(16);
  #asm("sei")

  while (1)
  {
    firstpass();
    lcd_gotoxy(0,1);
    lcd_puts("enter your password:");
    yourpassword();
  }
}

void firstpass (void)
{
  lcd_puts("enter password:");
  for (i=0;i<=3;i++)
  {
    if(ch == '1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9')
    {
      lcd_putchar(ch);
      mainpass[i]=ch;
    }
    else i--;
  }

  while(1)
  {
    if(ch=='+')
    {
      for(i=0;i<4;i++) userpass[i]=mainpass[i];
      lcd_clear();
      lcd_puts("save");
      break;
    }
  }

  lcd_clear();
  lcd_puts("press C to close");

  while(1)
  {
    if(ch=="C")
    {
      lcd_clear();
      lcd_puts("close");
      break;
    }
  }
}

void checkpassword(void)
{
  checkpass=1;
  for(i=0; i<=3;i++)
  {
    if(yourpass[i]!=userpass[i]) checkpass=0;
  }

  if(checkpass==1)
  {
    lcd_clear();
    lcd_puts("dore is open");
  }
  else
  {
    lcd_clear();
    lcd_puts("dore is close");
  }
}

void yourpassword(void)
{
  for (i=0;i<=3;i++)
  {
    if(ch == '1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9')
    {
      lcd_putchar(ch);
      yourpass[i]=ch;
    }
  }

  lcd_clear();
  lcd_puts("press C to check");
  while(1)
  {
    if(ch=="C") break;
  }
  checkpassword();
}
