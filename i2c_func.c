// File Name    : i2c_func.c 
// PIC24 family, C language. 
// Dependencies : p24fj128ga010.h, i2c.h 
// Processor    : PIC24FJ128GA010    
// Hardware     : Explorer 16 demo board
// I.D.E.       : MPLAB + C30 compiler v3.30b
/***********************************************************************
* Company:         Microchip Technology, Inc.
*
* Software License Agreement
*
* The software supplied herewith by Microchip Technology Incorporated
* (the “Company”) for its dsPIC30F Microcontroller is intended 
* and supplied to you, the Company’s customer, for use solely and
* exclusively on Microchip's dsPIC30F Microcontroller products. 
* The software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*
* Author            Date          Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* Eugen Ionescu	    11/7/2011     Released for PIC24FJ128GA010
*
 *************************************************************************************************/
#include "p33FJ128GP202.h"
#include "i2c.h"
//..................................................................................................
// Init the I2C1 module
//..................................................................................................
unsigned char err_flg           ;   // global error flag 
void ini_i2c1(void){
I2C1BRG = 0x880;//x009d                ; 	// Fcy = 40 MHz -> Fscl = 100 kHz
I2C1STAT= 0X0000                ;
I2C1CON = 0x1200                ;	// release SCL1 clock, 7-bit slave address
									// slew rate control disabled
I2C1RCV = 0x0000                ;	// clear the transmit and receive registers
I2C1TRN = 0x0000;
I2C1CONbits.I2CEN=1             ; 	// enable the I2C1 module
}	
//...................................................................................................
// This function checks the I2C/Timer1 Interrupt Flags
//...................................................................................................
void poll_tim1(void){
T1CONbits.TON=1;					// start Timer1
while (!(IFS0bits.T1IF|IFS1bits.MI2C1IF));
if (IFS0bits.T1IF){ 			    // if Timer1 overflowed (the I2C device is unplugged)								
	IFS0bits.T1IF=0       ;			// clear Timer1 & I2C Interrupt Flags
	IFS1bits.MI2C1IF=0     ;
    err_flg = 0x01         ;        // set the error flag if a time-out occured
	}
//    LATA = 0xff            ;    }   // set a breakpoint on LEDs 
else { err_flg=0x00        ;        // if no error in the I2C comm, clear the error flag 
	   IFS1bits.MI2C1IF=0  ;    }   // and the I2C general flag 
T1CONbits.TON=0            ;		// stop Timer1 in any case 
TMR1 = 0x0000              ;    }   // and clear it 
//..................................................................................................
// This function generates an I2C Start Condition
//..................................................................................................
void i2c_start(void){
while (I2C1STATbits.TRSTAT);		// Wait for bus Idle
I2C1CONbits.SEN = 1        ;		// Generate Start Condition
poll_tim1()                ;    }	// Wait for I2C/Timer1 interrupt flag
//..................................................................................................
// This function generates a Restart Condition (for reads)
//..................................................................................................
void i2c_restart(void){
while (I2C1STATbits.TRSTAT);		// Wait for bus Idle
I2C1CONbits.RSEN = 1       ;		// Generate a Restart		
poll_tim1()                ;	}	// Wait for I2C/Timer1 interrupt flag
//..................................................................................................
// This function generates an I2C Stop Condition
//..................................................................................................
void i2c_stop(void){
while (I2C1STATbits.TRSTAT);		// Wait for bus Idle
I2C1CONbits.PEN = 1        ;		// Generate Stop Condition
poll_tim1()                ;	}	// Wait for I2C/Timer1 interrupt flag
//..................................................................................................
// Writes a byte to the I2C bus
//..................................................................................................
void i2c_wr(unsigned char i2c_data){
while (I2C1STATbits.TRSTAT);		// Wait for bus Idle
I2C1TRN=i2c_data           ;		// Load byte in the transmit buffer
poll_tim1()                ;	}	// Wait for I2C/Timer1 interrupt flag
//..................................................................................................
// Reads a byte from the I2C bus
//..................................................................................................
unsigned char i2c_rd(void){
while (I2C1STATbits.TRSTAT);		// Wait for bus Idle
I2C1CONbits.RCEN = 1       ;		// Enable Master receive
poll_tim1()                ;		// Wait for I2C/Timer1 interrupt flag
return(I2C1RCV)            ;	}	// Return data in buffer
//...................................................................................................
// Generates a Master No Acknowledge on the Bus
//...................................................................................................
void i2c_nack(void){
I2C1CONbits.ACKDT = 1      ;		// Set   the related flag for NotAck
I2C1CONbits.ACKEN = 1      ;		// Start Ack sequence
poll_tim1()                ;		// Wait  for I2C/Timer1 interrupt flag
I2C1CONbits.ACKDT = 0      ;    }	// Clear the related flag for ACk
//..................................................................................................
// Generates a Master Acknowledge on the Bus
//..................................................................................................
void i2c_ack(void){
I2C1CONbits.ACKDT = 0      ;		// Clear  the related flag for Ack
I2C1CONbits.ACKEN = 1      ;		// Start Ack sequence
poll_tim1()                ;	}	// Wait for I2C/Timer1 interrupt flag
