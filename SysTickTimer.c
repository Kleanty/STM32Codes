#include "stm32f10x.h"                  // Device header


uint32_t counter=0;
void gpioConfig(){
	
	GPIO_InitTypeDef gpioStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	gpioStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	gpioStructure.GPIO_Pin=GPIO_Pin_9;
	gpioStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&gpioStructure);

}

void SysTick_Handler(){
	if(counter>0){
		counter--;
	}
}

void delay_ms(uint16_t time){
counter=time;
	while(counter);
	
}

int main(){
gpioConfig();
SystemCoreClockUpdate();
SysTick_Config(SystemCoreClock/1000);//1ms
	

}