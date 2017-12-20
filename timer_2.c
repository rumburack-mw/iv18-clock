#include "p33FJ128GP202.h"
#include "unit_param.h"
#include "timer_2.h"

void timer2init(void){
// Timer 2 
// Nastaveni preddelicu na 1/1
	T2CONbits.TCKPS		= 0;
// Period registers for Timer 2 									
	PR2					= 2000;//(unsigned int)((float)FCY/FPWM);
	T2CONbits.TON 		= 1;		// start Timer 2										
// A jeste povolit preruseni a nastavit priority...
//	IEC0bits.T2IE		= 1;		// enable global T2 interrupt 
//	IPC2bits.T2IP		= 3;		// interrupt priority 4	
// OC2
	OC2CONbits.OCM 		= 0b000;	// Disable Output Compare Module
	OC2CONbits.OCTSEL 	= 0;		// Timer 2
	OC2CONbits.OCM 		= 0b110;	// Pwm
	OC2R 				= 0;
	OC2RS 				= 0;

OC2R 	=	50;
OC2RS = 50;	

}