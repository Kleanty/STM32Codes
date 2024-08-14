#include "stm32f10x.h"  // Cihaz basligi

/* ADC degerlerini depolamak için tampon bellek volatile,
volatile donanim kesintileri veya baska bir islemin degistirebilecegi bir degiskenin, derleyici optimizasyonlarindan korunmasini saglar.*/

volatile uint16_t adcBuffer[1];

void gpioConfig() {
    GPIO_InitTypeDef adcStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    adcStructure.GPIO_Mode = GPIO_Mode_AIN;
    adcStructure.GPIO_Pin = GPIO_Pin_0;
    adcStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &adcStructure);
}

void adcConfig() {
    ADC_InitTypeDef ADCstructure;

    // ADC1 için saat sinyalini etkinlestir
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    // ADC1 konfigürasyonu
    ADCstructure.ADC_ContinuousConvMode = ENABLE;  // Sürekli okuma
    ADCstructure.ADC_DataAlign = ADC_DataAlign_Right;  //saga yatir
    ADCstructure.ADC_ScanConvMode = DISABLE;  // Tarama modu devre disi
    ADCstructure.ADC_NbrOfChannel = 1;  
    ADCstructure.ADC_ExternalTrigConv = ADC_ExternalTrigInjecConv_None;  // Harici tetikleme kapali
    ADCstructure.ADC_Mode = ADC_Mode_Independent;  // Bagimsiz mod
    
    ADC_Init(ADC1, &ADCstructure);
    ADC_Cmd(ADC1, ENABLE);  

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
}

void DMAconfig() {
    DMA_InitTypeDef DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
    // DMA1 Ayarlar i
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;  // ADC1 i Data Registere yazdiriyoruz
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)adcBuffer;      // Bellek adresi (ADC degerlerini depolamak için dizi)
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;               // Veri aktarim yönü Çevreselden bellege
    DMA_InitStructure.DMA_BufferSize = 1;                            // Aktarilacak veri sayisi
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // Çevresel adresi artirma devre disi
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;          // Bellek adresini artir
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                  // Sürekli veri aktarimi için döngüsel mod
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;              // Yüksek öncelik kafana göre ver 
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                     // memory ile isimiz yok
    
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1, ENABLE);
}

int main() {
    gpioConfig();  
    adcConfig();   
    DMAconfig();  
    
    while (1) {
       
    }
}
