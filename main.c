#include <reg51.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
 
 sbit START = P1^0;
 sbit STOP = P1^1;
 sbit RESET = P1^2;
 
 unsigned int milliseconds = 0;
 unsigned int seconds = 0;
 unsigned int minutes = 0;
 bit stopwatch_running = 0;

 void timer0_Init(void){
	 TMOD = 0x01; //timer0 mode 1(16 - bit)
	 TH0 = 0xFC;  //load timer0 higher byte
	 TL0 = 0x66;  //load timer0 lower byte
	 ET0 = 1;     //enable timer0 interrupt
	 EA = 1;      //enable global interupt
	 TR0 = 1;     //timer0 start
 }
 
 void timer0_ISR(void) interrupt 1{
	 TH0 = 0xFC;
	 TL0 = 0x66;
	 if(stopwatch_running){
		 milliseconds++;
		 if(milliseconds >= 1000){
			 milliseconds = 0;
			 seconds++;
			 if(seconds >= 60){
				 seconds = 0;
				 minutes++;
			 }
		 }
	 }
 }

 
void display_time(){
	unsigned char time_str[16];
	sprintf(time_str, "%02u:%02u:%03u", minutes, seconds, milliseconds);
	lcd_gotoxy(0,1);
	lcd_string(time_str);
}

void delay_ms(unsigned int ms){
	unsigned int i,j;
	for(i = 0; i < ms; i++){
		for(j = 0; j < 127; j++);
	}
}

void main(void)
{ 
	 LCD_Init();
	 timer0_Init();
   while(1)
   {
		 
		 if(START == 0){
			 delay_ms(20);
			 if(START == 0){
				 stopwatch_running = 1;
			 }
			 while(START == 0);
		 }
		 if(STOP == 0){
			 delay_ms(20);
			 if(STOP == 0){
				 stopwatch_running = 0;
			 }
			 while(STOP == 0);
		 }
		 if(RESET == 0){
			 delay_ms(20);
			 if(RESET == 0){
				 milliseconds = 0;
				 seconds = 0;
				 minutes = 0;
				 stopwatch_running = 0;
				 display_time();
			 }
			 while(RESET == 0);
		 }
		 display_time();
		 delay_ms(100);
   }
}