/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Question 4
Version : 
Date    : 1/7/2021
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
#include <delay.h>

// Declare your global variables here

int State[4] = {0b00001001 , 0b00000101 , 0b00000110 , 0b00001010};
int motorState = -1;
int mode = 0;
int n = 0;
int direction = 1;
int counter = 0;
int h = 0;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{ 
    if(motorState < 4 && motorState > (-1) && mode == 0)
    {
       PORTA = State[motorState];
       if(direction == 1)
       {
       motorState = motorState + 1;
       if(motorState == 4)
       {
            motorState = 0;
       }
       }
       else if(direction == 0)
       {
         motorState = motorState - 1;
         if(motorState == (-1))
       {
            motorState = 3;
       }
       }
       mode = 1;
       if(counter < 254 && h == 0)
      {
        counter++;
        if(counter == 254)
            {
            h = 1;
            }
        }
    else if(counter >= 100 && h == 1)
    {
            counter--;  
            if(counter == 100)
            {
            h = 0;
            direction = 0;
            }
      } 
    }
    else if(mode == 1)
    {
      PORTA = 0b00000000; 
      mode = 0; 
      if(counter < 254 && h == 0)
      {
        counter++;
        if(counter == 254)
            {
            h = 1;
            }
        }
    else if(counter >= 100 && h == 1)
    {       
            if(direction == 0 && counter == 101)
            {   
                mode = 2;
            }
            counter--;  
            if(counter == 100)
            {
            h = 0;
            direction = 0;
            }
      }
        
    }
    if(counter != 100)
    {  
    TCNT0 = counter;
     }
     else if(counter == 100 && direction == 0)
     {       
     n = 0;
     }
}

void main(void)
{
// Declare your local variables here

        DDRA = 0b11111111;
        TCNT0 = 1; 
        TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
        OCR0=0x00; 
    
        TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

        MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
        MCUCSR=(0<<ISC2);



while (1)
      {
      // Place your code here  
      if(PINC.2 == 0 && n == 0)
      {
      n = 1;
      h = 0; 
      direction = 1;
      motorState = 0;
      counter = 100;
      mode = 0;  
         // Global enable interrupts
        #asm("sei")
      }
      
      if(mode == 2)
      {
       // Global disable interrupts
        #asm("cli")
      }   
      

      }
}