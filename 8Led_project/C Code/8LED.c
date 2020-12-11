#include <mega16.h>
#include <delay.h>

int state = 1;

static unsigned int time_count;

//interrupt for blinking 0.5 sec
interrupt [TIM0_OVF] void timer0_ovf_isr(void) 
{
    TCNT0 = 31; 
    ++time_count; 
    if (time_count == 3333)
  {
        PORTC.0 = (PORTC.0 ^ 1); 
        time_count = 0; 
     }
}

void main(void)
{          

//for 0.5 sec
DDRC = 0x01;
TCCR0=0x02;
TCNT0=31;
TIMSK=0x01; 

DDRA = 0x00;   
PINA = 0x00;  
DDRB = 0xff;  
PORTB = 0x00;
#asm("sei")

while (1)
      {
             if(PINA.0==1)    
            {  
                PORTB = 0;    
                PORTB += 1;
                state=1;
            }
            
            if(state == 1 && PORTB != 0)
            {
                delay_ms(50);
                PORTB = PORTB<<1;
                if(PORTB == 128)
                {
                  state = 0;  
                }
            }
            else
            {  
                if(PORTB == 0)
                {
                  PORTB = 0; 
                  state = 1; 
                } 
                else
                {
                delay_ms(50);
                PORTB = PORTB>>1;  
                }
            }                
            
      }
}
