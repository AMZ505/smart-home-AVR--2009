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
Company :                        
Comments: Shematic 1


Chip type           : ATmega32
Program type        : Application
Clock frequency     : 8.000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 256
*****************************************************/

#include <mega16.h>
#include <delay.h>
#include<stdio.h>
#include<stdlib.h>
// I2C Bus functions
#asm
   .equ __i2c_port=0x1B ;PORTA
   .equ __sda_bit=0
   .equ __scl_bit=1
#endasm                                                                                                                                                                                                                                                                                                                            *

#include <i2c.h>

// DS1307 Real Time Clock functions
#include <ds1307.h>

// Alphanumeric LCD Module functions
#asm
   .equ __lcd_port=0x18 ;PORTB
#endasm
#include <lcd.h>

// Declare your global variables here
unsigned char hour1f=0,minute1f=0,second1f=0,hour2f=0,minute2f=0,second2f=0,hour3f=0,minute3f=0,second3f=0,hour4f=0,minute4f=0,second4f=0  ;
unsigned char hour,minute,second,hour1=0,minute1=0,second1=0,hour2=0,minute2=0,second2=0,hour3=0,minute3=0,second3=0,hour4=0,minute4=0,second4=0;
int win1,win2,win3,win4,door,gas,temp=25;
int ii,jj,kk,hh,ll,bb,cc,dd,ee,ff,gg,aa,rr,protect,f1=0,f2=0,f3=0,f4=0; 
 char lcd1[16],lcd2[16],lcd3[20],lcd4[16],lcd5[10],lcd6[10],lcd7[10],lcd8[5],lcd9[5],lcd10[5],data[]={'0','1','2','3','4','5','6','7','8','9'},sum[13];
unsigned char year,month,day;
char password_att[5], password_temp[5],key1=0,c,i=0,accept=0,cc2;
unsigned char key,keystate; 
int k1,k2=0,k3,k4;   
char password[5]={1,3,4,0,1};



char keypad(void);    
void  new_password(void);

flash unsigned char miltable[6][12]={
        {20,19,19,19,20,20,21,21,21,21,20,20},
        {10,11,10,12,11,11,10,10,10,9,10,10},
        {19,18,20,20,21,21,22,22,22,22,21,21},
        {11,12,10,11,10,10,9,9,9,8,9,9},
        {20,19,20,20,21,21,22,22,22,22,21,21},
        {10,11,9,11,10,10,9,9,9,8,9,9}};

 struct date{
 unsigned char day;
 unsigned char month;
 unsigned char year;
}; 
 struct date shmdate,mildate ;   
  char password_check(void);
/****************************************************/
void miltoshmcv(unsigned char year,unsigned char month,unsigned char day)
{
    unsigned char k,t1,t2; 
    k=year%4;
    if(k==3)
       k=2;
    k*=2;
    t1=miltable[k][month-1];
    t2=miltable[k+1][month-1];
    if(month<3 || (month==3 && day<=miltable[k][month-1]))
       shmdate.year = year + 78;
    else
       shmdate.year = year + 79;
       
    if(day<=t1)
    { 
       shmdate.day=day+t2;
       shmdate.month=(month+8)%12+1;
    }
    else 
    { 
       shmdate.day=day-t1;
       shmdate.month=(month+9)%12+1;
    }
} 
/****************************************************/

#define ADC_VREF_TYPE 0x40

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input|ADC_VREF_TYPE;
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}
/****************************************************/


