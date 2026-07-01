#include <lpc21xx.h>

#include "LCD2.h"
#include "RTC2.h"
#include "ADC2.h"
#include "keypad.h"
#include "delay2.h"
#include "interrupt2.h"

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

        else if(key == '*')
        {
            if(count > 0)
            {
                count--;
                num /= 10;
                pos--;
                CmdLCD(pos);
                CharLCD(' ');
                CmdLCD(pos);
            }
            while(KeyScan());
        }

        else if(key == '#')
        {
            while(KeyScan());
            return num;
        }
    }
}

int main(void)
{
    unsigned int light;
    char key;
    unsigned int mode = 0;
    unsigned int value;

    Init_LCD();
    keypad_init();
    RTC_Init();
    ADC_Init();
    EINT1_Init();          // Enable External Interrupt

    PINSEL0 &= ~(3<<14);   // P0.7 GPIO
    IODIR0 |= 1<<7;        // LED Output

    RTC_SetTime(20,45,0);
    RTC_SetDate(16,5,2026);
    DOW = 5;

    CmdLCD(0x80);
    StrLCD("SMART STREET");
    CmdLCD(0xC0);
    StrLCD("LIGHT SYSTEM");
    delay_ms(500);
    CmdLCD(0x01);

    while(1)
    {
        /* ----------- Interrupt Button Opens Menu ----------- */
        if(menu_flag)
        {
            menu_flag = 0;

            CmdLCD(0x01);
            CmdLCD(0x80);
            StrLCD("1.RTC EDIT");
            CmdLCD(0xC0);
            StrLCD("2.EXIT");

            mode = 1;
        }

        /* ----------- NORMAL DISPLAY ----------- */

        if(mode == 0)
        {
            light = ADC_Read();

            RTC_DisplayTime();
            RTC_DisplayDate();

            CmdLCD(0xCC);

            if((HOUR >= 18 || HOUR < 6) && light >= 1000)
            {
                IOSET0 = 1<<7;
                StrLCD("ON ");
            }
            else
            {
                IOCLR0 = 1<<7;
                StrLCD("OFF");
            }
        }

        /* ----------- MAIN MENU ----------- */

        else if(mode == 1)
        {
            key = KeyScan();

            if(key=='1')
            {
                while(KeyScan());

                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("1.H 2.M 3.S 4.D");
                CmdLCD(0xC0);
                StrLCD("5.DT 6.M 7.Y");

                mode = 2;
            }

            else if(key=='2')
            {
                while(KeyScan());
                CmdLCD(0x01);
                mode = 0;
            }
        }

        /* -------- RTC EDIT MENU -------- */

        else if(mode == 2)
        {
            key = KeyScan();

            if(key=='1')
            {
                while(KeyScan());
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("ENTER HOUR");
                value = ReadNum(2);

                if(value<=23)
                    HOUR = value;

                mode = 0;
                CmdLCD(0x01);
            }

            else if(key=='2')
            {
                while(KeyScan());
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("ENTER MIN");
                value = ReadNum(2);

                if(value<=59)
                    MIN = value;

                mode = 0;
                CmdLCD(0x01);
            }

            else if(key=='3')
            {
                while(KeyScan());
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("ENTER SEC");
                value = ReadNum(2);

                if(value<=59)
                    SEC = value;

                mode = 0;
                CmdLCD(0x01);
            }

            else if(key=='4')
            {
                while(KeyScan());
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("DAY(0-6)");
                value = ReadNum(1);

                if(value<=6)
                    DOW = value;

                mode = 0;
                CmdLCD(0x01);
            }

            else if(key=='5')
            {
                while(KeyScan());
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("ENTER DATE");
                value = ReadNum(2);

                if(value>=1 && value<=31)
                    DOM = value;

                mode = 0;
                CmdLCD(0x01);
            }

            else if(key=='6')
            {
                while(KeyScan());
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("ENTER MONTH");
                value = ReadNum(2);

                if(value>=1 && value<=12)
                    MONTH = value;

                mode = 0;
                CmdLCD(0x01);
            }

            else if(key=='7')
            {
                while(KeyScan());
                CmdLCD(0x01);
                CmdLCD(0x80);
                StrLCD("ENTER YEAR");
                value = ReadNum(4);

                if(value>=2000 && value<=4095)
                    YEAR = value;

                mode = 0;
                CmdLCD(0x01);
            }

            else if(key=='8')
            {
                while(KeyScan());
                CmdLCD(0x01);
                mode = 0;
            }
        }

        delay_ms(100);
    }
}
