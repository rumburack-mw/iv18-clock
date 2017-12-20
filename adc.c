void init_ADC(void){
       
		ADCONbits.ADON 			= 0;    //Disable the ADC  
		ADCONbits.FORM 			= 0;    //Integer data format
		ADCONbits.EIE 			= 0;    //Early Interrupt disabled
		ADCONbits.ORDER 		= 0;	//Convert even channel first
		ADCONbits.SEQSAMP 		= 0;	//Select simultaneous sampling
		ADCONbits.ADCS 			= 5;	//ADC clock = FADC/6 = 120MHz / 6 = 20MHz
		ADCONbits.SLOWCLK		= 1;

// Par 0 Uin, Uout	
		ADPCFGbits.PCFB15 		= 0;    //CH0 as analog pin Uin

		ADCPC0bits.TRGSRC0		= 4;    //ADC Pair 0 triggered by PWM4 Trigger
		IFS6bits.ADCP0IF		= 0;    //Clear ADC Pair 0 interrupt flag 
		IPC27bits.ADCP0IP		= 5;    //Set ADC Pair 0 interrupt priority
		IEC6bits.ADCP0IE		= 1;    //Enable the ADC Pair 0 interrupt
		ADSTATbits.P0RDY		= 0;    //Clear Pair 0 data ready bit
		ADCPC0bits.IRQEN0		= 1;    //Enable ADC Interrupt pair 0 



		ADCONbits.ADON = 1;          // Enable the ADC  
}