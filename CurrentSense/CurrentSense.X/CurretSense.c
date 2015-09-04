#include <xc.h>        /* XC8 General Include File */

//==========================================================================
//  Configuration bits
//==========================================================================
// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)
// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting)
#pragma config VREGEN = ON      // USB Voltage Regulator Enable bit (USB voltage regulator enabled)
// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)
// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)
// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)
// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)
// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)
// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)
// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

#define _XTAL_FREQ      48000000                //CPU use 96MHZ/ 2 = 48MHz

#define REALTIME	0
#define MAX		1

#define LED	     	LATBbits.LATB1		//LED on SK28A is connected to RB1
#define	SW1		PORTBbits.RB0		//Push button labeled as SW1 is connected to RB0

#define LCD_DB7		LATBbits.LATB7		//LCD data pin 7
#define LCD_DB6		LATBbits.LATB6		//LCD data pin 6
#define LCD_DB5		LATBbits.LATB5		//LCD data pin 5
#define LCD_DB4		LATBbits.LATB4		//LCD data pin 4
#define LCD_DATA	LATB
#define LCD_RS   	LATBbits.LATB2		//LCD Register Select pin is connected to RB2 on SK28A
#define LCD_E   	LATBbits.LATB3		//LCD Enable pin is connected to RB3 on SK28A

#define	Control1	LATCbits.LATC0
#define	Control2	LATCbits.LATC1
#define	Control3	LATCbits.LATC2
#define SSbit0		LATAbits.LATA4
#define SSbit1		LATAbits.LATA1
#define SSbit2		LATAbits.LATA2
#define SSbit3		LATAbits.LATA3

#define Vref 5.04

void lcd_init(void);
void lcd_4bit_write(unsigned char data);
void lcd_config(unsigned char command);
void lcd_putchar(unsigned char data);
void lcd_putstr(char *str);
void lcd_clear(void);
void lcd_home(void);
void lcd_set_cursor(unsigned char uc_column, unsigned char uc_row);	//uc_column is 0 for first character, uc_row is 0 for 1st line
void lcd_goto(unsigned char address);		// move cursor with the address according to datasheet of LCD
void lcd_e_clock(void);
void lcd_bcd(unsigned char uc_digit, unsigned int ui_number);

void delay_ms(unsigned int ui_data);		//delay in millisecond, maximum value is 65,535; 0 will result in 65536 millisecond of delay
void delay_us(unsigned char uc_data);	// delay in microsecond, maximum value is 255; 0 will result in 256 microsecond of delay

void bcd(unsigned char uc_digit, unsigned int ui_number);

int adc_run();

void HighPriorityISRCode();					//interrupt function prototype
void LowPriorityISRCode();

char selection = REALTIME;
int maximum = 0, i, j, incrementValue = 8, counter, centerValue;

char firstLine1[25]  = {"Mode = Real Time Value   "};
char firstLine2[25]  = {"Mode = Maximum Value     "};
char secondLine[25]  = {"Press SW1 to change Mode "};

