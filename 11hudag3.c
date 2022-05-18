#include "C:\Users\User\Documents\Azaa_1\TURSHILT\11hudag3.h"


#byte port_d   =  0x0f83
#byte port_a   =  0x0f80
#byte port_e   =  0x0f84
#byte port_b   =  0x0f81

int8 temp,i=0,a0,a1,a2,a3,a4,a5,a6,a7,a8;
int8 data[20],numb[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
int8 n1,n2,n3,tmp,rh,p1,p2,h1,smoke,blok,dundaj=0,j=0;
int16 r0=0,r10=0;

#int_RDA
RDA_isr()
{
temp=getc();
if(temp=='q'){j=1;}
if(temp>='A' && temp<='B'){
   switch (temp){
      case 0x41 : port_d=0x01;break;
      case 0x42: port_d=0x02;break;
   }
}


}



void main()
{

   setup_adc_ports(ALL_ANALOG);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_psp(PSP_DISABLED);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
set_tris_c(0x80);
set_tris_d(0x00);
set_tris_a(255);
set_tris_e(0xff);
set_tris_b(255);
port_d=0;



for(;;){
//for(r10=0;r10<3600;r10++){
putc(0);
port_d=0;


  for(i=0;i<=19;i++){
   set_adc_channel(0);
   delay_ms(12);
   a0=read_adc();
   r0=r0+a0;
   }
   a0=r0/20;
   r0=0;

   for(i=0;i<=19;i++){
   set_adc_channel(1);
   delay_ms(12);
   a1=read_adc();
   r0=r0+a1;
   }
   a1=r0/20;
   r0=0;

for(i=0;i<=19;i++){

   set_adc_channel(3);
delay_ms(12);
a2=read_adc();
r0=r0+a2;
}
a2=r0/20;
r0=0;

for(i=0;i<=19;i++){

   set_adc_channel(4);
delay_ms(12);
a4=read_adc();
r0=r0+a4;
}
a4=r0/20;
r0=0;
delay_ms(1200);

while(j==1){
//temperature
n1=a0/100;
n2=a0/10;
n2=n2%10;
n3=a0%10;

n1=numb[n1];n2=numb[n2];n3=numb[n3];

putc('c');putc('c');putc(':');
putc(n1);putc(n2);putc(n3);putc(':');


//rh
n1=a1/100;
n2=a1/10;
n2=n2%10;
n3=a1%10;

n1=numb[n1];n2=numb[n2];n3=numb[n3];
putc(n1);putc(n2);putc(n3);putc(':');

//p1
n1=a2/100;
n2=a2/10;
n2=n2%10;
n3=a2%10;

n1=numb[n1];n2=numb[n2];n3=numb[n3];
putc(n1);putc(n2);putc(n3);putc(':');

//a4 inverter
n1=a4/100;
n2=a4/10;
n2=n2%10;
n3=a4%10;

n1=numb[n1];n2=numb[n2];n3=numb[n3];
putc(n1);putc(n2);putc(n3);putc(':');

putc(n1);putc(n2);putc(n3);putc(':');
delay_ms(1);
//putc(n1);putc(n2);putc(n3);putc(':');
delay_ms(1);
//putc(n1);putc(n2);putc(n3);putc(':');
delay_ms(1);
//putc(n1);putc(n2);putc(n3);putc(':');
delay_ms(1);


a8=0b00111111 & port_b;
putc(a8);

putc(0x0d);
j=0;
delay_ms(800);
}
delay_ms(1000);
}
//reset_cpu();
//}
}