void main(void)
{   

// Declare your local variables here

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
PORTC=0xC0;
DDRC=0xF8;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=O Func0=O 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0xFC;
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
// USART Receiver: Off
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud rate: 9600
UCSRA=0x00;
UCSRB=0x08;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;
// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// I2C Bus initialization
i2c_init();

// DS1307 Real Time Clock initialization
// Square wave output on pin SQW/OUT: Off
// SQW/OUT pin state: 0
rtc_init(0,0,0);        

// ADC initialization
// ADC Clock frequency: 125.000 kHz
// ADC Voltage Reference: AVCC pin
// ADC Auto Trigger Source: None
ADMUX=ADC_VREF_TYPE;
ADCSRA=0x86;

// LCD module initialization
lcd_init(16);

while (1)
      {  
      char c[10],e[10],d[10];int u1,u2,u3;float l1,l2,l3; 
    
     
    rtc_get_time(&hour,&minute,&second);
    rtc_get_date(&day,&month,&year);
    miltoshmcv(year,month,day); 
    ii=read_adc(2);    
   putchar(0xff);
    if(hour==hour1 && minute==minute1 && second==second1){  
    putchar(data[1]) ; 
    sum[0]=data[1];
    } 
    else {
    putchar(data[0]) ;
    sum[0]=data[0];}            
    if(hour==hour1f && minute==minute1f && second==second1f)
    {
     putchar(data[2]) ;
     sum[1]=data[2];
     }             
      else { 
    putchar(data[0]) ;  
    sum[1]=data[0];}  
     if(hour==hour2 && minute==minute2 && second==second2){
     putchar(data[3]) ;  
     sum[2]=data[3];}
        else{ 
    putchar(data[0]) ;  
    sum[2]=data[0];
    }  
     if(hour==hour2f && minute==minute2f && second==second2f){
     putchar(data[4]); 
     sum[3]=data[4];
     }      
          else {
    putchar(data[0]) ; 
    sum[3]=data[0];
    }   
     if(hour==hour3 && minute==minute3 && second==second3){
     putchar(data[5]); 
     sum[4]=data[5];}
        else {
    putchar(data[0]) ; 
    sum[4]=data[0] ;
    }  
     if(hour==hour3f && minute==minute3f && second==second3f) {
     putchar(data[6]);
     sum[5]=data[6];
     }
        else{ 
    putchar(data[0]) ; 
    sum[5]=data[0];}
       
     if(hour==hour4 && minute==minute4 && second==second4){
     putchar(data[7]);
     sum[6]=data[7];
     }   
       else {
    putchar(data[0]) ;   
    sum[6]=data[0];
    }
     
     if(hour==hour4f && minute==minute4f && second==second4f){
     putchar(data[8]); 
     sum[7]=data[8];
     }
      else{ 
    putchar(data[0]) ;    
    sum[7]=data[0]; }  
    sprintf(lcd1,"%02u:%02u:%02u",hour,minute,second);
    sprintf(lcd2,"%02u/%02u/%02u",shmdate.year,shmdate.month,shmdate.day); 
    sprintf(lcd3,"Temp:%d,%dC",ii/10,ii%10);  
    
    lcd_clear();
    lcd_gotoxy(0,0);
    lcd_puts(lcd2);
    lcd_gotoxy(0,1);
    lcd_puts(lcd1);
    lcd_gotoxy(0,2);
    lcd_puts(lcd3); 
    
    
   if (temp < ii/10) {
     putchar(data[9]);   //on 
     sum[8]=data[9];
        
     }
      else { 
    putchar(data[0]) ;
    sum[8]=data[0];}    
     if (temp > ii/10){
     putchar(data[1]);   //off 
     sum[9]=data[1];
     }     
     
     
           else {
    putchar(data[0]) ; 
      sum[9]=data[0]; 
      }        
      //****************PHOTOCELLADJUSTMENT**********        
    
  u1=read_adc(3);
  u2=read_adc(4);
  u3=read_adc(5);
  
  l1=u1*0.0048875855327428; 
  l2=u2*0.0048875855327428;
  l3=u3*0.0048875855327428; 
  
  ftoa(l1,4,d); 
  ftoa(l2,4,e);
  if (l1<=1.500){
  putchar(data[2]);
  sum[10]=data[2];//out is dark
     } 
      else {
    putchar(data[0]) ; 
      sum[10]=data[0]; 
      }        
     if (l2>2.500){
    putchar(data[3])  ;
    sum[11]=data[3];//home is bright
     }         
      else {
    putchar(data[0]) ; 
      sum[11]=data[0]; 
      }        
  
sum[12]=sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7]+sum[8]+sum[9]+sum[10]+sum[11];
     putchar(sum[12]) ;         
 
        //************************LASERADJUSTMENT********
    
  if (protect==1) {
   lcd_gotoxy(0,3);
   lcd_putsf("LOCK PRESS 7");  
   if(!PIND.7){
                   delay_ms(200);
                   cc2=password_check();     
                  if (cc2==1)  
                  protect=0;
                  
                   }
     
    if(l3<=3) 
    PORTC.3=1;//BUZZER ON 
     
    
        }       
   if (protect==0) 
    PORTC.3=0;//BUZZER Off
   //*****WIN&DOORCONTROL*************************


     
    if (PINC.0==1) win1=1;
    else win1=0;
    if (PINC.1==1) win2=1;
    else   win2=0;
    if (PINC.2==1) door=1;
    else   door=0;  
    if(door) 
   {lcd_gotoxy(12,1);
    lcd_putsf("D00R"); }
    if(gas) 
   {lcd_gotoxy(12,0);
    lcd_putsf("GAS!");}
    if(win1) 
   {lcd_gotoxy(9,1);
    lcd_putsf("W1"); }
    if(win2) 
   {lcd_gotoxy(9,0);
    lcd_putsf("W2");}
    if(win3) 
   {lcd_gotoxy(10,2);
    lcd_putsf("W3"); }
    if(win4) 
   {lcd_gotoxy(13,2);
    lcd_putsf("W4");}
    delay_ms(100); 

    
//*****************SETTINGS*************************

     if (PINC.6==0)  kk=1; 
     if (protect==1) kk=0;
     while(kk)
 { 
 lcd_gotoxy(0,0);
  lcd_putsf("1set time & Date");
  lcd_gotoxy(0,1); 
  lcd_putsf("2set  program"); 
  lcd_gotoxy(0,2);
  lcd_putsf("                             "); 
  lcd_gotoxy(0,3); 
  lcd_putsf("Back:0  Next:2")  ;  
    delay_ms(500);
 if (PINC.6==0)  kk=0; 
 
 
      
   if (PINC.7==0)  jj=1;
   while(jj)
   {   
    rtc_get_time(&hour,&minute,&second);
    rtc_get_date(&day,&month,&year);
    miltoshmcv(year,month,day);    
    lcd_clear();     
    sprintf(lcd1,"%02u:%02u:%02u",hour,minute,second);        sprintf(lcd2,"%02u/%02u/%02u",shmdate.year,shmdate.month,shmdate.day); 
    lcd_gotoxy(0,0);
    lcd_puts(lcd2);
    lcd_gotoxy(0,1);
    lcd_puts(lcd1);
    lcd_gotoxy(0,2);   
    lcd_putsf("Y:2 M:3 D:4 H:5");
    lcd_gotoxy(0,3); 
    lcd_putsf("M:6 S:7 BACK:1 ");   
    delay_ms(200);  
   if (PINC.7==0)  jj=0;
key=PIND & 0b11111100;
if (key!=keystate)
{
   if (key!=0b11111100)
   {
       if (key==0xF8)        //if key 1 pressed set the year
       {
           year++;
           if (year==100)
               year=0;
       }
       if (key==0xF4)        //if key 2 pressed set the month
       {
           month++;
           if (month==13)
               month=1;
       }
       if (key==0xEC)        //if key 3 pressed set the day
       {
           day++;
           if (day==32)
               day=1;
       }
       if (key==0xDC)        //if key 4 pressed set the hour
       {
           hour++;
           if (hour==24)
               hour=0;
       } 
       if (key==0xBC)        //if key 5 pressed set the minute
       {
           minute++;
           if (minute==60)
               minute=0;
       } 
       if (key==0x7C)        //if key 6 pressed set the second
       {
           second++;
           if (second==60)
               second=0; 
       }   
       rtc_set_time(hour,minute,second);
       rtc_set_date(day,month,year);
       keystate=key;
   }else
       keystate=0b11111100;
}  

} 
lcd_clear();       
if (PIND.2==0)  ll=1;
     while(ll) {   
         lcd_clear();
         lcd_gotoxy(0,0);   
         lcd_putsf("3:for temp prog")  ; 
         lcd_gotoxy(0,1);   
         lcd_putsf("4:for relay prog ")  ; 
         lcd_gotoxy(0,2);   
         lcd_putsf("6:for Mode 2  ")  ;
         lcd_gotoxy(0,3); 
          lcd_putsf("Back:2   Next:7")  ; 
        delay_ms(200);      
         lcd_clear();       
         if  (PIND.7==0) k1=1;
         while(k1){
         delay_ms(200); 
         if  (PIND.7==0) k1=0;
         lcd_gotoxy(0,0); 
         lcd_putsf("1:chang pasword")  ; 
         lcd_gotoxy(0,1); 
         lcd_putsf("7:back                    ") ;  
          if  (PINC.7==0)  k2=!k2;
          while(k2){  
         delay_ms(500);
         new_password()  ;
         k2=!k2;               
          
          }
           }
         
         if (PIND.2==0)  ll=0;
          if (PIND.3==0)  bb=1;  
          while(bb){
          
          delay_ms(200);
          if (PIND.3==0)  bb=0; 
          lcd_gotoxy(0,0);
         lcd_putsf("enter fave temp: (by 1&2 back:3)")  ;     
         
          if (PINC.7==0) temp++;
          if (PIND.2==0) temp--;
          sprintf(lcd4,"Now is: %02u",temp);
          lcd_gotoxy(0,2);   
          lcd_puts(lcd4); } 
          //*********************************************
           if (PIND.6==0)  ee=1;     
             
              while(ee)
              {
              delay_ms(200);   
              if (PIND.6==0) ee=0;
              lcd_gotoxy(0,0);
              lcd_putsf("Enter Pass")  ;
               lcd_gotoxy(0,1);
               lcd_putsf("Quit: 6")  ; 
             
                 aa=password_check();
                 if (aa==1)
                 lcd_clear();
                  
                  while(aa)
                  {
                lcd_gotoxy(0,0);
                 lcd_putsf("The protect is:")  ; 
                 lcd_gotoxy(0,1);
                  lcd_putsf("1:ON 2:OFF ")  ;
                  lcd_gotoxy(0,2);
                  lcd_putsf("0:BACK ")  ;
                  
                  delay_ms(200);
                  if(PINC.7==0)
                  {delay_ms(200);
                 lcd_gotoxy(0,3); protect=1;
                 lcd_putsf("NOW IS ON ")  ; }
                   if(PIND.2==0)
                  {delay_ms(200);protect=0;
                 lcd_gotoxy(0,3);
                 lcd_putsf("NOW IS OFF")  ; }
                     if(PINC.6==0)  aa=0;ee=0;
                 }

                 }
                 //********************************************
          
          if (PIND.4==0)  cc=1;
          while(cc){ 

          lcd_gotoxy(0,0);
          lcd_putsf("0-R.1")  ;
          lcd_gotoxy(7,0);
          lcd_putsf("1-R.2")  ; 
          lcd_gotoxy(0,1);
          lcd_putsf("2-R.3")  ;
          lcd_gotoxy(7,1);
          lcd_putsf("3-R.4")  ;
           lcd_gotoxy(0,2);
            lcd_putsf("back:  4 ") ;           
          delay_ms(200);
          if (PIND.4==0)  cc=0; 
            lcd_clear();
            
             if (PINC.6==0)  dd=1;     
             
              while(dd)
              {
              delay_ms(200);   
              if (PINC.6==0) dd=0;
              lcd_gotoxy(0,0);
              lcd_putsf("R.1 SETTING b:0  ")  ;
              lcd_gotoxy(0,1);
              lcd_putsf("5.H 6.M 7.S 4.f ")  ;
              if (PIND.5==0)        
                      {
                         hour1++;
                         if (hour1==24)
                         hour1=0;
                      } 
              if (PIND.6==0)        
              {
                        minute1++;
                        if (minute1==60)
                           minute1=0;
              } 
              if (PIND.7==0)        
             {
                        second1++;
                        if (second1==60)
                           second1=0; 
             }   
              lcd_gotoxy(0,2);
             sprintf(lcd5,"s:%02u:%02u:%02u",hour1,minute1,second1);
              lcd_puts(lcd5);
              if (PIND.4==0)  f1=1;
              while(f1)  
               { 
               delay_ms(200);  
                 if (PIND.4==0)  f1=0; 
                if (PIND.5==0)  
               
                      {
                         hour1f++;
                         if (hour1f==24)
                         hour1f=0;
                      } 
              if (PIND.6==0)        
              {
                        minute1f++;
                        if (minute1f==60)
                           minute1f=0;
              } 
              if (PIND.7==0)        
             {
                        second1f++;
                        if (second1f==60)
                           second1f=0;  
                           
             }
                         
             sprintf(lcd8,"f:%02u:%02u:%02u",hour1f,minute1f,second1f);    

 
                lcd_gotoxy(0,3);
              lcd_puts(lcd8);
             }  
              lcd_putsf(" ");
               }
            //***********************************************
            if (PINC.7==0)  ee=1;     
             
              while(ee)
              {
              delay_ms(200);   
              if (PINC.7==0) ee=0;
              lcd_gotoxy(0,0);
              lcd_putsf("R.2 SETTING b:1")  ;
              lcd_gotoxy(0,1);
              lcd_putsf("5.H 6.M 7.S 4.f")  ;
              if (PIND.5==0)        
                      {
                         hour2++;
                         if (hour2==24)
                         hour2=0;
                      } 
              if (PIND.6==0)        
              {
                        minute2++;
                        if (minute2==60)
                           minute2=0;
              } 
              if (PIND.7==0)        
             {
                        second2++;
                        if (second2==60)
                           second2=0; 
             }   
             lcd_gotoxy(0,2);
             sprintf(lcd6,"s:%02u:%02u:%02u",hour2,minute2,second2);
              lcd_puts(lcd6);
              //ygty
               if (PIND.4==0)  f2=1;
              while(f2)  
               { 
               delay_ms(200);  
                 if (PIND.4==0)  f2=0; 
                if (PIND.5==0)  
               
                      {
                         hour2f++;
                         if (hour2f==24)
                         hour2f=0;
                      } 
              if (PIND.6==0)        
              {
                        minute2f++;
                        if (minute2f==60)
                           minute2f=0;
              } 
              if (PIND.7==0)        
             {
                        second2f++;
                        if (second2f==60)
                           second2f=0;  
                           
             }
                         
             sprintf(lcd9,"f:%02u:%02u:%02u",hour2f,minute2f,second2f);    

 
                lcd_gotoxy(0,3);
              lcd_puts(lcd9);
             }  
              lcd_putsf(" ");
               }
               
             //***********************************************
                         if (PIND.2==0)  ff=1;     
             
              while(ff)
              {
              delay_ms(200);   
              if (PIND.2==0) ff=0;
              lcd_gotoxy(0,0);
              lcd_putsf("R.3 SETTING b:2")  ;
              lcd_gotoxy(0,1);
              lcd_putsf("5.H 6.M 7.S 4.f")  ;
              if (PIND.5==0)        
                      {
                         hour3++;
                         if (hour3==24)
                         hour3=0;
                      } 
              if (PIND.6==0)        
              {
                        minute3++;
                        if (minute3==60)
                           minute3=0;
              } 
              if (PIND.7==0)        
             {
                        second3++;
                        if (second3==60)
                           second3=0; 
             }   
             lcd_gotoxy(0,2);
             sprintf(lcd6,"s:%02u:%02u:%02u",hour3,minute3,second3);
              lcd_puts(lcd6);  
               if (PIND.4==0)  f3=1;
              while(f3)  
               { 
               delay_ms(200);  
                 if (PIND.4==0)  f3=0; 
                if (PIND.5==0)  
               
                      {
                         hour3f++;
                         if (hour3f==24)
                         hour3f=0;
                      } 
              if (PIND.6==0)        
              {
                        minute3f++;
                        if (minute3f==60)
                           minute3f=0;
              } 
              if (PIND.7==0)        
             {
                        second3f++;
                        if (second3f==60)
                           second3f=0;  
                           
             }
                         
             sprintf(lcd9,"f:%02u:%02u:%02u",hour3f,minute3f,second3f);    

 
                lcd_gotoxy(0,3);
              lcd_puts(lcd9);
             }  
              lcd_putsf(" ");
               }
             //***************************************************
              if (PIND.3==0)  gg=1;     
             
              while(gg)
              {
              delay_ms(200);   
              if (PIND.3==0) gg=0;
              lcd_gotoxy(0,0);
              lcd_putsf("R.4 SETTING b:3")  ;
              lcd_gotoxy(0,1);
              lcd_putsf("5.H 6.M 7.S 4.f")  ;
              if (PIND.5==0)        
                      {
                         hour4++;
                         if (hour4==24)
                         hour4=0;
                      } 
              if (PIND.6==0)        
              {
                        minute4++;
                        if (minute4==60)
                           minute4=0;
              } 
              if (PIND.7==0)        
             {
                        second4++;
                        if (second4==60)
                           second4=0; 
             }   
             lcd_gotoxy(0,2);
             sprintf(lcd7,"s:%02u:%02u:%02u",hour4,minute4,second4);
              lcd_puts(lcd7);
              if (PIND.4==0)  f4=1;
              while(f4)  
               { 
               delay_ms(200);  
                 if (PIND.4==0)  f4=0; 
                if (PIND.5==0)  
               
                      {
                         hour4f++;
                         if (hour4f==24)
                         hour4f=0;
                      } 
              if (PIND.6==0)        
              {
                        minute4f++;
                        if (minute4f==60)
                           minute4f=0;
              } 
              if (PIND.7==0)        
             {
                        second4f++;
                        if (second4f==60)
                           second4f=0;  
                           
             }
                         
             sprintf(lcd10,"f:%02u:%02u:%02u",hour4f,minute4f,second4f);    

 
                lcd_gotoxy(0,3);
              lcd_puts(lcd10);
             }  
              lcd_putsf(" ");
               } 
             
             
           }}
 }
      };
}   

