#include <lpc21xx.h>
#include "ADC2.h"


void ADC_Init(void)
{
    PINSEL1 |= 1 << 22;
    ADCR = (1 << 0) |
           (4 << 8) |
           (1 << 21);
}
unsigned int ADC_Read(void)
{
    unsigned int adc_value;
    ADCR |= 1 << 24;
    while(((ADDR >> 31) & 1) == 0);
    adc_value = (ADDR >> 6) & 0x3FF;
    ADCR &= ~(1 << 24);
    return adc_value;
}