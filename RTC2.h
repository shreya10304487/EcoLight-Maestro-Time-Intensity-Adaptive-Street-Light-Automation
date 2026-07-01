#ifndef RTC2_H
#define RTC2_H

void RTC_Init(void);

void RTC_SetTime(unsigned char hr,
                 unsigned char min,
                 unsigned char sec);

void RTC_SetDate(unsigned char date,
                 unsigned char month,
                 unsigned int year);

void RTC_DisplayTime(void);

void RTC_DisplayDate(void);

#endif