float value = 0, valueans = 0;
//===============================================================================
//	Main Program
//===============================================================================
void main()
{
	// I/O initialize Start
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	TRISA = 0b00000001;		//RA0 as input
	TRISB = 0b00000001;		//SW1 as input
	TRISC = 0b00000000;
	// I/O initialize End

	//Comparator initialize start
	CM0 = 1;				//Turn off comparator
	CM1 = 1;
	CM2 = 1;
	//Comparator initialize end

	//ADC initialize start
	VCFG1 = 0;				//Vref VSS VDD
	VCFG0 = 0;
	PCFG0 = 0;				//Set RA0 as anolog input
	PCFG1 = 1;
	PCFG2 = 1;
	PCFG3 = 1;
	CHS0 = 0;				//AN0 selected
	CHS1 = 0;
	CHS2 = 0;
	CHS3 = 0;
	ADFM = 1;				//Right justified result
	ADCS0 = 1;				//Fosc/16
	ADCS1 = 0;
	ADCS0 = 1;
	ADON = 1;				//AD Module ON
	//ADC initialize end

	lcd_init();
	lcd_clear();
	lcd_home();
	lcd_putstr(" Cytron ");
	delay_ms(1000);
	lcd_goto(0x40);
	lcd_putstr("AmpMeter");
	lcd_clear();

        //Find Center Value Start
        lcd_goto(0x00);
	lcd_putstr("Ctr=    ");
        lcd_goto(0x40);
	lcd_putstr("PressSW1");
        while(1)
        {
            value = 0;
            for(i = 0;i < 256;i++)
            {
                value = value + (float)adc_run();
            }
            value = value /256.0;
            lcd_goto(0x05);
            lcd_bcd(3,value);
            if(SW1==0)  break;
        }
        lcd_clear();
        centerValue = value;
        delay_ms(500);
        //Find Center Value End

	while(1)
	{
		if(SW1 == 0){	//SW1 press
			while(SW1 == 0);	//Wait until SW1 release
			if(selection == REALTIME){
				selection = MAX;
				LED = 1;}
			else if(selection == MAX){
				selection = REALTIME;
				LED = 0;}}

		if(counter == 5){
			counter = 0;
			lcd_goto(0x00);
			for(i=incrementValue-8;i<incrementValue;i++){
				if(selection == REALTIME)	lcd_putchar(firstLine1[i]);
				else if(selection == MAX)	lcd_putchar(firstLine2[i]);}
			lcd_goto(0x40);
			for(i=incrementValue-8;i<incrementValue;i++){
				lcd_putchar(secondLine[i]);}
			if(incrementValue < 25)	incrementValue++;
			else if(incrementValue == 25)	incrementValue = 8;}
		else	counter++;               

                value = 0;
                for(i = 0;i < 256;i++)
                {
                    value = value + (float)adc_run();
                }
                value = value /256.0;

		if(value > centerValue){
			valueans = value-centerValue;
			valueans = ((valueans * (Vref/1023.0)) / 0.04);}	//calculation from the ADC value to change it to AMP
		else if(value < centerValue){
			valueans = centerValue-value;
			valueans = ((valueans * (Vref/1023.0)) / 0.04);}	//calculation from the ADC value to change it to AMP
		else	valueans = 0;

		if(valueans > maximum) maximum = valueans;

		if(selection == REALTIME)	bcd(3,valueans);
		else if(selection == MAX)	bcd(3,maximum);

		delay_ms(100);
	}
}

//===============================================================================
//	Functions
//===============================================================================
//4-bit mode configuration
//4-bit mode configuration
void lcd_init()
{
	delay_ms(30);	//wait for 30ms after power ON for LCD internal controller to initialize itself
	LCD_E = 1;
	//Set lcd to configuration mode
	LCD_RS = 0;		//Selected command register
	delay_us(5);	//macro from HITECH compiler to generate code to delay for 1 microsecond base on _XTAL_FREQ value

	LCD_DATA = (LCD_DATA & 0x0F) | 0b00110000;	//make it in 8-bit mode first, for 3 times
	lcd_e_clock();
   	delay_ms(2);
   	LCD_DATA = (LCD_DATA & 0x0F) | 0b00110000;	//make it in 8-bit mode first, for 3 times
	lcd_e_clock();
   	delay_ms(2);
   	LCD_DATA = (LCD_DATA & 0x0F) | 0b00110000;	//make it in 8-bit mode first, for 3 times
	lcd_e_clock();
   	delay_ms(2);

   	LCD_DATA = (LCD_DATA & 0x0F) | 0b00100000;	//make it in 4-bit mode
	lcd_e_clock();
   	delay_ms(2);

	//start sending command in 4 bit mode
   	//Function Set
   	lcd_config(0b00101000);	 //0b 0 0 1 ID N F X X
   							//Interface Data Length, ID= 4-bit
   							//Number of line to display, N = 1 is 2 line display, N = 0 is 1 line display
   							//Display Font, F = 0 is 5x 8 dots, F = 1 is 5 x 11 dots

	//Command Entry Mode
	lcd_config(0b00000110);	//0b 0 0 0 0 0 1 ID SH
							//ID  = 1, cursor automatic move to right, increase by 1
   							//SH = 0,  shift of entire display is not perform

	//Display Control
	lcd_config(0b00001100);	//0b 0 0 0 0 1 D C B
							//D  = 1, Display is ON
   							//C = 0,  Cursor is not display
   							//B = 0. Cursor does not blink

	lcd_clear();	//clear LCD and move the cursor back to home position
}

