#include <mega16.h>
#include <delay.h>

int Seg[10] = {0b00111111 , 0b00000110 , 0b01011011 , 0b01001111 , 0b01100110 , 0b01101101 , 0b01111101 , 0b00000111 ,0b01111111 ,0b01101111};
int TimerOverFlowCounter=0;
int i =0;

// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
// Place your code here
    TimerOverFlowCounter++;
        if(TimerOverFlowCounter == 61 ){  

          if(i < 10){
           PORTC =  Seg[i];
         }else{
           i = 0 ;
           PORTC = Seg[i];

         }

         i++;

        }

TCNT1H=0xFF;
TCNT1L=0xF5;

}

void main(void)
{

DDRC=0b11111111;
PORTC=0b00000000;

TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (0<<CS10);
TCNT1H=0xFF;
TCNT1L=0xF5;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here

      }
}
