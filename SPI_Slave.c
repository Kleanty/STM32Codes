#include "stm32f10x.h"

void SPI_Slave_Init(void) {
    // SPI ve GPIO konfigürasyonu için gerekli saat sinyallerini açar
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    
    // SCK (PA5), MOSI (PA7) ve NSS (PA4) pinlerini giris olarak ayarlar
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // MISO (PA6) pinini alternatif fonksiyon çikisi olarak ayarlar
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    SPI_InitTypeDef SPI_InitStruct;
    
    // SPI yapilandirmasini yapar
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  // Tam çift yönlü veri yolu
    SPI_InitStruct.SPI_Mode = SPI_Mode_Slave;  // Slave modunda çalisir
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;  // Veri uzunlugu 8 bit
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;  // Saat sinyali bosta düsük seviyede
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;  // Ilk saat kenarinda veri yakalama
    SPI_InitStruct.SPI_NSS = SPI_NSS_Hard;  // NSS pinini donanim kontrol eder
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;  // En yüksek bit ilk gönderilir
    SPI_InitStruct.SPI_CRCPolynomial = 7;  // CRC polinomu
    SPI_Init(SPI1, &SPI_InitStruct);

    // SPI'yi etkinlestirir
    SPI_Cmd(SPI1, ENABLE);
}

uint8_t SPI_Slave_Receive(void) {
    // Veri alinincaya kadar bekler
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI1);  // Alinan veriyi döndürür
}

int main(void) {
    SPI_Slave_Init();  // SPI slave'i baslatir

    while (1) {
        uint8_t received_data = SPI_Slave_Receive();  // Veriyi al
        // Alinan veri ile yapilacak islemler
    }
}
