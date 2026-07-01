#include <lpc21xx.h>

#include "LCD2.h"
#include "delay2.h"
#include "LCD_DEFINES.h"

void WriteLCD(unsigned char data)
{
	IOCLR0 = 0xFF << LCDDATA;
	IOSET0 = data << LCDDATA;
	IOSET0 = 1 << EN;
	delay_ms(2);
	IOCLR0 = 1 << EN;
}

void CmdLCD(unsigned char cmd)
{
	IOCLR0 = 1 << RS;
	IOCLR0 = 1 << RW;
	WriteLCD(cmd);
	delay_ms(2);
}

void CharLCD(unsigned char data)
{
  IOSET0 = 1 << RS;
	IOCLR0 = 1 << RW;
	WriteLCD(data);
	delay_ms(2);
}

void StrLCD(char *str)
{
  while(*str)
   {
      CharLCD(*str++);
   }
}

void U32LCD(unsigned int num)
{
  unsigned char arr[10];
	int i = 0;
	if(num == 0)
   {
		CharLCD('0');
		return;
   }
	while(num)
    {
      arr[i++] = (num % 10) + '0';
			num /= 10;
    }
		for(i=i-1;i>=0;i--)
    {
     CharLCD(arr[i]);
    }
}

void Init_LCD(void)
{
  IODIR0 |= 0xFF << LCDDATA;
	IODIR0 |= (1<<RS) | (1<<RW) | (1<<EN);
	delay_ms(20);
	CmdLCD(0x38);
	CmdLCD(0x0C);
	CmdLCD(0x01);
	CmdLCD(0x06);
}