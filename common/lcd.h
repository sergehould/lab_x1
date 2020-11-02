/**********************************************************************
* File name: lcd.h
* 
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      		Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Serge Hould		9 June 2017		8 bit LCD lib for LAB-X1 board
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
*
**********************************************************************/
#ifndef LCD_H
#define LCD_H
#define _XTAL_FREQ 4000000

/******	LCD FUNCTION PROTOYPES ******/

//void Init_LCD( void );		        // initialize display
void LCDInit(void);
void lcd_cmd( char cmd );	        // write command to lcd
void lcd_data( char data );		    // write data to lcd
void LCDClear(void);
void LCDPut(char A);
void LCDPos(char pos);
void LCDL2Home(void);
void LCDL1Home(void);



/*****	LCD COMMAND FUCNTION PROTOTYPES  *****/
#define cursor_right()  lcd_cmd( 0x14 )
#define cursor_left()   lcd_cmd( 0x10 )
#define display_shift() lcd_cmd( 0x1C )
#define home_clr()      lcd_cmd( 0x01 ) 
#define home_it()       lcd_cmd( 0x02 ) 
#define line_2()        lcd_cmd( 0xC0 ) // (0xC0)

#endif