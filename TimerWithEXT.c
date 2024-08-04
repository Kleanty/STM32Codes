#include "stm32f10x.h" // Device header

void gpioConfig()
{
    GPIO_InitTypeDef gpioStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    gpioStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10; // A8, A9, A10 pinleri
    gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &gpioStructure);
}

void timerConfig()
{
    TIM_TimeBaseInitTypeDef timerStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    timerStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerStructure.TIM_RepetitionCounter = 0;
    timerStructure.TIM_Period = 3999; // 2000 Hz / 4000 = 0.5 Hz => 2 saniye
    timerStructure.TIM_Prescaler = 35999; // 72 MHz / 36000 = 2000 Hz

    TIM_TimeBaseInit(TIM2, &timerStructure);
    TIM_Cmd(TIM2, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // TIM2 kesmesi
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // Ana öncelik seviyesi
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // Alt öncelik seviyesi
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // Kesme etkinlestir
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // Kesme etkinlestir
}

void toggle_led(void)
{
    uint16_t ledFlag = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
    if (ledFlag == (uint16_t)Bit_SET) {
        GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
    } else {
        GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        toggle_led();
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}

int main()
{
    SystemInit(); // Sistem saatini ve diger ayarlari baslat
    gpioConfig();
    timerConfig();

    while (1)
    {
        // Ana döngüde yapilacak islemler
    }
}
