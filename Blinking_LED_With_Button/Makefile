# MPLAB IDE generated this makefile for use with GNU make.
# Project: Blinking_LED_With_Button.mcp
# Date: Mon Feb 07 19:13:02 2022

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

Blinking_LED_With_Button.cof : Main.o
	$(LD) /p18F87K90 /l"C:\Program Files (x86)\Microchip\MPLABC18\v3.47\lib" "Main.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"Blinking_LED_With_Button.cof" /M"Blinking_LED_With_Button.map" /W

Main.o : Main.c ../../../../../../../../Program\ Files\ (x86)/Microchip/MPLABC18/v3.47/h/stdio.h ../../../../../../../../Program\ Files\ (x86)/Microchip/MPLABC18/v3.47/h/delays.h Main.c ../../../../../../../../Program\ Files\ (x86)/Microchip/MPLABC18/v3.47/h/p18cxxx.h ../../../../../../../../Program\ Files\ (x86)/Microchip/MPLABC18/v3.47/h/p18f87k90.h ../../../../../../../../Program\ Files\ (x86)/Microchip/MPLABC18/v3.47/h/stdarg.h ../../../../../../../../Program\ Files\ (x86)/Microchip/MPLABC18/v3.47/h/stddef.h
	$(CC) -p=18F87K90 "Main.c" -fo="Main.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "Main.o" "Blinking_LED_With_Button.cof" "Blinking_LED_With_Button.hex"

