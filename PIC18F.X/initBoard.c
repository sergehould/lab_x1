/**********************************************************************
* File name: initBoard.c
* 
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author            Date      		Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Serge Hould		22 March 2018		
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
*
**********************************************************************/

#include "../common/initBoard.h"

// CONFIG1
//#pragma config OSC = RC
#pragma config OSC = INTIO67    // internal oscillator block
#pragma config WDT = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRT = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config EBTRB = OFF //Boot Block Table Read Protection bit
//#pragma config CP0 = OFF         // Code Protection bit (Program memory code protection is disabled)
//#pragma config CP1 = OFF         // Code Protection bit (Program memory code protection is disabled)
//#pragma config CP2 = OFF         // Code Protection bit (Program memory code protection is disabled)
//#pragma config CP3 = OFF         // Code Protection bit (Program memory code protection is disabled)
//#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown Out Reset Selection bits (BOR diabled)
#pragma config IESO = OFF       //Internal/External Oscillator Switchover bit
#pragma config PBADEN = OFF  //PORTB<4:0> pins are configured as digital I/O on Reset
#pragma config FCMEN = OFF      //	Fail-Safe Clock Monitor Enable bit
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
//#pragma config BORV = 4   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRTC = OFF        //

/***************************************************************
Name:	void initOscillator(void)
Description: Initializes the oscillator.  Must be called at boot time.

****************************************************************/
void initOscillator(void){
    //IRCF2:IRCF0: Internal Oscillator Frequency Select bits to 8MHz
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
}

/***************************************************************
Name:	void initIO(void)
Description: Initializes port SFRs

****************************************************************/
void initIO(void){
    TRISD = 0x00;
    //ANSEL = 0x00;   // Disable ALL Analog ports
}