//Routine to send data to LCD via 2 nibbles in 4-bit mode
void lcd_4bit_write(unsigned char data)
{
	LCD_DATA = (LCD_DATA & 0x0F) | (data & 0xF0);	//send out the Most Significant Nibble
	lcd_e_clock();

	LCD_DATA = (LCD_DATA & 0x0F) | (data << 4); //send out the Least Significant Nibble
	lcd_e_clock();
}

//Routine to send command to LCD
void lcd_config(unsigned char command)
{
    LCD_RS = 0;        			//Selected command register
    delay_us(5);
    lcd_4bit_write(command);	//Send command via 2 nibbles
    delay_ms(1);
}

//Routine to send display data (single character) to LCD
void lcd_putchar(unsigned char data)
{
    LCD_RS = 1;        			//Selected data register
    delay_us(5);
    lcd_4bit_write(data);		//Send display via 2 nibbles
    delay_ms(1);
}

//Routine to send string to LCD
void lcd_putstr(char *str)
{
	while(*str != '\0')		//loop till string ends
	{
     	lcd_putchar(*str++);  		//send characters to LCD one by one
	}
}

//Routine to clear the LCD
void lcd_clear(void)
{
	lcd_config(0x01);			//command to clear LCD
	delay_ms(1);
}
//function to move LCD cursor to home position
void lcd_home(void)
{
	lcd_config(0x02);			//command to move cursor to home position
  	delay_ms(1);
}
//Rountine to set cursor to the desired position base on coordinate, column and row
/*Place a string in the specified row and column of the screen.
* +--+--+--+--+--+---------------------+
* |0 |1 |2 |3 |4 |5 ...etc             | <- row 0
* +--+--+--+--+--+---------------------+
* |0 |1 |2 |3 |4 |5 ...etc             | <- row 1
* +--+--+--+--+--+---------------------+
*/
void lcd_set_cursor(unsigned char uc_column, unsigned char uc_row)
{
	if(uc_row == 0) lcd_config(0x80 + uc_column);	//command to move cursor to first row/line with offset of column
	else if(uc_row ==1 ) lcd_config(0xC0 + uc_column);	//command to move cursor to 2nd row/line with offset of column
}

//Rountine to set cursor to the desired position base on LCD DDRAM address
/*Place a string in the specified row and column of the screen.
* +--+--+--+--+--+---------------------+
* |0x00 |0x01 |0x02 |0x03 |0x04 |0x05  ...etc          |0x0F| <- 1st line
* +--+--+--+--+--+---------------------+
* |0x40 |0x41 |0x42 |0x43 |0x44 |0x45 ...etc           |0x4F| <- 2nd line
* +--+--+--+--+--+---------------------+
*/
void lcd_goto(unsigned char address)
{
	 lcd_config(0x80 + address);	//command to move cursor to desire position base on the LCD DDRAM address
}

//function to output enable clock pulse to LCD
void lcd_e_clock(void)
{
	delay_us(10);
	LCD_E = 0;	//create a falling edge for Enable pin of LCD to process data
	delay_us(100);
	LCD_E = 1;	//pull the Enable pin high again
	delay_us(100);
}

void lcd_bcd(unsigned char uc_digit, unsigned int ui_number)
{
	unsigned int ui_decimal[5] ={ 0 };
	//extract 5 single digit from ui_number
		ui_decimal[4] = ui_number/10000;	// obtain the largest single digit, digit4
		ui_decimal[3] = ui_number%10000;	// obtain the remainder
		ui_decimal[2] = ui_decimal[3]%1000;
		ui_decimal[3] = ui_decimal[3]/1000;			// obtain the 2nd largest single digit, digit3
		ui_decimal[1] = ui_decimal[2]%100;
		ui_decimal[2] = ui_decimal[2]/100;			// obtain the 3rd largest single digit, digit2
		ui_decimal[0] = ui_decimal[1]%10;			// obtain the smallest single digit, digit0
		ui_decimal[1] = ui_decimal[1]/10;			// obtain the 4th largest single digit, digit1

		if (uc_digit > 5) uc_digit = 5;			// limit to 5 digits only
		for( ; uc_digit > 0; uc_digit--)
		{
			lcd_putchar(ui_decimal[uc_digit - 1] + 0x30);
		}
}

