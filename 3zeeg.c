#include "C:\Users\User\Documents\Azaa_1\TURSHILT\3zeeg.h"


#byte port_d   =  0x0f83
#byte port_a   =  0x0f80
#byte port_e   =  0x0f84
#byte port_b   =  0x0f81
#bit dat0 = 0xf82.0

int8 temp2,i=0,a0,a1,a2,a3,a4,a5,a6,a7,a8;
int8 data[20],numb[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
int8 n1,n2,n3,tmp,p1,p2,h1,smoke,blok,dundaj=0,j=0;
int16 r0=0,r10=0;

char message1[] = "Temp = 00.0  ";
char message2[] = "RH   = 00.0  ";
short Time_out;
unsigned int8 T_byte1, T_byte2, RH_byte1, RH_byte2, CheckSum;
unsigned int16 RH, Temp;

#int_RDA
RDA_isr()
{
temp2=getc();

if(temp2>='O' && temp2<='S'){
   switch (temp2){
       case 'O' : port_d=1;break;
      case 'P':port_d=2;break;
      case 'Q': port_d=4;break;
      case 'R':port_d=8;break;
      case 'S':port_d=0x10;break;
   }
}

}


void start_signal(){
 set_tris_c(0x80);    //Configure RD0 as output
 dat0 = 0;    //RD0 sends 0 to the sensor
  delay_ms(25);
  dat0 = 1;                       // Connection pin output high
  delay_us(30);
  set_tris_c(0x81);              // Configure connection pin as input
}
short check_response(){
  delay_us(30);
  if(dat0 == 0){                     // Read and test if connection pin is low
    delay_us(80);
    if(dat0 == 1){                    // Read and test if connection pin is high
      delay_us(50);
      return 1;}
    }
}
unsigned int8 Read_Data(){
  unsigned int8 i1, k, _data = 0;     // k is used to count 1 bit reading duration
  if(Time_out)
    break;
  for(i1 = 0; i1 < 8; i1++){
    k = 0;
    while(dat0 == 0){                          // Wait until pin goes high
      k++;
      if (k > 100) {Time_out = 1; break;}
      delay_us(1);}
    delay_us(30);
    if(dat0 == 0)
      bit_clear(_data, (7 - i1));               // Clear bit (7 - i)
    else{
      bit_set(_data, (7 - i1));                 // Set bit (7 - i)
      while(dat0 == 1){                         // Wait until pin goes low
      k++;
      if (k > 100) {Time_out = 1; break;}
      delay_us(1);}
    }
  }
  return _data;
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
set_tris_a(0xff);
set_tris_e(0xff);
set_tris_b(0xff);
port_d=0;
port_a=0;
port_e=0;
port_b=0;

for(;;){
for(r10=0; r10<175;r10++){
port_d=0;
delay_ms(20);

Time_out = 0;
   Start_signal();
       if(check_response()){                    // If there is response from sensor
      RH_byte1 = Read_Data();                 // read RH byte1
      RH_byte2 = Read_Data();                 // read RH byte2
      T_byte1 = Read_Data();                  // read T byte1
      T_byte2 = Read_Data();                  // read T byte2
      Checksum = Read_Data();                 // read checksum
      if(Time_out){                           // If reading takes long time
        //putc('4');putc('4');putc('4');putc(':');putc('4');putc('4');putc('4');
      }
      else{
       if(CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF)){
        rh = RH_byte1;
        rh = (rh << 8) | RH_byte2;
        Temp = T_byte1;
        Temp = (Temp << 8) | T_byte2;
        if (Temp > 0x8000){
         message1[6] = '-';
         Temp = Temp & 0x7FFF; }
        else{
        message1[6] = '0';}
        message1[7]  = (Temp / 100) % 10  + 48;
        message1[8]  = (Temp / 10) % 10  + 48;
        message1[10] = Temp % 10  + 48;
        message2[7]  = (RH / 100) % 10 + 48;
        message2[8]  = (RH / 10) % 10 + 48;
        message2[10] = RH % 10 + 48;



       }
        else {
          //putc('3');putc('3');putc('3');putc(':');putc('3');putc('3');putc('3');
        }
      }
    }
    else {
     // putc('2');putc('2');putc('2');putc(':');putc('2');putc('2');putc('2');
    }


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
set_adc_channel(2);
delay_ms(12);
a2=read_adc();
r0=r0+a2;
}
a2=r0/20;
r0=0;

/*for(i=0;i<=19;i++){
set_adc_channel(3);
delay_ms(12);
a3=read_adc();
r0=r0+a3;
}
a3=r0/20;
r0=0;*/

//h1
for(i=0;i<=79;i++){
set_adc_channel(4);
delay_ms(12);
a4=read_adc();
r0=r0+a4;
}
a4=r0/80;
r0=0;

for(i=0;i<=19;i++){
set_adc_channel(5);
delay_ms(12);
a5=read_adc();
r0=r0+a5;
}
a5=r0/20;
r0=0;

for(i=0;i<=19;i++){
set_adc_channel(6);
delay_ms(12);
a6=read_adc();
r0=r0+a6;
}
a6=r0/20;
r0=0;


for(i=0;i<=19;i++){
set_adc_channel(7);
delay_ms(12);
a7=read_adc();
r0=r0+a7;
}
a7=r0/20;
r0=0;



//temperature

putc('z');putc('g');putc(':');
putc(message1[6]);putc(message1[7]); putc(message1[8]);putc(':');


//rh

putc('0');putc(message2[7]);putc(message2[8]);putc(':');

//p1
n1=a0/100;
n2=a0/10;
n2=n2%10;
n3=a0%10;

n1=numb[n1];n2=numb[n2];n3=numb[n3];
putc(n1);putc(n2);putc(n3);putc(':');

//p2
n1=a1/100;
n2=a1/10;
n2=n2%10;
n3=a1%10;

n1=numb[n1];n2=numb[n2];n3=numb[n3];
putc(n1);putc(n2);putc(n3);putc(':');

//h1
n1=a4/100;
n2=a4/10;
n2=n2%10;
n3=a4%10;

n1=numb[n1];n2=numb[n2];n3=numb[n3];
putc(n1);putc(n2);putc(n3);putc(':');

//dorgio1
n1=a5/100;
n2=a5/10;
n2=n2%10;
n3=a5%10;

n1=numb[n1];n2=numb[n2];n3=numb[n3];
putc(n1);putc(n2);putc(n3);putc(':');

//dorgio2
n1=a6/100;
n2=a6/10;
n2=n2%10;
n3=a6%10;

n1=numb[n1];n2=numb[n2];n3=numb[n3];
putc(n1);putc(n2);putc(n3);putc(':');

//inverter
n1=a7/100;
n2=a7/10;
n2=n2%10;
n3=a7%10;

n1=numb[n1];n2=numb[n2];n3=numb[n3];
putc(n1);putc(n2);putc(n3);putc(':');


a8=0b00111111 & port_b;
putc(a8);
putc(13);


}
reset_cpu();
}
}
