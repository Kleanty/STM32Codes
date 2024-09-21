#ifndef INC_4X3KEYPADLIB_H_
#define INC_4X3KEYPADLIB_H_

#include "main.h"
#include "stm32f4xx_hal.h"  // STM32 HAL kütüphanesi
#include <stdio.h>
// Define the pin connections according to your setup
#define ROW1_Pin GPIO_PIN_15
#define ROW1_GPIO_Port GPIOD
#define ROW2_Pin GPIO_PIN_12
#define ROW2_GPIO_Port GPIOF
#define ROW3_Pin GPIO_PIN_13
#define ROW3_GPIO_Port GPIOF
#define ROW4_Pin GPIO_PIN_9
#define ROW4_GPIO_Port GPIOE
#define COLUMN1_Pin GPIO_PIN_11
#define COLUMN1_GPIO_Port GPIOE
#define COLUMN2_Pin GPIO_PIN_14
#define COLUMN2_GPIO_Port GPIOF
#define COLUMN3_Pin GPIO_PIN_13
#define COLUMN3_GPIO_Port GPIOE

#define ROWSIZE 4
#define COLUMNSIZE 3


void keypadINIT(void);
void readKeypad(uint8_t *keyPressed);

#endif /* INC_4X3KEYPADLIB_H_ */
