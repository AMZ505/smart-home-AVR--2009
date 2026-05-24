This program was produced by the
CodeWizardAVR V1.24.6 Standard
Automatic Program Generator
© Copyright 1998-2005 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com
e-mail:office@hpinfotech.com

Project : 
Version : 
Date    : 2/6/2009
Author  : ALI FARID & AMIN ALAIE                                                   
Company 
Comments: Shematic2
Chip type           : ATmega32
Program type        : Application
Clock frequency     : 8.000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 256
*****************************************************/

#include <mega16.h>

// Alphanumeric LCD Module functions
#asm
   .equ __lcd_port=0x1B ;PORTA
#endasm
#include <lcd.h>
 #include <delay.h>
// Standard Input/Output functions
#include <stdio.h>

// Declare your global variables here
char data[13];   
int  r1,r2,r3,r4,r5;
char a,b,c,d,e,f,g,h,i,j,k,l,m,n,k2,k3,temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0;    
void main(void)
{

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x00;
DDRC=0xFF;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0x00;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer 1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer 2 Stopped
// Mode: Normal top=FFh
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: Off
// USART Mode: Asynchronous
// USART Baud rate: 9600
UCSRA=0x00;
UCSRB=0x10;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// LCD module initialization
lcd_init(16);

while (1)
      {

     
      a=getchar();
      if(a==0xff)
      {data[0]=getchar(); 
       data[1]=getchar();
       c=data[1]; 
      data[2]=getchar();
      d=data[2];
     data[3]=getchar();  
     e=data[3]; 
        data[4]=getchar();  
        f=data[4];
       data[5]=getchar(); 
       g=data[5]; 
       data[6]=getchar();
       h=data[6];   
      data[7]=getchar();
      i=data[7];   
      data[8]=getchar();  
      j=data[8];
        data[9]=getchar(); 
        k=data[9]; 
        data[10]=getchar(); 
        k2=data[10];
        data[11]=getchar(); 
        k3=data[11];  


       l=(data[0]+data[1]+data[2]+data[3]+data[4]+data[5]+data[6]+data[7]+data[8]+data[9]+data[10]+data[11]);
        
       data[12]=getchar(); 
           
       if (data[12]==l){    
       
        lcd_clear();
        if( data[0]=='1'){
        
         lcd_putsf(" 1on");
         PORTC.0=1; 
         temp1=1;

         }   
         else  if( data[0]=='0' &&  temp1==0)  PORTC.0=0;
          if( data[1]=='2'){
         PORTC.0=0;
         } 
          if( data[2]=='3'){
         lcd_putsf(" 2on");
         PORTC.1=1;
         temp2=1;
         }         
         else if( data[2]=='0' &&  temp2==0)  PORTC.1=0;
         if( data[3]=='4'){
         PORTC.1=0;
         }        
         if( data[4]=='5'){
         } 
         else if( data[4]=='0' && temp3==0)  PORTC.2=0;
         if( data[5]=='6'){
         }        
         if( data[6]=='7'){
         }                

         if( data[7]=='8'){
         }        
         if( data[8]=='9'){
         lcd_putsf(" Cooler on");
         PORTC.2=1;
         }   
         if( data[9]=='1'){
         lcd_putsf(" Cooler off");
         PORTC.2=0;
         }

         if( data[10]=='2' &&  data[11]=='0' ){
         lcd_putsf("          lON");
         PORTC.3=1;
         }              
        if( data[10]=='0' &&  data[11]=='3' ){
         lcd_putsf("          LOF   ");
         PORTC.3=0;
         }            
        
         }    }           
         
             
     };
}
