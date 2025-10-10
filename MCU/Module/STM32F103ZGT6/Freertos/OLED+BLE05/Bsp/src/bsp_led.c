#include "bsp_led.h"

void LED_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPEEN;

    GPIOB->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
    GPIOB->CRL |=  (GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0);

    GPIOE->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5);
    GPIOE->CRL |=  (GPIO_CRL_MODE5_1 | GPIO_CRL_MODE5_0);

    GPIOB->ODR |= GPIO_ODR_ODR5;  
    GPIOE->ODR |= GPIO_ODR_ODR5;    
}

void LED0_On(void) {
    GPIOB->BSRR = GPIO_BSRR_BR5; 
}

void LED0_Off(void) {
    GPIOB->BSRR = GPIO_BSRR_BS5; 
}

void LED1_On(void) {
    GPIOE->BSRR = GPIO_BSRR_BR5;
}

void LED1_Off(void) {
    GPIOE->BSRR = GPIO_BSRR_BS5;
}

void LED0_Toggle(void) {
    GPIOB->ODR ^= GPIO_ODR_ODR5;    
}

void LED1_Toggle(void) {
    GPIOE->ODR ^= GPIO_ODR_ODR5;    
}
