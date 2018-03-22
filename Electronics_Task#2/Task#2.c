/*------------------------------------------------------------------------------
HELLO.C

Copyright 1995-2005 Keil Software, Inc.
------------------------------------------------------------------------------*/

#include <C8051F020.h>
#include <stdio.h>

int  delay;
int current;
unsigned char Sev_Segment[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};

void Delay_Ms(unsigned int itime)
{
	int i,j;

	for (i=0;i<itime;i++) 				
	{
		for (j=0;j<1275;j++);
	}
}
void WTC_Disabled()
{
	WDTCN = 0xde;						//disable watchdog timer
  WDTCN = 0xad;
}
void interrupt_init()
{
	XBR0    = 0x04;
	XBR1    = 0x14;						//INT1 and INT0 routed to Port pin
	XBR2    = 0x40;            //Enable crossbar and weak pull-ups
	EA      = 1;               //Enable All
	EX0     = 1;  						//Enable External Interrupt0
	EX1     = 1;							//Enable External Interrupt1
	IT0     = 1;							//choose falling edge
	IT1     = 0;
}

void init_port()
{22
	P74OUT 	= 0x08;
	P1MDOUT = 0xff;	
	P5 		= 0x01; 

}

void increment()
{
	for(current=0;current<=9;current++)
	{
		P1 = Sev_Segment[current];
		if ((P5&0x01) == 0x00) 
		{
			delay = 50 ;
		}
		else if ((P5&0x01) == 0x01)
		{
			delay = 150;
		}

		Delay_Ms(delay);

		if(current == 9)
		{
			current =-1;
		}
		
		
	}
}
void decrement()
{
	for(;current>=0;current--)
	{
		P1 = Sev_Segment[current];
		if(current !=0)
		{
			if ((P5&0x01) == 0x00) 
		{
			delay = 50 ;
		}
		else if ((P5&0x01) == 0x01)
		{
			delay = 150;
		}
			Delay_Ms(delay);
		}
	}
}

void INT0_ (void) interrupt 0		//interrupt 0 action
{

	P5 |= 0x10;
	P5 |= 0x20;
	P5 |=0x40;
	Delay_Ms(600);
	P5 &= 0x0f;
	decrement();
	  
	
}


void main(void)
{
 	WTC_Disabled();
	interrupt_init();
	init_port();

	while(1)
	{
		increment();
		
	}

}