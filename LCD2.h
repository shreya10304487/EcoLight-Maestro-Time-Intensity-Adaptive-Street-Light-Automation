#ifndef LCD2_H
#define LCD2_H

void Init_LCD(void);

void CmdLCD(unsigned char cmd);

void CharLCD(unsigned char data);

void StrLCD(char *str);

void U32LCD(unsigned int num);

void WriteLCD(unsigned char);


#endif