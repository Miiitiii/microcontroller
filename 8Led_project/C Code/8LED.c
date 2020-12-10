#include <mega16.h>
#include <delay.h>

int state = 1;

void main(void)
{

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
