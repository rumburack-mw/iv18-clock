/**********************************************************************
* FileName:        i2c_rtcc.h
* Dependencies:    None
* Processor:       PIC24FJ128GA010 
* Hardware:        Explorer 16 demo board, MCP79410 I2C RTCC
* Compiler:        MPLAB® C30 v3.30b
* Company:         Microchip Technology , Inc. 
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
//.............................................................................................
* Author                           Date       Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Alexandru Valeanu          				  Initial release for MCP79410 I2C RTCC    
*
***********************************************************************************************/
void i2c_rtcc_wr(unsigned char rtcc_reg, unsigned char data); // writes data to  the I2C RTCC   
unsigned char i2c_rtcc_rd(unsigned char rtcc_reg)           ; // reads data from the I2C RTCC
void ini_i2c_rtcc(void)                                     ; // init the I2C RTCC
void ini_i2c_time(void)                                     ; // init ime/date vars in the RTCC
int ReadTempFromRtc(void);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                   GLOBAL CONSTANTS RTCC - REGISTERS ADDRESSES 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     #define  ADDR_RTCC_WRITE   0b11010000 //  DEVICE ADDR for RTCC MCHP  (writes) 
     #define  ADDR_RTCC_READ    0b11010001 //  DEVICE ADDR for RTCC MCHP  (reads) 
//.............................................................................................  
     #define  ADDR_SEC          0x00       //  address of SECONDS      register 
     #define  ADDR_MIN          0x01       //  address of MINUTES      register 
     #define  ADDR_HOUR         0x02       //  address of HOURS        register 
     #define  ADDR_DAY          0x03       //  address of DAY OF WK    register 
     #define  ADDR_DATE         0x04       //  address of DATE         register  
     #define  ADDR_MNTH         0x05       //  address of MONTH        register 
     #define  ADDR_YEAR         0x06       //  address of YEAR         register 

     #define  ADDR_ALM1SEC      0x07       //  address of ALARM1 SEC   register 
     #define  ADDR_ALM1MIN      0x08       //  address of ALARM1 MIN   register 
     #define  ADDR_ALM1HR       0x09       //  address of ALARM1 HOUR  register 
     #define  ADDR_ALM1DAT      0x0a       //  address of ALARM1 DATE  register  
   
     #define  ADDR_ALM2MIN      0x0b       //  address of ALARM2 MIN   register 
     #define  ADDR_ALM2HR       0x0c       //  address of ALARM2 HOUR  register 
     #define  ADDR_ALM2DAT      0x0d       //  address of ALARM2 DATE  register  
//............................................................................................
     #define  ADDR_CTRL         0x0e       //  address of CONTROL      register 
     #define  ADDR_STAT         0x0f       //  address of STATUS       register 
     #define  ADDR_OFFSET       0x10       //  address of OFFSET       register 	
//............................................................................................. 
     #define  ADDR_MSB_TEMP     0x11       //  address of Temperature Register (Upper Byte)   
     #define  ADDR_LSB_TEMP     0x12       //  address of Temperature Register (Lower Byte)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                  GLOBAL CONSTANTS RTCC - INITIALIZATION 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     #define  PM                0x20       //  post-meridian bit (ADDR_HOUR) 
     #define  OUT_PIN           0x80       //  = b7 (ADDR_CTRL) 
     #define  SQWE              0x40       //  SQWE = b6 (ADDR_CTRL) 
     #define  ALM_NO            0x00       //  no alarm activated        (ADDR_CTRL) 
     #define  ALM_0             0x10       //  ALARM0 is       activated (ADDR_CTRL)
     #define  ALM_1             0x20       //  ALARM1 is       activated (ADDR_CTRL)
     #define  ALM_01            0x30       //  both alarms are activated (ADDR_CTRL)
     #define  MFP_01H           0x00       //  MFP = SQVAW(01 HERZ)      (ADDR_CTRL)  
     #define  MFP_04K           0x01       //  MFP = SQVAW(04 KHZ)       (ADDR_CTRL)  
     #define  MFP_08K           0x02       //  MFP = SQVAW(08 KHZ)       (ADDR_CTRL)  
     #define  MFP_32K           0x03       //  MFP = SQVAW(32 KHZ)       (ADDR_CTRL)  
     #define  MFP_64H           0x04       //  MFP = SQVAW(64 HERZ)      (ADDR_CTRL)
     #define  ALMx_POL          0x80       //  polarity of MFP on alarm  (ADDR_ALMxCTL)   
     #define  ALMxC_SEC         0x00       //  ALARM compare on SEC      (ADDR_ALMxCTL)              
     #define  ALMxC_MIN         0x10       //  ALARM compare on MIN      (ADDR_ALMxCTL)   
     #define  ALMxC_HR          0x20       //  ALARM compare on HOUR     (ADDR_ALMxCTL)   
     #define  ALMxC_DAY         0x30       //  ALARM compare on DAY      (ADDR_ALMxCTL)   
     #define  ALMxC_DAT         0x40       //  ALARM compare on DATE     (ADDR_ALMxCTL)   
     #define  ALMxC_ALL         0x70       //  ALARM compare on all param(ADDR_ALMxCTL)    
     #define  ALMx_IF           0x08       //  MASK of the ALARM_IF      (ADDR_ALMxCTL)

// Status register
     #define  OSF               0x80       //  state of the oscillator(running or not)
     #define  EN32KHZ           0x08       //  
     #define  BSY               0x04       //  
     #define  A2F               0x02       //  
     #define  A1F               0x01       //  
// Control register
     #define  EOSC              0x80       //  Enable Oscillator (EOSC)
     #define  BBSQW             0x40       //  Battery-Backed Square-Wave Enable (BBSQW)
     #define  CONV              0x20       //  Convert Temperature (CONV).
     #define  RS2               0x10       //  Rate Select (RS2 and RS1)
     #define  RS1               0x08       //  Rate Select (RS2 and RS1)
     #define  INTCN             0x04       //  Interrupt Control (INTCN)
     #define  A2IE              0x02       //  Alarm 2 Interrupt Enable (A2IE)
     #define  A1IE              0x01       //  Alarm 1 Interrupt Enable (A1IE)
     
