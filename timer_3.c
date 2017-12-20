#include "p33FJ128GP202.h"
#include "unit_param.h"
#include "timer_3.h"


int volatile 		Blik_1ms; 
long int volatile 	sw_timer0;
long int volatile 	sw_timer1;
long int volatile 	sw_timer2;
long int volatile 	sw_timer3;

long int volatile DisplayMapToSend, DisplayMapTmp, SegmentBright;
int volatile Max6921BitCounter;


t_Max6921_State volatile Max6921_State;

int volatile Diplay[NO_OF_SEGMENTS];	// Cislice
int volatile Bright[NO_OF_SEGMENTS];	// Zvyrazneni	
int volatile Anode_Pointer, Number;

void MakeDisplay(void);

void timer3init(void){
// Timer 3 
// Nastaveni preddelicu na 1/1
	T3CONbits.TCKPS		= 0;
// Period registers for Timer 3 									
	PR3= 200;//(unsigned int)((float)FCY/FPWM);
	T3CONbits.TON 		= 1;		// start Timer 3										
// A jeste povolit preruseni a nastavit priority...
	IEC0bits.T3IE		= 1;		// enable global T3 interrupt 
	IPC2bits.T3IP		= 3;		// interrupt priority 4	

	Max6921_State 		= MAX6921_RESET;
}


void __attribute__((__interrupt__,auto_psv)) _T3Interrupt (void){
	IFS0bits.T3IF = 0;  							// interrupt acknowledge      

// Blikaci bit
	Blik_1ms ^= 1;

// SW Timery
	if(sw_timer0) sw_timer0--;
	if(sw_timer1) sw_timer1--;
	if(sw_timer2) sw_timer2--;
	if(sw_timer3) sw_timer3--;

// Komunikace s MAXem

	switch(Max6921_State){
		case MAX6921_RESET:	// Reset MAX6921
			MAX6921_DIN			= FALSE;			
			MAX6921_CLK			= FALSE;
			MAX6921_LOAD		= FALSE;
			MAX6921_BLANK		= FALSE;
			Max6921_State 		= MAX6921_INIT;
			break;
		case MAX6921_INIT:
			if(Anode_Pointer) Anode_Pointer --;
			else Anode_Pointer 	= NO_OF_SEGMENTS;	
			MakeDisplay();
			SegmentBright 		= Bright[Anode_Pointer];	
			Max6921BitCounter 	= 20;
			Max6921_State 		= MAX6921_CLK_LO;
			break;
		case MAX6921_CLK_LO:
			MAX6921_CLK			= FALSE;
			Max6921_State 		= MAX6921_SEND_BIT;
			break;
		case MAX6921_SEND_BIT:
			DisplayMapTmp 		= DisplayMapToSend & 0x1;
			if(DisplayMapTmp)	MAX6921_DIN = TRUE;			
			else 				MAX6921_DIN = FALSE;	
			DisplayMapToSend 	= DisplayMapToSend >> 1;
			Max6921_State 		= MAX6921_CLK_HI;
			break;
		case MAX6921_CLK_HI:
			MAX6921_CLK			= TRUE;
			Max6921_State 		= MAX6921_SEND_BIT;
			if(--Max6921BitCounter==0)
				Max6921_State	= 	MAX6921_LOAD_HI;
			else{
				Max6921_State	= 	MAX6921_CLK_LO;
			}
			break;
		case MAX6921_LOAD_HI:
			MAX6921_LOAD		= TRUE;
			Max6921_State 		= MAX6921_LOAD_LO;
			break;
		case MAX6921_LOAD_LO:
			MAX6921_LOAD		= FALSE;
			if(SegmentBright){
				sw_timer1		= 150;
			}
			Max6921_State 		= MAX6921_WAIT;
			break;
		case MAX6921_WAIT:
			if(!sw_timer1){	
				Max6921_State 	= MAX6921_INIT;
			}
			break;
	}
}

// ------------------------------------------------
// Anody
void MakeDisplay(void){
		switch(Anode_Pointer){
			case 0:
				DisplayMapToSend	= _A0;		
				break; 
			case 1:
				DisplayMapToSend 	= _A1;		
				break; 	
			case 2:
				DisplayMapToSend 	= _A2;		
				break; 
			case 3:
				DisplayMapToSend 	= _A3;		
				break; 	
			case 4:
				DisplayMapToSend 	= _A4;		
				break; 
			case 5:
				DisplayMapToSend 	= _A5;		
				break;
		 	case 6:
				DisplayMapToSend 	= _A6;		
				break; 
			case 7:
				DisplayMapToSend 	= _A7;		
				break; 	
			default:
				break;
		}
// ------------------------------------------------
// Tvary znaku
		switch(Diplay[Anode_Pointer]){
			case 0:
				DisplayMapToSend	|= _0;		
				break; 
			case 1:
				DisplayMapToSend 	|= _1;		
				break; 	
			case 2:
				DisplayMapToSend 	|= _2;		
				break; 
			case 3:
				DisplayMapToSend 	|= _3;		
				break; 	
			case 4:
				DisplayMapToSend 	|= _4;		
				break; 
			case 5:
				DisplayMapToSend 	|= _5;		
				break;
		 	case 6:
				DisplayMapToSend 	|= _6;		
				break; 
			case 7:
				DisplayMapToSend 	|= _7;		
				break; 	
			case 8:
				DisplayMapToSend 	|= _8;		
				break; 
			case 9:
				DisplayMapToSend 	|= _9;		
				break;
			case SPACE:
				DisplayMapToSend 	|= _SPACE;		
				break;
			case MINUS:
				DisplayMapToSend 	|= _MINUS;		
				break;
			case GRAD:
				DisplayMapToSend 	|= _GRAD;
				break;
			case C:
				DisplayMapToSend 	|= _C;
				break;
			default:
				DisplayMapToSend 	|= _SPACE;	
				break;
		}
}
//------------------------------------------------


