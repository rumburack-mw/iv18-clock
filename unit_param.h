#ifndef ___UNIT_PARAM_H__
#define __UNIT_PARAM_H__

#define TRUE	1
#define FALSE	0

// =======================================================
//            Crystal Frequency  * (PLLDIV+2)
// Fosc =     ---------------------------------
//              (PLLPOST+2) * (PLLPRE+2) 
// FCY = Fosc/2	
// ======================================================= 

#define Fin  7372800UL									// Xtal freq

#if((Fin < 3500000) || (Fin > 25000000))
# error "Krystal musi byt v rozsahu 3.5 - 25MHz" 
#endif 

#define FCY 40000000									// Required MIPs

#if(FCY > 71000000)
# error "Pozadovana frekvence jadra FCY  > 70MIPs" 
#endif
#define PLLpre 	0ul										// PLL prescale
#define PLLpost	0ul										// PLL post divisor
#define PLLdiv ((FCY *2* (PLLpost+2)*(PLLpre+2))/Fin)-2 // PLL VCO divisor
														// now calculate PLL input and output
#define VCOinput  (Fin/(PLLpre+2))
#if((VCOinput < 800000ul) || (VCOinput > 8000000ul))
#error "error rozsah VCOinput musi byt 0.8 - 8MHz"
#endif 
#define VCOoutput (VCOinput*(PLLdiv+2))
#if((VCOoutput < 120000000ul) || (VCOoutput > 340000000ul))
#error "error VCOoutput musi byt 100 - 340MHz"
#endif
#define Fosc (VCOoutput/(PLLdiv+2))
#define SysCLK Fosc
// =======================================================



#define _TMR_FREQ(a)	(int)((float)FCY/(float)a)
// LED fpashing freq
#define F_LED_BLIK	10	//Hz

#define SET_MODE_TIMEOUT	2000000


// I/O direction
#define PORT_DIR_IN		1
#define PORT_DIR_OUT	0

// V/V 	
#define LED_TRIS			TRISBbits.TRISB5	//
#define MAX6921_DIN_TRIS	TRISBbits.TRISB1	
#define MAX6921_CLK_TRIS	TRISBbits.TRISB2
#define MAX6921_LOAD_TRIS	TRISBbits.TRISB3
#define MAX6921_BLANK_TRIS	TRISAbits.TRISA4
#define DISP_HEATING_TRIS	TRISBbits.TRISB4

#define BTN1_TRIS			TRISBbits.TRISB10
#define BTN2_TRIS			TRISBbits.TRISB11
#define BTN3_TRIS			TRISBbits.TRISB12
#define BTN4_TRIS			TRISBbits.TRISB13

#define LED					LATBbits.LATB5		//	
#define MAX6921_DIN			LATBbits.LATB1	
#define MAX6921_CLK			LATBbits.LATB2
#define MAX6921_LOAD		LATBbits.LATB3
#define MAX6921_BLANK		LATAbits.LATA4
#define DISP_HEATING		LATBbits.LATB4		

#define BTN1				!PORTBbits.RB10				
#define BTN2				!PORTBbits.RB11
#define BTN3				!PORTBbits.RB12	
#define BTN4				!PORTBbits.RB13	



// Codes of chars
#define SPACE	10
#define MINUS	11
#define GRAD	12
#define C		13

// Map of chars
//            DCEGBAF
#define _0		0b1110111
#define _1		0b0100100
#define _2		0b1011110
#define _3		0b1101110
#define _4		0b0101101
#define _5		0b1101011
#define _6		0b1111011
#define _7		0b0100110
#define _8		0b1111111
#define _9		0b1101111
#define _SPACE	0b0000000
#define _MINUS	0b0001000
#define _GRAD	0b0001111
#define _C		0b1010011




// Anodes
#define _A0	0b0100000000000000000
#define _A1	0b0000000010000000000
#define _A2	0b0010000000000000000
#define _A3	0b0000000100000000000
#define _A4	0b0001000000000000000
#define _A5	0b0000001000000000000
#define _A6	0b0000010000000000000
#define _A7	0b0000100000000000000
#define _A8	0b1000000000000000000



#endif

