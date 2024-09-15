//sfr lcd_Port=0xA0; // port 2
#define lcd_Port P2
sbit rs=P2^0;
sbit en=P2^1;

void delay(unsigned int);
void lcd_Command(char);
void lcd_data(char);
void lcd_String(char *str);
void lcd_getoxy(unsigned char, unsigned char);
void LCD_Init(void);
 
void delay(unsigned int count)
{
   int i,j;
   for(i=0;i<count;i++)
   {
      for(j=0;j<922;j++); //provides us a delay of 1ms
   }
}
 
void lcd_Command(char cmd)
{
   lcd_Port=(lcd_Port&0x0F) | (cmd&0xF0); //Sending in your higher nibble
	 rs=0;
   en=1;
   delay(1);
   en=0;
   delay(1);
   lcd_Port=(lcd_Port&0x0F) | (cmd<<4); // sending in your lower nibble
   en=1;
   delay(1);
   en=0;
   delay(1);
}

 
void lcd_data(char cmd)
{
   lcd_Port=(lcd_Port&0x0F) | (cmd&0xF0);
   rs=1;
   en=1;
   delay(1);
   en=0;
   delay(1);
   lcd_Port=(lcd_Port&0x0F) | (cmd<<4);
   en=1;
   delay(1);
   en=0;
   delay(1);
}
 
void lcd_string(char *str)
{
   int i;
   for(i=0;str[i]!=0;i++)
   {
      lcd_data(str[i]);
   }
}

void lcd_gotoxy(unsigned char x, unsigned char y){
	if(y == 1){
		lcd_Command(0x80 + x);
	}
	else if(y == 2){
		lcd_Command(0xC0 + x);
	}
}

void LCD_Init()
{
	 rs=0;
	 en=0;
   delay(20);
   lcd_Command(0x02); //Return Home
   lcd_Command(0x28); //Sets 4 bit Mode
   lcd_Command(0x0C); //Display control
   lcd_Command(0x06); //Entry Mode
   lcd_Command(0x01); //Clear display
   lcd_Command(0x80); //DDRAM
	 delay(2);
}