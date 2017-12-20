#include "p33FJ128GP202.h"
#include "unit_param.h"
#include "timer_3.h"
#include "clock.h"
#include "i2c_rtcc.h"


// Configuracni bity MCU
_FOSCSEL(FNOSC_FRC)								// Po resetu jede na vnitrni oscilator
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT)	//
_FWDT(FWDTEN_OFF)								// Wdog vyp	
_FPOR(FPWRT_PWR128)								
_FICD(ICS_PGD2 & JTAGEN_OFF)					// Vypnout JTAG	
//---------------------------------------------------

 void ini_tim1(void)      {        // initialization of TIMER1 
    T1CON = 0x0010           ;        // stop TMR1, psc = 08 / 0.5usec  
    PR1   = 200              ;        //   
    TMR1  = 0x0000           ;   }    // clear the timer




int main(){
// MCU jede po resetu na vnitrni RC oscilator 7.37 MHz
/* Konfigurace oscilatoru pro beh na xxMhz a xtal. oscilatoru:
   Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
   Fosc= 7.3728*(43)/(2*2)=80Mhz for Fosc, Fcy = 40Mhz */

// Konfigurace PLL preddelicky, PLL delicky, PLL nasobicky 

	PLLFBDbits.PLLDIV	= PLLdiv;
	CLKDIVbits.PLLPOST 	= PLLpost;		
	CLKDIVbits.PLLPRE 	= PLLpre;		
	OSCTUN = 0;			

// Priprava multiplexeru hodin pro prepnuti zdroje hodin XT_PLL (NOSC = 0b011)
    __builtin_write_OSCCONH(0x03);		//Novy zdroj hodin - XTAL w/ PLL 
    __builtin_write_OSCCONL(0x01);  	//Enable Switch

	while(OSCCONbits.COSC != 0x03);		//Cekani, nez dojde k prepnuti zdroje hodin 
   	while(OSCCONbits.LOCK != 1);		//Cekani na zaveseni PLL hodin

// ====================== A jedeme na TURBO ... ==============================================

//Konfigurace pinu MCU 
  __builtin_write_OSCCONL(OSCCON & ~(1<<6));  		// Odemkni konfiguracni registr

// UART1
//	RPINR18bits.U1RXR 		= 10; 					// RP10 ->UART1_RX	
//	RPOR5bits.RP11R			= 0b00011;     			// RP71 ->UART1_TX
// OC3
	RPOR7bits.RP14R			= 0b10011;     			// RP14 ->OC2
//	RPOR4bits.RP9R			= 0b10100;     			// RP9 ->OC3

	__builtin_write_OSCCONL(OSCCON |(1<<6));		// Zamkni konfiguracni registr  

	ADPCFG	 	= 0xffff;    	// Nastaveni vsech moznych analogovych  pinu do digitalnido modu,

TRISBbits.TRISB8 = 1;
TRISBbits.TRISB9 = 1;		           // RB8 = SCL1, RB9 = SDA1 = inputs;


	LED_TRIS 			= PORT_DIR_OUT;
	MAX6921_DIN_TRIS	= PORT_DIR_OUT;
	MAX6921_CLK_TRIS	= PORT_DIR_OUT;
	MAX6921_LOAD_TRIS	= PORT_DIR_OUT;
	MAX6921_BLANK_TRIS	= PORT_DIR_OUT;
	DISP_HEATING_TRIS	= PORT_DIR_OUT;

	BTN1_TRIS			= PORT_DIR_IN;
	BTN2_TRIS			= PORT_DIR_IN;		
	BTN3_TRIS			= PORT_DIR_IN;	
	BTN4_TRIS			= PORT_DIR_IN;		

// Reset MAX6921
	MAX6921_DIN			= FALSE;			
	MAX6921_CLK			= FALSE;
	MAX6921_LOAD		= FALSE;
	MAX6921_BLANK		= FALSE;
// Zhaveni displeje
	DISP_HEATING		= TRUE;

	timer2init();
	timer3init();

ini_tim1()                        ;   // init TMR1 for the time-out in the I2C comm         
ini_i2c1()					      ;   // init the I2C module
//ini_i2c_rtcc()					  ;   // init the I2C RTCC device (enable the battery back-up)
//i2c_rtcc_wr(ADDR_CTRL,SQWE+ALM_NO+MFP_01H);  
                                      // square wave on MFP, no alarms, MFP = 1Hz(CONTROL REG)
//ini_i2c_time()				      ;   // init time: 1.11.2011, 00:00:00 AM  



	Diplay[0] 			= SPACE;
	Diplay[1] 			= SPACE;
	Diplay[2] 			= SPACE;
	Diplay[3] 			= SPACE;
	Diplay[4] 			= SPACE;
	Diplay[5] 			= SPACE;
	Diplay[6] 			= SPACE;
	Diplay[7] 			= SPACE;

	Bright[0] 			= FALSE;
	Bright[1] 			= FALSE;
	Bright[2] 			= FALSE;
	Bright[3] 			= FALSE;
	Bright[4] 			= FALSE;
	Bright[5] 			= FALSE;
	Bright[6] 			= FALSE;
	Bright[7] 			= FALSE;



	while(1){

clock();

			}
}// Main





