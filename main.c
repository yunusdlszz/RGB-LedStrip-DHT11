#include "io430.h"
 
#define BLED BIT2
#define GLED BIT1
#define RLED BIT0
 


 

unsigned int tR=0,tG=0,tB=0;
 
unsigned long sicaklik = 0;
unsigned long adcdeger = 0; 
unsigned long sicaklik1 = 0;
 

void RGB_ON(unsigned int tR,unsigned int tG, unsigned int tB){
unsigned int a;
unsigned int i;
 
for(a=0;a<25;a++){
for(i=1;i<=255;i++){  
	if(i<=tR)P1OUT|=RLED;
	if(i>tR)P1OUT&= ~RLED;
 
	if(i<=tG)P1OUT|=GLED;
	if(i>tG)P1OUT&= ~GLED;
 
	if(i<=tB)P1OUT|=BLED;
	if(i>tB)P1OUT&= ~BLED; 
 
	__delay_cycles(1);
}}}
//---------------------------------------
 

void bak_renk_tablosu(void){
		if(sicaklik<20){tR=255; tG=0;   tB=255;}
if(sicaklik>=20 && sicaklik<21){tR=255; tG=0;   tB=255;} // pembe
if(sicaklik>=21 && sicaklik<22){tR=204; tG=0;   tB=255;}
if(sicaklik>=22 && sicaklik<23){tR=153; tG=0;   tB=255;}
if(sicaklik>=23 && sicaklik<24){tR=102; tG=0;   tB=255;}
if(sicaklik>=24 && sicaklik<25){tR=51;  tG=0;   tB=255;}
if(sicaklik>=25 && sicaklik<26){tR=0;   tG=0;   tB=255;} // mavi
if(sicaklik>=26 && sicaklik<27){tR=0;   tG=51;  tB=255;}
if(sicaklik>=27 && sicaklik<28){tR=0;   tG=102; tB=255;}
if(sicaklik>=28 && sicaklik<29){tR=0;   tG=153; tB=255;}
if(sicaklik>=29 && sicaklik<30){tR=0;   tG=204; tB=255;}
if(sicaklik>=30 && sicaklik<31){tR=0;   tG=255; tB=255;} // turkuaz
if(sicaklik>=31 && sicaklik<32){tR=0;   tG=255; tB=204;}
if(sicaklik>=32 && sicaklik<33){tR=0;   tG=255; tB=153;}
if(sicaklik>=33 && sicaklik<34){tR=0;   tG=255; tB=102;}
if(sicaklik>=34 && sicaklik<35){tR=0;   tG=255; tB=51;}
if(sicaklik>=35 && sicaklik<36){tR=0;   tG=255; tB=0;} // yesil
if(sicaklik>=36 && sicaklik<37){tR=51;  tG=255; tB=0;}
if(sicaklik>=37 && sicaklik<38){tR=102; tG=255; tB=0;}
if(sicaklik>=38 && sicaklik<39){tR=153; tG=255; tB=0;}
if(sicaklik>=39 && sicaklik<40){tR=204; tG=255; tB=0;}
if(sicaklik>=40 && sicaklik<41){tR=255; tG=255; tB=0;} // sari
if(sicaklik>=41 && sicaklik<42){tR=255; tG=204; tB=0;}
if(sicaklik>=42 && sicaklik<43){tR=255; tG=153; tB=0;}
if(sicaklik>=43 && sicaklik<44){tR=255; tG=102; tB=0;}
if(sicaklik>=44 && sicaklik<45){tR=255; tG=51;  tB=0;}
if(sicaklik>=45 && sicaklik<46){tR=255; tG=0;   tB=0;} // kirmizi
	       if(sicaklik>=46){tR=255; tG=0;   tB=0;}
}
//---------------------------------------
 

main(void)
{
WDTCTL = WDTPW + WDTHOLD;
 
   BCSCTL1 = CALBC1_1MHZ;
   DCOCTL = CALDCO_1MHZ;
 
  ADC10CTL0 &= ~ENC;                            
  ADC10CTL1 = INCH_5 + ADC10SSEL_3 + ADC10DIV_4;  
  ADC10CTL0 = ADC10SHT_1 + ADC10ON + ADC10IE;    
 
  P1DIR =  BIT0|BIT1|BIT2;
  P1OUT =  0;
__bis_SR_register(GIE); 
while(1){
ADC10CTL0 |= ENC + ADC10SC;
bak_renk_tablosu();
RGB_ON(tR,tG,tB);
 
}
}
#pragma vector = ADC10_VECTOR     
__interrupt void ADC10_ISR (void){       
    adcdeger = ADC10MEM;            
    sicaklik1 = ((adcdeger*3300)/1024);  
    sicaklik = sicaklik1/10;            
   }
