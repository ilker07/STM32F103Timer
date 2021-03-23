

#include "stm32f10x.h"
#include "lcd.h"                  // Device header
#include "delay.h"


void ilkKomutlar(unsigned char komut);

void lcd_komut_yolla(unsigned char komut)
{
	
	GPIOB->BRR =1<<0;//RS reset.
	
	GPIOB->BSRR =1<<1;//E set.
	GPIOA->ODR = komut;
	delay_ms(2);//1 mikro sn.
	GPIOB->BRR =1<<1;//E reset.
	delay_ms(2);
	GPIOA->BRR = 0x000000F0;//Yüksek 4 bit silindi.
	delay_ms(2);//100 mikro sn.
	
	komut=komut<<4;
	
	GPIOB->BSRR =1<<1;//E set.
	GPIOA->ODR = komut;
	delay_ms(2);//1 mikro sn.
  GPIOB->BRR =1<<1;//E reset.
	delay_ms(2);
	GPIOA->BRR = 0x000000FF;//Düsük 4 bit silindi.
	
 
}

void lcd_basla()
{
	
	ilkKomutlar(0x30);
  delay_ms(5);//4,1ms gerek
  ilkKomutlar(0x30);
  delay_ms(1);//150 mikrosaniye gerek.
	ilkKomutlar(0x30);
	delay_ms(1);
	ilkKomutlar(0x20);
	delay_ms(1);
	
  lcd_komut_yolla(0x02);
  delay_ms(2);
  lcd_komut_yolla(0x28);
  delay_ms(2);
  lcd_komut_yolla(0x0C);
  delay_ms(2);
  lcd_komut_yolla(0x01);
  delay_ms(2);
  lcd_komut_yolla(0x06);
  delay_ms(2);

}
void lcdHucreyeGit(unsigned int satir,unsigned int sutun)
{
  if(satir==1)
  {
    sutun--;
    lcd_komut_yolla(0x80+sutun);
    
    
  }
  else if(satir==2)
  {
    sutun--;
    lcd_komut_yolla(0xC0+sutun);
    
  }
	
}


void lcd_veri_yaz(unsigned char	veri)
{
  GPIOB->BSRR =1<<0;//RS reset.
	
	GPIOB->BSRR =1<<1;//E set.
	GPIOA->ODR = veri;
	delay_ms(4);//1 mikro sn.
	GPIOB->BRR =1<<1;//E reset.
	delay_ms(2);
	GPIOA->BRR = 0x000000F0;//Yüksek 4 bit silindi.
	delay_ms(4);//100 mikro sn.
	
	veri=veri<<4;
	
	GPIOB->BSRR =1<<1;//E set.
	GPIOA->ODR = veri;
	delay_ms(4);//1 mikro sn.
  GPIOB->BRR =1<<1;//E reset.
	delay_ms(2);
	GPIOA->BRR = 0x000000FF;//Düsük 4 bit silindi.
}
void ilkKomutlar(unsigned char komut)
{
	GPIOB->BRR =1<<0;//RS reset.
	
	GPIOB->BSRR =1<<1;//E set.
	GPIOA->ODR = komut;
	delay_ms(2);//1 mikro sn.
	GPIOB->BRR =1<<1;//E reset.
	delay_ms(2);
	GPIOA->BRR = 0x000000F0;//Yüksek 4 bit silindi.
	delay_ms(2);//100 mikro sn.
}
void portAyarlari()
{
	
	
	RCC->APB2ENR |=1<<2;//A portu aktif edildi.
	RCC->APB2ENR |=1<<3;//B portu aktif edildi.
	RCC->APB2ENR  |=1<<11; //TIMER1 AKTIF.
	
	GPIOA->CRL &=0x00;//A portu temizlendi.
	GPIOA->CRL =0x22222222;//A0 ve A2 Output.

	
	
	GPIOB->CRL &=0x00;//B portu temizlendi.
	
	GPIOB->CRL =0x22222222;//B7,B6,B5,B4 Output.
	
	GPIOA->ODR =0x00;//B portu 0 landi.
	GPIOB->ODR =0x00;//B portu 0 landi.
	
	
	
	delay_ms(20);
	
	
}



void lcd_yaz(char *kelime) {
 uint8_t i=0;
 
 while(kelime[i] != '\0') {
  lcd_veri_yaz(kelime[i]);
  i++;
 }
 
 
}


uint8_t kelimeBoyut(char *kelime) {
 uint8_t i=0;
 
 while(kelime[i] != '\0') {
  i++;
 }
 
 return i;
}










