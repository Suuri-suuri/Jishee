#include <18F452.h>
#device adc=8
#use delay(clock=20000000)
#fuses NOWDT,WDT128,HS, NOPROTECT, NOOSCSEN, BROWNOUT, BORV20, NOPUT, STVREN, NODEBUG, NOLVP, NOWRT, NOWRTD, NOWRTB, NOWRTC, NOCPD, NOCPB, NOEBTR, NOEBTRB
#use rs232(baud=19200,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#use i2c(Slave,Slow,sda=PIN_C4,scl=PIN_C3,address=0xA0)

