#include "stm32f10x.h"  // Device header

void gpioConfig() {
    GPIO_InitTypeDef gpioStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    gpioStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // Alternate Function Push Pull for PWM
    gpioStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpioStructure);
}

void timerConfig() {
    TIM_TimeBaseInitTypeDef timerStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); // TIM1 saat sinyali etkinlestir

    timerStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerStructure.TIM_Period = 3999; // Period for 4 kHz (0.25 ms)
    timerStructure.TIM_Prescaler = 71; // Prescaler for 1 MHz base frequency (assuming 72 MHz system clock)
    TIM_TimeBaseInit(TIM1, &timerStructure);

    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE); // TIM1 çikislarini etkinlestir
}

void pwmConfig() {
    TIM_OCInitTypeDef pwmStructure;
    pwmStructure.TIM_OCMode = TIM_OCMode_PWM1;
    pwmStructure.TIM_OutputState = TIM_OutputState_Enable;
    pwmStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    // PA9 - TIM1 Channel 2
    pwmStructure.TIM_Pulse = 1999; // 50% duty cycle
    TIM_OC2Init(TIM1, &pwmStructure);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // PA10 - TIM1 Channel 3
    pwmStructure.TIM_Pulse = 999; // 50% duty cycle
    TIM_OC3Init(TIM1, &pwmStructure);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // PA11 - TIM1 Channel 4
    pwmStructure.TIM_Pulse = 200; // 50% duty cycle
    TIM_OC4Init(TIM1, &pwmStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
}

int main() {
    gpioConfig();
    timerConfig();
    pwmConfig();

    while (1) {
        // Infinite loop
    }
}
