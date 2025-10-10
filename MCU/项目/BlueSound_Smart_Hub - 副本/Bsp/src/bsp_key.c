#include "bsp_key.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void KEY_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPEEN | RCC_APB2ENR_IOPAEN;
	
    GPIOE->CRL &= ~(GPIO_CRL_MODE4 | GPIO_CRL_CNF4);
    GPIOE->CRL |=  (GPIO_CRL_CNF4_1);
    GPIOE->ODR |=  (GPIO_ODR_ODR4);
	
    GPIOE->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_CNF3);
    GPIOE->CRL |=  (GPIO_CRL_CNF3_1);
    GPIOE->ODR |=  (GPIO_ODR_ODR3);
	
    GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
    GPIOA->CRL |=  (GPIO_CRL_CNF0_1);
    GPIOA->ODR &= ~(GPIO_ODR_ODR0);
}

#define DEBUG_KEY_SCAN 0

uint8_t key_scan(void) {
    static uint8_t key_up = 1;
    if (key_up && (
            !(GPIOE->IDR & GPIO_IDR_IDR4) || 
            !(GPIOE->IDR & GPIO_IDR_IDR3) || 
             (GPIOA->IDR & GPIO_IDR_IDR0)   
        ))
    {
#if DEBUG_KEY_SCAN
        printf("raw PE4=%d PE3=%d PA0=%d\r\n",
               (GPIOE->IDR & GPIO_IDR_IDR4)?1:0,
               (GPIOE->IDR & GPIO_IDR_IDR3)?1:0,
               (GPIOA->IDR & GPIO_IDR_IDR0)?1:0);
#endif
        vTaskDelay(pdMS_TO_TICKS(10));
        key_up = 0;
        if (!(GPIOE->IDR & GPIO_IDR_IDR4)) return KEY0_PRESSED;
        else if (!(GPIOE->IDR & GPIO_IDR_IDR3)) return KEY1_PRESSED;
        else if (GPIOA->IDR & GPIO_IDR_IDR0) return KEY2_PRESSED;
    }
    else if (
        (GPIOE->IDR & GPIO_IDR_IDR4) &&
        (GPIOE->IDR & GPIO_IDR_IDR3) &&
        !(GPIOA->IDR & GPIO_IDR_IDR0)
    ) {
        key_up = 1;
    }
    return NO_KEY_PRESSED;
}
