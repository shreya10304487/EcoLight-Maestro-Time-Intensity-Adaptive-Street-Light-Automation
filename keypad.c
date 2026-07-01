#include <lpc21xx.h>

#include "delay2.h"
#include "KEYPAD_DEFINES.h"

char keypad[4][3] =
{
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};
void keypad_init(void)
{
// ROWS OUTPUT
IODIR1 |= (1<<ROW0) |(1<<ROW1) |(1<<ROW2) |(1<<ROW3);
// COLUMNS INPUT
IODIR1 &= ~((1<<COL0) |(1<<COL1) |(1<<COL2));
}

char KeyScan(void)
{
	unsigned int row,col;
	for(row=0; row<4; row++)
    {
     // ALL ROWS HIGH
			IOSET1 = (1<<ROW0) |(1<<ROW1) |(1<<ROW2) |(1<<ROW3);
			// ONE ROW LOW
			IOCLR1 = 1 << (ROW0 + row);
			for(col=0; col<3; col++)
        {
          if((IOPIN1 & (1 << (COL0 - col))) == 0)
            {
              delay_ms(20);
							return keypad[row][col];
            }
        }
    }

    return 0;
}