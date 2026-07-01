#include <lpc21xx.h>

#include "RTC.h"
#include "LCD.h"
#include "RTC_DEFINES.h"

char day[][4] =
{
    "SUN",
    "MON",
    "TUE",
    "WED",
    "THU",
    "FRI",
    "SAT"
};

void RTC_Init(void)
{
  CCR = 0x02;
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
	CCR = 0x01;
}

void RTC_SetTime(unsigned char hr,unsigned char min,unsigned char sec)
{
  HOUR = hr;
	MIN = min;
  SEC = sec;
}

void RTC_SetDate(unsigned char date,unsigned char month,unsigned int year)
{
  DOM = date;
	MONTH = month;
	YEAR = year;
}

void RTC_DisplayTime(void)
{
  CmdLCD(0x80);
	CharLCD((HOUR/10)+'0');
  CharLCD((HOUR%10)+'0');
	CharLCD(':');
	CharLCD((MIN/10)+'0');
  CharLCD((MIN%10)+'0');
	CharLCD(':');
	CharLCD((SEC/10)+'0');
  CharLCD((SEC%10)+'0');
	CharLCD(' ');
	StrLCD(day[DOW]);
		CharLCD(' ');
	CharLCD(' ');
}

void RTC_DisplayDate(void)
{
	CmdLCD(0xC0);
	CharLCD((DOM/10)+'0');
  CharLCD((DOM%10)+'0');
	CharLCD('/');
	CharLCD((MONTH/10)+'0');
  CharLCD((MONTH%10)+'0');
	CharLCD('/');
	U32LCD(YEAR);
}