/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Characters
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
#include <stdio.h>

int init = 65;

int overflow = 0;

interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    if(init < 91){
        overflow++;
        if(overflow == 20)
        {
            char buffer[26];    
            sprintf(buffer, "%c",(char) init );
            
            lcd_puts(buffer);
			init++;
            
            overflow = 0;  
        }
    }
    
    TCNT1H = 0xFF;
    TCNT1L = 0xFE;
}

void main(void)
{

lcd_init(13);


TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H = 0xFF;
TCNT1L = 0xFE;

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

#asm("sei")

while (1)
      {
      // Place your code here

      }
}
