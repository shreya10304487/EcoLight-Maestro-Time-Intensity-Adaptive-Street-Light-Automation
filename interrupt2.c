#include <lpc21xx.h>
unsigned int menu_flag = 0;
void EINT1_ISR(void) __irq
{
  menu_flag = 1;
	EXTINT = 1 << 1;
	VICVectAddr = 0;
}

void EINT1_Init(void)
{
  PINSEL0 |= 0x000000C0;
	EXTMODE |= 1 << 1;
	EXTPOLAR &= ~(1 << 1);
	VICVectAddr5 = (unsigned)EINT1_ISR;
	VICVectCntl5 = 0x20 | 15;
	VICIntEnable = 1 << 15;
}
