#include "p33FJ128GP202.h"
#include "unit_param.h"
#include "clock.h"
#include "timer_3.h"
#include "i2c_rtcc.h"
#include "i2c.h"


#define	_BCD2DEC(a) 10*((a & 0x70) >> 4) + (a & 0x0f)
#define _DEC2BCD(a) ((a / 10) << 4) | (a % 10)

t_debouncer SetModePlus, SetModeMinus, Plus, Minus;
t_toggle	SetModePlusToggle;
t_set SetState;

void IntTo2Dec(int value, int position);

int volatile Sec, Min, Hrs;
int volatile SecBCD, MinBCD, HrsBCD;
int volatile SetSec, SetMin, SetHrs;
int volatile SetSecBCD, SetMinBCD, SetHrsBCD;

int SecOld;
int Blik_1s, Tik_1s;

int Temperature;

void clock(void){

// Debouncers
	SetModePlus.input 	= BTN1;				// Left
	SetModeMinus.input 	= BTN2;
	Plus.input 			= BTN3;
	Minus.input 		= BTN4;
	
	debouncer(&SetModePlus, Blik_1ms);	
	debouncer(&SetModeMinus, Blik_1ms);
	debouncer(&Plus, Blik_1ms);	
	debouncer(&Minus, Blik_1ms);

/*
	SetModePlusToggle.input = SetModePlus.debounced;
	toggle(&SetModePlusToggle);
*/	
	

	switch(SetState){
		case DISP_CLOCK:
			Bright[0] 		= FALSE;
			Bright[1] 		= FALSE;
			Bright[2] 		= FALSE;
			Bright[3] 		= FALSE;
			Bright[4] 		= FALSE;
			Bright[5] 		= FALSE;
			Bright[6] 		= FALSE;
			Bright[7] 		= FALSE;
// Read data from RTC
			SecBCD =  i2c_rtcc_rd(ADDR_SEC); 	// read SECs
			Sec = _BCD2DEC(SecBCD & 0x7f);
			MinBCD = i2c_rtcc_rd(ADDR_MIN);		// read MINs
			Min = _BCD2DEC(MinBCD);
			HrsBCD  = i2c_rtcc_rd(ADDR_HOUR); 	// read HOURs
			Hrs = _BCD2DEC(HrsBCD & 0x3f);
// Indicate - clock running
			if(Sec != SecOld){
				Blik_1s		= TRUE;
				sw_timer0	= 20000;
			}	
			SecOld = Sec;
			if(!sw_timer0){
				Blik_1s 	= FALSE;
			}
// Transfer to display
			IntTo2Dec(Sec,1);
			if(Blik_1s)	Diplay[2] = MINUS;
			else 		Diplay[2] = SPACE;
			IntTo2Dec(Min,4);
			if(Blik_1s)	Diplay[5] = MINUS;
			else 		Diplay[5] = SPACE;
			IntTo2Dec(Hrs,7);
// Set mode
			if(SetModePlus.puls){
				SetHrsBCD 	= HrsBCD & 0xc0;		// Store setting bits
				SetHrs		= Hrs;
				SetState	= SET_HOURS;
// Timer for timeout if inactivity in SET mode
				sw_timer3 	= SET_MODE_TIMEOUT;
			}
// Set display temperature 
			if(Minus.debounced){
					SetState	= DISP_TEMP_CLEAR;	
			}

		break;
	
		case SET_HOURS:
			Bright[0] 		= FALSE;
			Bright[1] 		= FALSE;
			Bright[2] 		= FALSE;
			Bright[3] 		= FALSE;
			Bright[4] 		= FALSE;
			Bright[5] 		= FALSE;
			Bright[6] 		= TRUE;
			Bright[7] 		= TRUE;

			if(Plus.puls){
				if(++SetHrs > 23) SetHrs = 0;
				sw_timer3 	= SET_MODE_TIMEOUT;
			}
			if(Minus.puls){
				if(--SetHrs < 0) SetHrs = 23;
				sw_timer3 	= SET_MODE_TIMEOUT;
 			}
			if(!sw_timer3){								// Setmode timeout
					SetState	= DISP_CLOCK;
			}
			if(SetModePlus.puls){
				SetHrsBCD  = _DEC2BCD(SetHrs);			// Write HRSs
				i2c_rtcc_wr(ADDR_HOUR,SetHrsBCD);  			
				
				MinBCD 		= i2c_rtcc_rd(ADDR_MIN);	// read MIN
				SetMinBCD	= MinBCD & 0x80;
				SetMin 		= _BCD2DEC(MinBCD);
				SetState	= SET_MINS;
			}				
			IntTo2Dec(SetHrs,7);
		break;

		case SET_MINS:
			Bright[0] 		= FALSE;
			Bright[1] 		= FALSE;
			Bright[2] 		= FALSE;
			Bright[3] 		= TRUE;
			Bright[4] 		= TRUE;
			Bright[5] 		= FALSE;
			Bright[6] 		= FALSE;
			Bright[7] 		= FALSE;

			if(Plus.puls){
				if(++SetMin > 59) SetMin = 0;
				sw_timer3 	= SET_MODE_TIMEOUT;
			}
			if(Minus.puls){
				if(--SetMin < 0) SetMin = 59;
				sw_timer3 	= SET_MODE_TIMEOUT;
			}
			if(!sw_timer3){								// Setmode inactivity timeout
					SetState	= DISP_CLOCK;
			}
			if(SetModePlus.puls){
				SetMinBCD |= _DEC2BCD(SetMin);			// Write MINs
				i2c_rtcc_wr(ADDR_MIN, SetMinBCD );  	// with set bits
			
				SecBCD 		= i2c_rtcc_rd(ADDR_SEC);	// read SEC
				SetSecBCD	= SecBCD & 0x80;			// store set bits
				SetSec 		= _BCD2DEC(SecBCD);
				SetState	= SET_SECS;
			}				
			IntTo2Dec(SetMin,4);
		break;

		case SET_SECS:
			Bright[0] 		= TRUE;
			Bright[1] 		= TRUE;
			Bright[2] 		= FALSE;
			Bright[3] 		= FALSE;
			Bright[4] 		= FALSE;
			Bright[5] 		= FALSE;
			Bright[6] 		= FALSE;
			Bright[7] 		= FALSE;

			if(Plus.puls){
				if(++SetSec > 59) SetSec = 0;
				sw_timer3 	= SET_MODE_TIMEOUT;
			}
			if(Minus.puls){
				if(--SetSec < 0) SetSec = 59;
				sw_timer3 	= SET_MODE_TIMEOUT;
			}
			if(!sw_timer3){								// Set mode timeout
					SetState	= DISP_CLOCK;
			}
			if(SetModePlus.puls){
				SetSecBCD 	|= _DEC2BCD(SetSec);		// Write SECs
				i2c_rtcc_wr(ADDR_SEC, SetSecBCD );  	// with set bits
				SetState	= DISP_CLOCK;
			}				
			IntTo2Dec(SetSec,1);
		break;

		case DISP_TEMP_CLEAR:
			Bright[0] 		= FALSE;
			Bright[1] 		= FALSE;
			Bright[2] 		= FALSE;
			Bright[3] 		= FALSE;
			Bright[4] 		= FALSE;
			Bright[5] 		= FALSE;
			Bright[6] 		= FALSE;
			Bright[7] 		= FALSE;
	 	
			Diplay[0] = SPACE;
			Diplay[1] = SPACE;
			Diplay[2] = SPACE;
			Diplay[3] = SPACE;
			Diplay[4] = SPACE;
			Diplay[5] = SPACE;
			Diplay[6] = SPACE;
			Diplay[7] = SPACE;
			
			SetState	= DISP_TEMP;
		break;		
		
		case DISP_TEMP:
			Temperature = ReadTempFromRtc();
			IntTo2Dec(Temperature,5);
			Diplay[3] = GRAD;
			Diplay[2] = C;
			if(!Minus.debounced){
					SetState	= DISP_CLOCK;	
			}
		break;			





	}// Switch

}// Clock





void IntTo2Dec(int value, int position){
	Diplay[position] = value / 10;
	value -= 10*Diplay[position];
	Diplay[position-1] = value ; 
}


void toggle(t_toggle *toggle){
	if(toggle->input & !toggle->input_pom & !toggle->output){
		toggle->input_pom 	= TRUE;	
		toggle->output 		= TRUE;
	}
	if(toggle->input & !toggle->input_pom & toggle->output ) {
		toggle->input_pom 	= TRUE; 
		toggle->output 		= FALSE;
	}
	toggle->input_pom = toggle->input;
}

void debouncer(t_debouncer *debouncer, unsigned int volatile sample){
unsigned int volatile bitschanged;
	if(sample && !debouncer->sample_old){
		bitschanged = debouncer->laststate ^ debouncer->input;					// XOR for evatution of change
		debouncer->debounced = (debouncer->debounced & bitschanged) | (debouncer->input & (~bitschanged));
		debouncer->last_state_debounced = debouncer->debounced;
		debouncer->laststate = debouncer->input;
	}
	debouncer->sample_old = sample;
// Ascendig edge (puls only)
	debouncer->puls = debouncer->debounced && (!debouncer->state_debounced_old);
	debouncer->state_debounced_old = debouncer->debounced;
}

