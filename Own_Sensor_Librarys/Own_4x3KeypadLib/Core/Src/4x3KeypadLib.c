#include "4x3KeypadLib.h"

// Keypad'in tuşlarını temsil eden karakter matrisi
char keyMap[ROWSIZE][COLUMNSIZE] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

GPIO_TypeDef *rowsports[4] = {GPIOD,GPIOF,GPIOF,GPIOE};
GPIO_TypeDef *columnsPorts[3] = {GPIOE,GPIOF,GPIOE};

uint16_t rowsPins[4] = { GPIO_PIN_15, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_9 };
uint16_t columnsPins[3] = { GPIO_PIN_11, GPIO_PIN_14, GPIO_PIN_13 };

// Keypad'i başlatma işlevi
void keypadINIT() {
	// pin clocklarını açmayı unutmayın
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

    // Satır pinleri için yapılandırma (Çıkış)
    GPIO_InitTypeDef outputConfig = {0};
    outputConfig.Mode = GPIO_MODE_OUTPUT_PP; // Push-Pull çıkış modu
    outputConfig.Pull = GPIO_NOPULL;         // Pull-up/down yok
    outputConfig.Speed = GPIO_SPEED_FREQ_MEDIUM;


    // Satırları yapılandır
    outputConfig.Pin = ROW1_Pin;
    HAL_GPIO_Init(ROW1_GPIO_Port, &outputConfig);

    outputConfig.Pin = ROW2_Pin;
    HAL_GPIO_Init(ROW2_GPIO_Port, &outputConfig);

    outputConfig.Pin = ROW3_Pin;
    HAL_GPIO_Init(ROW3_GPIO_Port, &outputConfig);

    outputConfig.Pin = ROW4_Pin;
    HAL_GPIO_Init(ROW4_GPIO_Port, &outputConfig);

    // Sütun pinleri için yapılandırma (Giriş, Pull-up aktif)
    GPIO_InitTypeDef inputConfig = {0};
    inputConfig.Mode = GPIO_MODE_INPUT;     // Giriş modu
    inputConfig.Pull = GPIO_PULLUP;         // Pull-up etkinleştir

    // Sütunları yapılandır
    inputConfig.Pin = COLUMN1_Pin;
    HAL_GPIO_Init(COLUMN1_GPIO_Port, &inputConfig);

    inputConfig.Pin = COLUMN2_Pin;
    HAL_GPIO_Init(COLUMN2_GPIO_Port, &inputConfig);

    inputConfig.Pin = COLUMN3_Pin;
    HAL_GPIO_Init(COLUMN3_GPIO_Port, &inputConfig);
}


// Keypad'den tuş okuma işlevi
// Keypad'den tuş okuma işlevi
void readKeypad(uint8_t *keyPressed) {
    *keyPressed = 0xFF;  // Varsayılan olarak basılı tuş yok

    for (int row = 0; row < ROWSIZE; row++) {
        // Aktif satırı LOW yap (aktif satır)
        HAL_GPIO_WritePin(rowsports[row], rowsPins[row], GPIO_PIN_RESET);

        // Küçük bir gecikme (Debouncing)
        HAL_Delay(5);  // 5ms gecikme, ihtiyaç halinde ayarlanabilir

        // Her sütunu kontrol et (LOW olan sütunda tuş basılıdır)
        for (int col = 0; col < COLUMNSIZE; col++) {
            if (HAL_GPIO_ReadPin(columnsPorts[col], columnsPins[col]) == GPIO_PIN_RESET) {
                // Basılan tuşu kaydet
                *keyPressed = keyMap[row][col];

                // Tuş basıldığında geri kalan satırları kontrol etmeye gerek yok
                // Satırı tekrar HIGH yap
                HAL_GPIO_WritePin(rowsports[row], rowsPins[row], GPIO_PIN_SET);

                // Küçük bir gecikme, tuş basımını daha net göstermek için
                HAL_Delay(200);  // 200ms bekle, tuş basımını yakalamak için
                return;
            }
        }

        // Satırı tekrar HIGH yap
        HAL_GPIO_WritePin(rowsports[row], rowsPins[row], GPIO_PIN_SET);
    }
}
