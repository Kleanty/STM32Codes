#include "stm32f10x.h"                  // Device header

void gpioConfig(){
GPIO_InitTypeDef gpioStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
gpioStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
gpioStructure.GPIO_Mode=GPIO_Mode_Out_PP;
gpioStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&gpioStructure);
	
	
}

void timerConfig(){
TIM_TimeBaseInitTypeDef timerStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
timerStructure.TIM_ClockDivision=1;
timerStructure.TIM_CounterMode=TIM_CounterMode_Up;
timerStructure.TIM_RepetitionCounter=0;//advanced counter degil ondan sifir verdik
	// core clock mhz gore hesaplamalar yapabilrisinz formullerine internetten bakin 
timerStructure.TIM_Prescaler=7199;
timerStructure.TIM_Period=9999;
	
	TIM_TimeBaseInit(TIM2,&timerStructure);
	TIM_Cmd(TIM2,ENABLE);
}

int main(){
	gpioConfig();
	timerConfig();
	while(1){
		
	}
	
}