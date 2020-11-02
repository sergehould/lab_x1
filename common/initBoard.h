/**********************************************************************
* File name: initBoard.h
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
#ifndef INITBOARD_H
#define INITBOARD_H
#include <xc.h>
#define _XTAL_FREQ 8000000	// For _delay()
/******Function prototypes	******/
void initOscillator(void);
void initIO(void);
#endif