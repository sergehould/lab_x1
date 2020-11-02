/**********************************************************************
* File name: lcd.c
* 
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      		Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Serge Hould		9 June 2017		v1.0 8-bit LCD lib for LAB-X1 board
*                   22 March 2018   v1.1 Clean up 
* 					9 April 2018	v1.2 Replace the legacy delays.h 
* 										(_delay(), __delay_ms(), __delay_us() APIs)
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*
*
**********************************************************************/
#include <xc.h>
#include "lcd.h"
//#include <delays.h> //Legacy only

/* 
	For Lab-X1 board, here are the data and control signal definitions
	RS -> RE0
	E  -> RE1
	RW -> RE2
	DATA -> RD0 - RD7   
*/

// Control signal data pins 
#define  RW  LATEbits.LATE2       // LCD R/W signal
#define  RS  LATEbits.LATE0      // LCD RS signal
#define  E   LATEbits.LATE1       // LCD E signal 


// Control signal pin direction 
#define  RW_TRIS	TRISEbits.TRISE2
#define  RS_TRIS	TRISEbits.TRISE0
#define  E_TRIS		TRISEbits.TRISE1


// Data signals and pin direction
#define  DATA      LATD           // Port for LCD data
#define  DATAPORT  PORTD
#define  TRISDATA  TRISD          // I/O setup for data Port


/***************************************************************
Name:	void LCDInit(void)
Description: Initializes the LCD.  Must be called at boot time.

****************************************************************/
void LCDInit( void )             // initialize LCD display
{
	// 15mS delay after Vdd reaches nnVdc before proceeding with LCD initialization
	// not always required and is based on system Vdd rise rate
	__delay_ms(15);
   // Delay1KTCYx(30); // For 8 MHz clock: Delay = 0.5 uS * 30 * 1000
			
	/* set initial states for the data and control pins */
	DATA &= 0x00;	
    RW = 0;                       // R/W state set low
	RS = 0;                       // RS state set low
	E = 0;                        // E state set low

	/* set data and control pins to outputs */
	TRISD &= 0x00;
 	RW_TRIS = 0;                  // RW pin set as output
	RS_TRIS = 0;                  // RS pin set as output
	E_TRIS = 0;                   // E pin set as output

	/* 1st LCD initialization sequence */
	DATA &= 0x00;
    DATA |= 0x38;
    E = 1;	
    Nop();
    Nop();
    Nop();
    E = 0;                        // toggle E signal
   	/* 5ms delay */
    __delay_ms(5);
	//Delay1KTCYx(10); // For 8 MHz clock: Delay = 0.5 uS * 10 * 1000
      
	/* 2nd LCD initialization sequence */
	DATA &= 0x00;
    DATA |= 0x38;
    E = 1;	
    Nop();
    Nop();
    Nop();	
    E = 0;                        // toggle E signal
    /* 200uS delay */
    __delay_us(200);
    // Delay10TCYx(40);	// Delay = 0.5 * 40 * 10

	/* 3rd LCD initialization sequence */
	DATA &= 0x00;
    DATA |= 0x38;
    E = 1;		
    Nop();
    Nop();
    Nop();	
    E = 0;                        // toggle E signal
    /* 200uS delay */
    __delay_us(200);
   //  Delay10TCYx(40);	// Delay = 0.5 * 40 * 10

    lcd_cmd( 0x38 );              // function set
    lcd_cmd( 0x0C );              // Display on/off control, cursor blink off (0x0C)
    lcd_cmd( 0x06 );			  // entry mode set (0x06)
}

/***************************************************************
Name:	void LCDClear(void)
Description: Clears the whole LCD

****************************************************************/
void LCDClear(void)
{
    lcd_cmd(0x01 );

}


void lcd_cmd( char cmd )          // subroutiune for lcd commands
{
//	TRISD &= 0xFF00;              // ensure RD0 - RD7 are outputs
	DATA &= 0x00;               // prepare RB0-RB7
    DATA |= cmd;                  // command byte to lcd
	RW = 0;                       // ensure RW is 0
    RS = 0;
    E = 1;                        // toggle E line
    Nop();
    Nop();
    Nop();
    E = 0;
   	/* 5ms delay */
    __delay_ms(5);
//	Delay1KTCYx(10); // For 8 MHz clock: Delay = 0.5 uS * 10 * 1000
}

void lcd_data( char data )        // subroutine for lcd data
{
//	TRISD &= 0xFF00;              // ensure RD0 - RD7 are outputs
	RW = 0;       				 // ensure RW is 0
    RS = 1;                       // assert register select to 1
	DATA &= 0x00;               // prepare RD0 - RD7
    DATA |= data;                 // data byte to lcd
    E = 1;				
 	Nop();
    Nop();
    Nop();
    E = 0;                       // toggle E signal
    RS = 0;                      // negate register select to 0
    /* 400uS delay */
    __delay_us(400);
   //  Delay10TCYx(10);	// Delay = 0.5 * 80 * 10
}


/***************************************************************
Name:	void LCDPut(char A)
Description: Put a character at the current position.

****************************************************************/
void LCDPut(char A)
{
        lcd_data(A);
}


/***************************************************************
Name:	void LCDPos(char pos)
Description: Position the cursor to a specific position.
The position can be anywhere between 0 and 31.
Line1: position 0 to 19
Line2: position 20 to 39

****************************************************************/
void LCDPos(char pos)
{
    __delay_us(12);
    //Delay100TCYx(1);//Wait for some time to let the LCD process it
      if(pos<20) lcd_cmd(0x80+pos);//Bring cursor to line 1
      else  lcd_cmd(0xC0+pos-20);//Bring cursor to line 1
    __delay_us(12);
     // Delay100TCYx(1);//Wait for some time to let the LCD process it
}

/***************************************************************
Name:	void LCDL1Home(void)
Description: Sets the position home on line1

****************************************************************/
void LCDL1Home(void)
{
    __delay_us(12);  
//    Delay100TCYx(1);//Wait for some time to let the LCD process it
      lcd_cmd(0x80);//Bring cursor to line 1
      __delay_us(12);
     // Delay100TCYx(1);//Wait for some time to let the LCD process it
}

/***************************************************************
Name:	void LCDL2Home(void)
Description: Sets the position home on line2

****************************************************************/
void LCDL2Home(void)
{
      __delay_us(12);
     // Delay100TCYx(1);//Wait for some time to let the LCD process it
      lcd_cmd(0xC0);//Bring cursor to line 1
      __delay_us(12);
    //  Delay100TCYx(1);//Wait for some time to let the LCD process it
}

