/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : hello_world
Version : 
Date    : 12/29/2020
Author  : Mahdi Firuzbakht
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 16.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <alcd.h>

void main(void)
{
lcd_init(50);
lcd_gotoxy(2,0);
lcd_putsf("Hello World!!!");   
    
    while (1)
    {
        
    }
}
