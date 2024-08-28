#include "stm32f10x.h"                  // Device header

void gpioConf(){//gpio A0 pinini ayarliyoruz 
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef gpioExtStructure;
	gpioExtStructure.GPIO_Mode=GPIO_Mode_IPD;
	gpioExtStructure.GPIO_Pin=GPIO_Pin_0;
	gpioExtStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&gpioExtStructure);
	
}

void ExtiConf(){//A0 pinine kesme uyguluyoruz
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
EXTI_InitTypeDef ExtStructure;
	ExtStructure.EXTI_Line=EXTI_Line0;
	ExtStructure.EXTI_LineCmd=ENABLE;
	ExtStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	ExtStructure.EXTI_Trigger=EXTI_Trigger_Rising;
	
	EXTI_Init(&ExtStructure);

	// INTERRUPT Kullanmast için Nvic Nested interrupt controlleri açmak lazim 
	
	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel=EXTI0_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority=1;
	nvicStructure.NVIC_IRQChannelSubPriority=0;
	nvicStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&nvicStructure);
	
}
void EXTI0_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        // Do something when the interrupt occurs

        // Clear the interrupt pending bit
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

int main(void) {
    ExtiConf();
		gpioConf();
	
    while (1) {
       
    }
}