char password_check()
{      
        int temp=0; 
        lcd_clear();
        lcd_putsf("Enter password:");  
        lcd_gotoxy(0,1); 
        
                  
        for (i=0;i<4;i++)       
        {        
                 
                password_att[i]=keypad();
                lcd_putchar('*');  
        }    
       for (i=0;i<4;i++)       
        {   
            if (password_att[i]==password[i])
                temp++;
        } 
        if(temp<4)
        {
                lcd_clear();
                lcd_putsf("invalid password!");
                temp=0;
                delay_ms(500);
                accept=0;
                
        }
        else if(temp==4)  
         {      
                lcd_clear();
                lcd_putsf("Password accepted!");
                delay_ms(500);
                accept=1; 
          }
       
       return accept; 
       
}  

char keypad(void){ 
while(PINC.6 &&  PINC.7  && PIND.2   &&   PIND.3 &&  PIND.4  && PIND.5 &&  PIND.6 && PIND.7 );
if (PINC.6==0)    key1=0;
 if (PINC.7==0)    key1=1;  
 if (PIND.2==0)    key1=2;
 if (PIND.3==0)    key1=3; 
  if (PIND.4==0)    key1=4;
  if (PIND.5==0)    key1=5;
   if (PIND.6==0)    key1=6;
   if (PIND.7==0)    key1=7;  
 //else key1=-1;
        delay_ms(200);  
        
        return key1;  
        }
 
    void new_password(void)
{      
        int temp;      
        lable:
        temp=0;
        lcd_clear(); 
        lcd_putsf("Enter old pass:");
        lcd_gotoxy(0,1); 
        for (i=0;i<4;i++)       
        {
                password_att[i]=keypad();
                lcd_putchar('*');
        }
       for (i=0;i<4;i++)       
        {   
            if (password_att[i]==password[i])  
                temp++;
        } 
        if(temp>3)  
         {      
                lcd_clear();
                lcd_putsf("Enter new pass:"); 
                lcd_gotoxy(0,1); 
                for (i=0;i<4;i++)       
                {      
                   password[i]=keypad();
                   lcd_putchar('*');
                }
          } 
         else if(temp<4)
        {
                lcd_clear();
                lcd_putsf("invalid password!");
                temp=0;
                delay_ms(500);
                goto lable;
               
        }
}  
