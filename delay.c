#include "delay.h"
#include "stm32f10x.h"  // STM32F10x baslik dosyasi

static __IO uint32_t TimingDelay;

void SysTick_Init(void) {
    // SysTick zamanlayicisini 1 ms olacak sekilde yapilandir
    if (SysTick_Config(SystemCoreClock / 1000)) {
        // Hata olusursa sonsuz döngüye gir
        while (1);
    }
}

void Delay_ms(uint32_t ms) {
    TimingDelay = ms;
    while (TimingDelay != 0);
}

void SysTick_Handler(void) {
    if (TimingDelay != 0) {
        TimingDelay--;
    }
}
