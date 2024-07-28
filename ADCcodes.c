#include "stm32f10x.h"                  // Device header

void GPIOconfig(){
    GPIO_InitTypeDef GpioStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GpioStructure.GPIO_Pin = GPIO_Pin_0; // PA0 pinini kullanacagiz
    GpioStructure.GPIO_Mode = GPIO_Mode_AIN; // Analog giris olarak yapilandir
    // Hiz ayari gerekli degil, çünkü okuma yapilacak

    GPIO_Init(GPIOA, &GpioStructure);
}

void ADCconfig(){
    ADC_InitTypeDef ADCstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // ADC1 saatini etkinlestir

    ADCstructure.ADC_ContinuousConvMode = ENABLE; // Sürekli dönüsüm modu
    ADCstructure.ADC_DataAlign = ADC_DataAlign_Right; // MSB en anlamli bit nereye dayali olsun
    ADCstructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // Tetikleyici yok
    ADCstructure.ADC_Mode = ADC_Mode_Independent;
    ADCstructure.ADC_NbrOfChannel = 1;
    ADCstructure.ADC_ScanConvMode = DISABLE;

    ADC_Init(ADC1, &ADCstructure);
    ADC_Cmd(ADC1, ENABLE);
    
    // ADC kalibrasyonu
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

// ADC okuma fonksiyonu
uint16_t adcRead(){
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); // PA0 pinini ADC kanali olarak yapilandir

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    // Dönüsüm tamamlanana kadar bekle
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

    return ADC_GetConversionValue(ADC1);
}

uint16_t dataAdcVal = 0;

int main(){
    GPIOconfig();
    ADCconfig();

    while(1){
        dataAdcVal = adcRead();
        // Okunan ADC degerini kullan
    }
}
