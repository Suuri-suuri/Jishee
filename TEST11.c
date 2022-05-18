#include "C:\Users\User\Documents\Azaa_1\TURSHILT\TEST11.h"

#byte port_d   =  0xf83
int8 r0,r1,r2,i=0,temp;
int8 data[100];

#int_RDA
RDA_isr()
{
temp=getc();
if(temp=='@'){i=0;}
/*if(temp>31 && temp<128){
   data[i]=temp;
   i++;
  
}
else{i=0;}*/
}

#int_SSP
SSP_isr()
{
r2=i2c_read();
}



void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_psp(PSP_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   enable_interrupts(INT_RDA);
   enable_interrupts(INT_SSP);
   enable_interrupts(GLOBAL);
set_tris_c(0x91);
set_tris_d(0x00);
port_d=0;
data[3]=1;
for(;;){
   if(i==0){
   delay_ms(1000);
   i=10;
      port_d=data[3];
      putc('#');
     
      putc('C');//delay_ms(100);
      putc('1');//delay_ms(100);
      putc(' ');//delay_ms(100);
      putc(data[3]);//delay_ms(100);
      putc(13);
      data[1]=0;
      data[0]=0;
             //delay_ms(3000);  
             
   }     
   
}
}
