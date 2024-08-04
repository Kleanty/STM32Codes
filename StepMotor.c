#include "stm32f10x.h"                  // Cihaz basligi
#include "delay.h"                      // Gecikme fonksiyonlari için baslik dosyasi

// Adim motoruna bagli GPIO pinlerini tanimla
#define STEP_PIN_1 GPIO_Pin_3  // Mavi
#define STEP_PIN_2 GPIO_Pin_2  // Pembe
#define STEP_PIN_3 GPIO_Pin_1  // Mavi
#define STEP_PIN_4 GPIO_Pin_0  // Turuncu
#define STEP_PORT GPIOA

void GPIO_Config(void);
void StepMotor_Setup(void);
void StepMotor_Step(uint8_t step);

int main(void)
{
    GPIO_Config();
    
    // SysTick zamanlayicisini baslat
    SysTick_Init();
    
    // Adim motorunu yapilandir
    StepMotor_Setup();
    
    while (1)
    {
        // Tam adim dizisi
        for (int i = 0; i < 4; i++)
        {
            StepMotor_Step(i);
            Delay_ms(500);  // Motor hizini ayarlamak için gecikmeyi degistir
        }
    }
}

void GPIO_Config(void)
{
    // Adim motoru kontrolü için GPIO'yu baslat
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = STEP_PIN_1 | STEP_PIN_2 | STEP_PIN_3 | STEP_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(STEP_PORT, &GPIO_InitStructure);
}

void StepMotor_Setup(void)
{
    // Tüm motor pinlerini baslangiçta düsük seviyeye ayarla
    GPIO_ResetBits(STEP_PORT, STEP_PIN_1 | STEP_PIN_2 | STEP_PIN_3 | STEP_PIN_4);
}

void StepMotor_Step(uint8_t step)
{
    // Tam adim dizisi: A-B-C-D (bir bobin açik, digerleri kapali)
    switch (step)
    {
        case 0:
            GPIO_SetBits(STEP_PORT, STEP_PIN_4);  // Turuncu
            GPIO_ResetBits(STEP_PORT, STEP_PIN_1 | STEP_PIN_2 | STEP_PIN_3);
            break;
        case 1:
            GPIO_SetBits(STEP_PORT, STEP_PIN_3);  // Mavi
            GPIO_ResetBits(STEP_PORT, STEP_PIN_1 | STEP_PIN_2 | STEP_PIN_4);
            break;
        case 2:
            GPIO_SetBits(STEP_PORT, STEP_PIN_2);  // Pembe
            GPIO_ResetBits(STEP_PORT, STEP_PIN_1 | STEP_PIN_3 | STEP_PIN_4);
            break;
        case 3:
            GPIO_SetBits(STEP_PORT, STEP_PIN_1);  // Mavi
            GPIO_ResetBits(STEP_PORT, STEP_PIN_2 | STEP_PIN_3 | STEP_PIN_4);
            break;
    }
}
