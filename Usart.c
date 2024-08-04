#include "stm32f10x.h" // Device header

void gpioConfig(){
    GPIO_InitTypeDef gpioTXStructure;
    // Ben Stm32 bluePill kullaniyorum 
    // yani RX--PA3 TX--PA2  APB2 ye bagli A pini datashetten bakabilsrisiniz

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // TX PA2
    gpioTXStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    gpioTXStructure.GPIO_Pin = GPIO_Pin_2;
    gpioTXStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpioTXStructure);

    // RX (PA3) 
    GPIO_InitTypeDef gpioRXStructure;
    gpioRXStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    gpioRXStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &gpioRXStructure);
}

void UARTconfig(){ // USART 1 APB2 e bagli 
    
    USART_InitTypeDef usartStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    
    usartStructure.USART_BaudRate = 9600;
    usartStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usartStructure.USART_Parity = USART_Parity_No;
    usartStructure.USART_WordLength = USART_WordLength_8b;
    usartStructure.USART_StopBits = USART_StopBits_1;
    usartStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    
    USART_Init(USART1, &usartStructure);
    USART_Cmd(USART1, ENABLE);
}

void uartTransmit(char *string){
    while(*string) {
        while(!(USART1->SR & 0x00000040)); //register bosalasaya kardar bekle
        USART_SendData(USART1, *string);
        string++;
    }
}

int main(){
    gpioConfig();
    UARTconfig();    
    
    char message[] = "SA!";
    uartTransmit(message); //mesaji ilet
    
    while(1) {} 
}
