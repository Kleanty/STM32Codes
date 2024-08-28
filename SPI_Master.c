#include "stm32f10x.h"

void SPI_Master_Init(void) {
    // SPI ve GPIO konfigürasyonu için gerekli saat sinyallerini açar
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    
    // SCK (PA5), MOSI (PA7) ve NSS (PA4) pinlerini alternatif fonksiyon çikisi olarak ayarlar
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // MISO (PA6) pinini giris olarak ayarlar
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    SPI_InitTypeDef SPI_InitStruct;
    
    // SPI yapilandirmasini yapar
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  // Tam çift yönlü veri yolu
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;  // Master modunda çalisir
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;  // Veri uzunlugu 8 bit
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;  // Saat sinyali bosta düsük seviyede
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;  // Ilk saat kenarinda veri yakalama
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;  // NSS pinini yazilim kontrol eder
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;  // Baud hizi bölücü 16
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;  // En yüksek bit ilk gönderilir
    SPI_InitStruct.SPI_CRCPolynomial = 7;  // CRC polinomu
    SPI_Init(SPI1, &SPI_InitStruct);

    // SPI'yi etkinlestirir
    SPI_Cmd(SPI1, ENABLE);
}

void SPI_Master_Transmit(uint8_t data) {
    // Veri gönderilene kadar bekler
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, data);  // Veriyi gönderir

    // Verinin alici tarafindan alindigindan emin olmak için bekler
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    SPI_I2S_ReceiveData(SPI1);  // Gelen veriyi okur (sadece TX islemi için zorunlu degil)
}

int main(void) {
    SPI_Master_Init();  // SPI master'i baslatir

    while (1) {
        SPI_Master_Transmit(0x55);  // Örnek veri gönderimi
        for (int i = 0; i < 100000; i++);  // Basit gecikme
    }
}
