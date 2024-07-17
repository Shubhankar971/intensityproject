/*
 * BLUETOOTH.c
 *
 * Created: 15-01-2021 16:54:07
 * Author : Dell
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#define BAUD_PRESCALE (((F_CPU/(BAUDRATE *16UL)))-1)
#define LED PORTB
#define MOTOR PORTA
void USART_Init(unsigned long);
char USART_Rxchar();
void USART_Txchar(char);
void USART_sendstring(char*);

int main(void)
{
  char Data_in;
  DDRB=0XFF;
  DDRA=0XFF;
  USART_Init(9600);
  LED=0;
  MOTOR=0;  /* Replace with your application code */
    while (1) 
    {
		Data_in=USART_Rxchar();
		if(Data_in=='1')
		{
			LED|=(1<<PB0);
			USART_sendstring("LED_ON");
    }
	else if (Data_in=='2')
	{
		MOTOR|=(1<<PA0);
		USART_sendstring("MOTOR_ON");
	}
	else if (Data_in=='3')
	{
		LED|=(1<<PB1);
		USART_sendstring("LED_ON");
	}
	else if (Data_in=='4')
	{
		LED&=~((1<<PB0)|(1<<PB1));
		USART_sendstring("LED_OFF");	
	}
	else if(Data_in=='5')
	{
		MOTOR&=~(1<<PA0);
		USART_sendstring("MOTOR_OFF");
	}
	else
	USART_sendstring("SELECT PROPER OPTION");
}
return 0;
}
void USART_Init(unsigned long BAUDRATE)
{
	UCSRB|=(1<<RXEN)|(1<<TXEN);
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UBRRL=BAUD_PRESCALE;
	UBRRH=(BAUD_PRESCALE>>8);
}
char USART_Rxchar()
{
	while(!(UCSRA&(1<<RXC)));
	return(UDR);
}
void USART_Txchar(char data)
{
	UDR=data;
	while(!(UCSRA&(1<<UDRE)));
}
void USART_sendstring(char*str)
{
	int i=0;
	while (str[i]!=0)
	{
		USART_Txchar(str[i]);
		i++;
	}
}