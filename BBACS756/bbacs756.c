/*******************************************************************************
* This file provides the functions for the RFID Sample code

* Author: ANG JIA YI @ Cytron Technologies Sdn. Bhd.
*******************************************************************************/
// This file is written for PIC16F877A, if other model of PIC is uses, please modify accordingly


#include <P18F2550.h>
#include "lcd.h"		
/*******************************************************************************
* DEVICE CONFIGURATION WORDS                                                   *
*******************************************************************************/
#pragma config LVP=OFF
#pragma config PBADEN=OFF
#pragma config WDT=OFF
#pragma config FOSC=HS
#pragma config MCLRE=ON

//		 WDTDIS &		// Disable Watchdog Timer.
//		 PWRTEN &		// Enable Power Up Timer.
//		 BORDIS &		// Disable Brown Out Reset.
//		 LVPDIS);		// Disable Low Voltage Programming.

/*******************************************************************************
* Defination of label		                                                  *
*******************************************************************************/

						
/*******************************************************************************
* PRIVATE FUNCTION PROTOTYPES                                                  *
*******************************************************************************/
void adc_initialize(void);
void delay_ms(unsigned int num);
/*******************************************************************************
* Global Variables                                                             *
*******************************************************************************/

/*******************************************************************************
* MAIN FUNCTION                                                                *
*******************************************************************************/
int main()
{
	unsigned int value = 0;	// declare a variable to store 
	unsigned int valueans = 0;	// declare a variable to store 
	// ensure all the hardware port in zero initially
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;

	// Initialize the I/O port direction, this must be configured according to circuit
	TRISA = 0b00000001;
	TRISB = 0b00000001;
	TRISC = 0b10010011;

	
	//Initialize lcd to be use
	lcd_init();
	
	//Initialize adc to be use
	adc_initialize();
	
	ADCON0bits.ADON=1;
	
	while(1) 	// create an infinite loop
	{
		ADCON0bits.GO=1;				//start the ADC system
		while(ADCON0bits.DONE==1);		//wait for it to done convertion
		value = ADRESH ;				//take the high value to kept
		value=value << 8;				//put it to high set of value
		value = (value | ADRESL);		//add the lower value to it
		if(value > 510)
		{
			valueans = value-510;
			valueans = valueans *125;		//calculation from the ADC value to change it to AMP
			lcd_goto(0x80);
			lcd_bcd(5,valueans);  	//turn the ADC value to AMP and display
		}	
		else if(value < 510)
		{
			valueans = 510-value;
			valueans = valueans *125;	//calculation from the ADC value to change it to AMP
			lcd_goto(0x80);
			lcd_bcd(5,valueans);		//turn the ADC value to AMP and display
		}
		else
		{
		lcd_goto(0x80);
		lcd_bcd(5,0);	
		}	
			
	}	
		while(1) continue;	// infinite loop to prevent PIC from reset if there is no more program	
}

/*******************************************************************************
* PRIVATE FUNCTION: delay_ms
*
* PARAMETERS:
* ~ ui_value	- The period for the delay in miliseconds.
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Delay in miliseconds.
*
*******************************************************************************/

/*******************************************************************************
* PRIVATE FUNCTION: beep
*
* PARAMETERS:
* ~ uc_count	- How many times we want to beep.
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Beep for the specified number of times.
*
*******************************************************************************/

void delay_ms(unsigned int num)
{
	unsigned int lop,i1,j1;
	for(lop=0;lop<=num;lop++)
	{
	for(i1=0;i1<200;i1++)
		for(j1=0;j1<25;j1++);	
	}	
}	

void adc_initialize(void)
{
	ADCON1=0b00001110;
	ADCON2=0b10101010;
	ADCON0=0b00000000;	
}	

