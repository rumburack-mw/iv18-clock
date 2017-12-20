/**********************************************************************************
// File Name    : i2c_rtcc_func.c 
// PIC24 family, C language. 
// Dependencies : p24fj128ga010.h, i2c_rtcc.h, i2c.h
// Processor    : PIC24FJ128GA010    
// Hardware     : Explorer 16 demo board, MCP79410 I2C RTCC
// I.D.E.       : MPLAB + C30 compiler v3.30b
// Company      : Microchip Technology , Inc. 
//.................................................................................
//                   SOFTWARE  LICENSE AGREEMENT    
//.................................................................................
// "Microchip Technology Inc." ("Microchip") licenses this software to you 
// solely for use with Microchip's Serial RTCC products.  
// The software is owned by Microchip and/or its licensors, and is protected 
// under applicable copyright laws.  All rights reserved.
// SOFTWARE IS PROVIDED "AS IS."  MICROCHIP AND ITS LICENSOR EXPRESSLY 
// DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING 
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS 
// FOR A PARTICULAR PURPOSE,OR NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP 
// AND ITS LICENSORS BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR 
// CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, HARM TO YOUR EQUIPMENT, 
// COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY 
// CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
// THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS."
//.......................................................................................
* Author                    Date            Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Alexandru Valeanu        	11/7/2011		Initial release for MCP79410 I2C RTCC    
*
****************************************************************************************/
#include "p33FJ128GP202.h"
#include "i2c_rtcc.h"
#include "i2c.h"
//********************************************************************************************
//                         I2C RTCC DRIVERS 
//********************************************************************************************
extern unsigned char err_flg  ;   // the error flag will be used in this file 

//............................................................................................
// The below function writes a data byte in the I2C RTCC
//............................................................................................
void i2c_rtcc_wr(unsigned char rtcc_reg, unsigned char time_var){ // writes a data byte to the I2C RTCC   
i2c_start()             ;  // start I2C communication   
i2c_wr(ADDR_RTCC_WRITE) ;  // write DEVICE ADDR for RTCC WRITES
i2c_wr(rtcc_reg)        ;  // write the register's ADDRESS
i2c_wr(time_var)        ;  // write byte variable in the register 
i2c_stop()           ;  }  // stop I2C communication
//..............................................................................................
// The below function reads a data byte from the I2C RTCC
//..............................................................................................
unsigned char i2c_rtcc_rd(unsigned char rtcc_reg){ // reads a data byte from the I2C RTCC
unsigned char rtcc_buf	;  // general data buffer for the i2c rtcc 
i2c_start()             ;  // start I2C communication
i2c_wr(ADDR_RTCC_WRITE) ;  // write DEVICE ADDR for RTCC WRITES
if(err_flg)                // if an error occured at a PICTAIL removal,
{ return rtcc_buf   ;   }  // leave fast the function 
i2c_wr(rtcc_reg)        ;  // write the register ADDRESS
if(err_flg)                // if an error occured at a PICTAIL removal, 
{ return rtcc_buf   ;   }  // leave fast the function    
i2c_restart()           ;  // RESTART for READS 
i2c_wr(ADDR_RTCC_READ)  ;  // send the DEVICE ADDRESS for RTCC READS.
if(err_flg)                // if an error occured at a PICTAIL removal,
{ return rtcc_buf   ;   }  // leave fast the function 
rtcc_buf=i2c_rd()       ;  // read register (stored in 'rtcc_buf')
i2c_nack()              ;  // NOACK from MASTER (last read byte)
i2c_stop()              ;  // stop I2C communication
return rtcc_buf    	;   }  // return the read byte, stored in the general rtcc buffer
//................................................................................................
// The below function initializes the I2C RTCC
//................................................................................................
void ini_i2c_rtcc(void){             	// initialization of the I2C RTCC: enables the battery circuit                                     // START bit is located in the Sec register
/*                                     	// time/date will be set in 'ini_i2c_time()' 
	unsigned char day=0; 				 // local variable (stores the RTCC DAY register)         
	day = i2c_rtcc_rd(ADDR_DAY); 		 // read day + OSCON bit   
	i2c_rtcc_wr(ADDR_DAY,day|VBATEN); 	 // enable the battery back-up  
*/
}
//................................................................................................
// The below function initializes the time/date variables, only if the oscillator is not yet running
void ini_i2c_time(void){             // initialization of time/date vars on the I2C RTCC
unsigned char status=0;   				 // local variable (stores the RTCC DAY register) 
	status = i2c_rtcc_rd(ADDR_STAT);   		 // read day + OSCON bit 
	if((status&OSF)!=OSF) ;             	 // if oscillator = already running, do nothing. 
	else{                                	 // if oscillator = not running, set time/date(arbitrary)
		i2c_rtcc_wr(ADDR_YEAR,0x11);         // initialize YEAR  register : (20)11           
		i2c_rtcc_wr(ADDR_MNTH,0x11);   	     // initialize MONTH register : november   
		i2c_rtcc_wr(ADDR_DATE,0x01);   	     // initialize DATE  register : date = 01  
		i2c_rtcc_wr(ADDR_HOUR,0x00);   	     // initialize HOUR  register : hour = 00  
		i2c_rtcc_wr(ADDR_MIN,0x00) ;   	     // initialize MIN   register : min  = 00  
//i2c_rtcc_wr(ADDR_SEC,START_32KHZ);}} // init SEC register and start the 32khz oscillator 
	}
} 
//................................................................................................
// Returns the temperature in Celsius times four.  

int ReadTempFromRtc(void){
unsigned char temp_msb, temp_lsb;
char nint;
float rv;

	temp_lsb= i2c_rtcc_rd(ADDR_LSB_TEMP)>>6;
	temp_msb= i2c_rtcc_rd(ADDR_MSB_TEMP);
	if ((temp_msb & 0x80) != 0)
        nint = temp_msb | ~((1 << 8) - 1);      // if negative get two's complement
    else
        nint = temp_msb;
 	
	rv = 0.25 * (float)temp_lsb + (float)nint;

	return (int)rv;
}