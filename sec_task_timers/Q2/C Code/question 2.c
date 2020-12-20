#include <mega16.h>
#include <delay.h>

int SevSeg[10] = {0b00111111 , 0b00000110 , 0b01011011 , 0b01001111 , 0b01100110 , 0b01101101 , 0b01111101 , 0b00000111 ,0b01111111 ,0b01101111};
int Timer1Counter=0;
int temp = 0;
int Timer0Counter =0;
int SevenSegCounter[4] = {0,0,0,0};
int i =3;
int lastSevenSeg=3;

// Declare your global variables here

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
++Timer0Counter;
    if(Timer0Counter ==2){
           PORTD = SevSeg[SevenSegCounter[lastSevenSeg]];
           temp = temp >>1;
           if(temp ==0){
           temp = 8;
           }
           PORTC = temp ^ 0b11111111;

              Timer0Counter=0;
             lastSevenSeg--;
             if(lastSevenSeg == -1 ){
             lastSevenSeg = 3;
             } 
    }
       TCNT0=0xFA;

}

// Timer1 overflow interrupt service routine
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
 ++Timer1Counter;
    if(Timer1Counter ==200){

         SevenSegCounter[3]++;

         while (i>=0){

            if( SevenSegCounter[i] ==10){
            SevenSegCounter[i-1]++;
            SevenSegCounter[i]=0;

            }
             i--;
         }

             i=3;
             Timer1Counter=0;
    }

        TCNT1H=0xFF;
        TCNT1L=0xF0;

}

void main(void)
{
// Declare your local variables here

DDRD=0b11111111;
PORTD=0b00000000;
DDRC=0b11111111;
PORTC=0b11101111;


TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0xFA;
OCR0=0x00;

TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0xFF;
TCNT1L=0xF0;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

// Global enable interrupts
#asm("sei")

while (1)
      {
      // Place your code here

      }
}
