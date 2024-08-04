#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>  // Gerekli veri türlerini tanimlar

void SysTick_Init(void);
void Delay_ms(uint32_t ms);

#endif // DELAY_H
