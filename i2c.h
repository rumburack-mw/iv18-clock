/***************************************************************************************
* FileName:        i2c.h
* Dependencies:    None
* Processor:       PIC24FJ128GA010 
* Hardware:        Explorer 16 demo board
* Compiler:        MPLAB® C30 v3.30b
* Company:         Microchip Technology , Inc. 
//......................................................................................
//                   SOFTWARE  LICENSE AGREEMENT    
//......................................................................................
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
* Author               Date            Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* Eugen Ionescu 	   11/7/2011 	   
*
****************************************************************************************/
void ini_i2c1(void)                ;  // init the I2C module
void i2c_start(void)               ;  // generates an I2C start condition
void i2c_restart(void)             ;  // generates an I2C Restart condition (for reads)
void i2c_stop(void)                ;  // generates an I2C stop condition
void i2c_wr(unsigned char i2c_data);  // writes a byte to the I2C bus
unsigned char i2c_rd(void)         ;  // reads a byte from the I2C bus
void i2c_ack(void)                 ;  // generates a Master Acknowledge
void i2c_nack(void)                ;  // generates a Master No Acknowledge

