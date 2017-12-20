# MPLAB IDE generated this makefile for use with GNU make.
# Project: V18_Clock.mcp
# Date: Sat Jun 11 14:16:39 2016

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

V18_Clock.hex : V18_Clock.cof
	$(HX) "V18_Clock.cof"

V18_Clock.cof : main.o timer_3.o timer_2.o clock.o i2c_func.o i2c_rtcc_func.o
	$(CC) -mcpu=33FJ128GP202 "main.o" "timer_3.o" "timer_2.o" "clock.o" "i2c_func.o" "i2c_rtcc_func.o" -o"V18_Clock.cof" -Wl,-Tp33FJ128GP202.gld,--defsym=__MPLAB_BUILD=1,-Map="V18_Clock.map",--report-mem

main.o : i2c_rtcc.h unit_param.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h clock.h unit_param.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h timer_3.h unit_param.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h main.c
	$(CC) -mcpu=33FJ128GP202 -x c -c "main.c" -o"main.o" -g -Wall -Os

timer_3.o : unit_param.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h timer_3.h unit_param.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h timer_3.c
	$(CC) -mcpu=33FJ128GP202 -x c -c "timer_3.c" -o"timer_3.o" -g -Wall -Os

timer_2.o : unit_param.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h timer_2.h unit_param.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h timer_2.c
	$(CC) -mcpu=33FJ128GP202 -x c -c "timer_2.c" -o"timer_2.o" -g -Wall -Os

clock.o : i2c.h i2c_rtcc.h unit_param.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h timer_3.h unit_param.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h clock.h unit_param.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h clock.c
	$(CC) -mcpu=33FJ128GP202 -x c -c "clock.c" -o"clock.o" -g -Wall -Os

i2c_func.o : i2c.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h i2c_func.c
	$(CC) -mcpu=33FJ128GP202 -x c -c "i2c_func.c" -o"i2c_func.o" -g -Wall -Os

i2c_rtcc_func.o : i2c.h i2c_rtcc.h ../../../../program\ files/microchip/mplabc30/v3.31/support/dsPIC33F/h/p33FJ128GP202.h i2c_rtcc_func.c
	$(CC) -mcpu=33FJ128GP202 -x c -c "i2c_rtcc_func.c" -o"i2c_rtcc_func.o" -g -Wall -Os

clean : 
	$(RM) "main.o" "timer_3.o" "timer_2.o" "clock.o" "i2c_func.o" "i2c_rtcc_func.o" "V18_Clock.cof" "V18_Clock.hex"