//Simple delay function
// delay in milli second, maximum value for ui_data is 65,535.
void delay_ms(unsigned int ui_data)
{
	for(;ui_data > 0; ui_data--)
	{
            __delay_ms(1);
	}
}

// delay in milli second, maximum value for ui_data is 65,535.
void delay_us(unsigned char uc_data)
{
	for(;uc_data > 0; uc_data--)
	{
            __delay_us(1);
	}
}

void bcd(unsigned char uc_digit, unsigned int ui_number)
{
	unsigned int ui_decimal[5] ={ 0 }, value = 0;
	//extract 5 single digit from ui_number
	ui_decimal[4] = ui_number/10000;	// obtain the largest single digit, digit4
	ui_decimal[3] = ui_number%10000;	// obtain the remainder
	ui_decimal[2] = ui_decimal[3]%1000;
	ui_decimal[3] = ui_decimal[3]/1000;			// obtain the 2nd largest single digit, digit3
	ui_decimal[1] = ui_decimal[2]%100;
	ui_decimal[2] = ui_decimal[2]/100;			// obtain the 3rd largest single digit, digit2
	ui_decimal[0] = ui_decimal[1]%10;			// obtain the smallest single digit, digit0
	ui_decimal[1] = ui_decimal[1]/10;			// obtain the 4th largest single digit, digit1

	if (uc_digit > 5) uc_digit = 5;			// limit to 5 digits only
	for( ; uc_digit > 0; uc_digit--)
	{
		value = ui_decimal[uc_digit - 1];
		switch(value)
		{
			case 0:
				SSbit0 = 0;
				SSbit1 = 0;
				SSbit2 = 0;
				SSbit3 = 0;
				break;
			case 1:
				SSbit0 = 1;
				SSbit1 = 0;
				SSbit2 = 0;
				SSbit3 = 0;
				break;
			case 2:
				SSbit0 = 0;
				SSbit1 = 1;
				SSbit2 = 0;
				SSbit3 = 0;
				break;
			case 3:
				SSbit0 = 1;
				SSbit1 = 1;
				SSbit2 = 0;
				SSbit3 = 0;
				break;
			case 4:
				SSbit0 = 0;
				SSbit1 = 0;
				SSbit2 = 1;
				SSbit3 = 0;
				break;
			case 5:
				SSbit0 = 1;
				SSbit1 = 0;
				SSbit2 = 1;
				SSbit3 = 0;
				break;
			case 6:
				SSbit0 = 0;
				SSbit1 = 1;
				SSbit2 = 1;
				SSbit3 = 0;
				break;
			case 7:
				SSbit0 = 1;
				SSbit1 = 1;
				SSbit2 = 1;
				SSbit3 = 0;
				break;
			case 8:
				SSbit0 = 0;
				SSbit1 = 0;
				SSbit2 = 0;
				SSbit3 = 1;
				break;
			case 9:
				SSbit0 = 1;
				SSbit1 = 0;
				SSbit2 = 0;
				SSbit3 = 1;
				break;
		}

		if(uc_digit == 3)
		{
			Control1 = 0;
			Control1 = 1;
		}
		else if(uc_digit == 2)
		{
			Control2 = 0;
			Control2 = 1;
		}
		else if(uc_digit == 1)
		{
			Control3 = 0;
			Control3 = 1;
		}
	}
}

int adc_run()
{
	GODONE = 1;
	while(GODONE == 1);
	return ( (ADRESH<<8) | ADRESL );
}

#pragma interrupt HighPriorityISRCode
void HighPriorityISRCode()
{

}
#pragma interruptlow LowPriorityISRCode
void LowPriorityISRCode()
{

}
