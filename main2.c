
#include <lpc21xx.h>

#include "LCD2.h"
#include "RTC.h"
#include "ADC2.h"
#include "keypad.h"
#include "delay2.h"

#include "LCD_DEFINES.h"
#include "RTC_DEFINES.h"
#include "ADC_DEFINES.h"
#include "KEYPAD_DEFINES.h"

unsigned int ReadNum(unsigned char digits)
{
  char key;
	unsigned int num = 0;
	unsigned char count = 0;
	unsigned char pos = 0xC0;
	
	while(1)
    {
			key = KeyScan();
			
			// NUMBER PRESS
			if(key >= '0' && key <= '9')
        {
					if(count < digits)
            {
							CmdLCD(pos);
							CharLCD(key);
							num = (num * 10) + (key - '0');
							count++;
							pos++;
            }
						while(KeyScan());
        }
				// BACKSPACE
				else if(key == '*')
        {
					if(count > 0)
            {
              count--;
							num = num / 10;
							pos--;
							CmdLCD(pos);
							CharLCD(' ');
							CmdLCD(pos);
            }
					while(KeyScan());
        }

        // ENTER
				else if(key == '#')
        {
          while(KeyScan());
					return num;
        }
    }
}

int main()
{
	unsigned int light;
	char key = 0;
	unsigned int mode = 0;
	unsigned int submenu = 0;
	unsigned int value;
	
	Init_LCD();
	CmdLCD(0x80);
	StrLCD("SMART STREET");
	CmdLCD(0xC0);
	StrLCD("LIGHT SYSTEM");
	delay_ms(500);
	CmdLCD(0x01);
	keypad_init();
	RTC_Init();
	ADC_Init();
	
	// P0.7 as GPIO
	
	PINSEL0 &= ~(3 << 14);
	
	// LED OUTPUT
	
	IODIR0 |= 1 << 7;
	RTC_SetTime(20,45,00);
	RTC_SetDate(16,5,2026);
	DOW = 5;
	while(1)
    {
      // NORMAL DISPLAY
			
			if(mode == 0)
        {
          light = ADC_Read();
					RTC_DisplayTime();
					RTC_DisplayDate();
					CmdLCD(0xCC);
					if((HOUR >= 18 || HOUR < 6) && (light == 1013))
            {
              IOSET0 = 1 << 7;
							
							StrLCD("ON ");
            }
            else
            {
              IOCLR0 = 1 << 7;
							StrLCD("OFF");
            }

            // OPEN MAIN MENU
            key = KeyScan();
						if(key == '#')
            {
              CmdLCD(0x01);
							CmdLCD(0x80);
							StrLCD("1.RTC EDIT");
							CmdLCD(0xC0);
							StrLCD("2.EXIT");
							mode = 1;
							delay_ms(300);
            }
        }

        // MAIN MENU
        else if(mode == 1)
        {
          key = KeyScan();
					
					// RTC EDIT
					if(key == '1')
            {
              CmdLCD(0x01);
							CmdLCD(0x80);
							StrLCD("1.H 2.M 3.S 4.D");
							CmdLCD(0xC0);
							StrLCD("5.DT 6.M 7.YR");
							submenu = 1;
							mode = 2;
							delay_ms(300);
            }

            // EXIT
            else if(key == '2')
            {
							CmdLCD(0x01);
							mode = 0;
							delay_ms(300);
            }
        }

        // RTC SUBMENU
        else if(mode == 2)
        {
          key = KeyScan();
					// HOUR
					if(key == '1')
            {
							CmdLCD(0x01);
							CmdLCD(0x80);
							StrLCD("ENTER HOUR");
							value = ReadNum(2);
							if(value <= 23)
                {
                  HOUR = value;
                }
								mode = 0;
            }

            // MINUTE
            else if(key == '2')
            {
              CmdLCD(0x01);
							CmdLCD(0x80);
							StrLCD("ENTER MIN");
							value = ReadNum(2);
							if(value <= 59)
                {
                  MIN = value;
                }

                mode = 0;
            }

            // SECOND
            else if(key == '3')
            {
              CmdLCD(0x01);
							CmdLCD(0x80);
							StrLCD("ENTER SEC");
							value = ReadNum(2);
							if(value <= 59)
                {
                  SEC = value;
                }

                mode = 0;
            }

            // DAY
          else if(key == '4')
            {
              CmdLCD(0x01);
							CmdLCD(0x80);
							StrLCD("DAY 0-6");
							value = ReadNum(1);
							if(value <= 6)
                {
                  DOW = value;
                }

                mode = 0;
            }

            // DATE
            else if(key == '5')
            {
              CmdLCD(0x01);
							CmdLCD(0x80);
							StrLCD("ENTER DATE");
							value = ReadNum(2);
							if(value >= 1 && value <= 31)
                {
                  DOM = value;
                }

                mode = 0;
            }

            // MONTH

            else if(key == '6')
            {
              CmdLCD(0x01);
							CmdLCD(0x80);
							StrLCD("ENTER MONTH");
							value = ReadNum(2);
							if(value >= 1 && value <= 12)
                {
                  MONTH = value;
                }

                mode = 0;
            }

            // YEAR

            else if(key == '7')
            {
              CmdLCD(0x01);
							CmdLCD(0x80);
							StrLCD("ENTER YEAR");
							value = ReadNum(4);
							if(value >= 2000 && value <= 4095)
                {
                  YEAR = value;
                }

                mode = 0;
            }

            // EXIT

            else if(key == '8')
            {
              CmdLCD(0x01);
							mode = 0;
            }
        }

        delay_ms(100);
    }
}