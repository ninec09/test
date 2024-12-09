#include "stm32f4xx.h"



void ClockConfig(void){
unsigned int i;
  for (i=0;i<0x00100000;i++);
  RCC->CFGR |= 0x00009400;        												// AHB ve APB hizlari max
  RCC->CR |= 0x00010000;          												// HSE Xtal Osc Enable
  while (!(RCC->CR & 0x00020000));												// Xtal Osc stabilizasyon
  RCC->PLLCFGR = 0x07402A04;      												// PLL katsayilari ayarlandi.
  RCC->CR |= 0x01000000;          												// PLL start
  while(!(RCC->CR & 0x02000000)); 												// PLL ready wait
  FLASH->ACR = 0x00000605;        												// Flash ROM icin 5 Wait state secelim ve ART aktif
  RCC->CFGR |= 0x00000002;        												// CLK u PLL uzerinden besleyelim
  while ((RCC->CFGR & 0x0000000F) != 0x0000000A); 								// Besleninceye kadar bekle
  RCC->AHB1ENR |= 0x0000003F; 												// All Port Clock enable
}

int main(void) {

	ClockConfig();

	GPIOD->MODER		|=  (1UL << 12*2);
	GPIOD->OTYPER 		&= ~(1UL << 12*1);
	GPIOD->OSPEEDR		|=	(3UL << 12*2);
  	GPIOD->PUPDR	  	&= ~(3UL << 12*2);

	GPIOD->MODER		|=  (1UL << 13*2);
	GPIOD->OTYPER 		&= ~(1UL << 13*1);
	GPIOD->OSPEEDR		|=	(3UL << 13*2);
  	GPIOD->PUPDR	  	&= ~(3UL << 13*2);


    while (1) {
		GPIOD->ODR			|=	 (1UL << 13);
    }
}
