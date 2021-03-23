

#include "stm32f10x.h"                  // Device header
#include "lcd.h"
#include "delay.h"
uint16_t sayac=0;

unsigned char harf=' ';
void  timer1_init(void);
void pin_init(void);




void TIM1_UP_IRQHandler(void)
{
	
  if(TIM1->SR & (1<<0))  //UIF 1 olmussa
	{
		TIM1->SR &=~(1<<0);//UIF Temizleme.
		sayac++;
		
		if(sayac<1000)			
			harf='a';
		
		 if(sayac>1000)
			harf='b';
			
		
		 if(sayac==2000 || sayac>2000)
			sayac=0;
		
	}
}

int main()
	
{
	
	delay_init();
	portAyarlari();
	lcd_basla();
	
	
	timer1_init();
	
	
	while(1)
	{
		
		lcdHucreyeGit(1,1);
		lcd_veri_yaz(harf);
	
	}
	
	
}


void timer1_init()
{

	
	
	
	TIM1->CCMR1 = 0;
	TIM1->RCR =0;
	TIM1->PSC =1;
	TIM1->ARR =35999;
	
	
	TIM1->CR1 |=1<<0;//ENABLE.
  NVIC->ISER[0] |=1<<25;
	TIM1->DIER |=1<<0;//INTERRUPT ENABLE.
	
	
}

