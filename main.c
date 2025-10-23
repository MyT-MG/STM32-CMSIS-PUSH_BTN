#include "stm32f1xx.h"

void delay(int t);

int main(void) {
    // 1. Enable clock for GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // 2. Configure PA0 as Input with Pull-up
    GPIOA->CRL &= ~(0xF << (0 * 4));   // Clear bits
    GPIOA->CRL |=  (0x8 << (0 * 4));   // CNF=10, MODE=00 (Input Pull-up)
    GPIOA->ODR |=  (1 << 0);           // Pull-up active

    // 3. Configure PA1 as Output push-pull, 2 MHz
    GPIOA->CRL &= ~(0xF << (1 * 4));
    GPIOA->CRL |=  (0x2 << (1 * 4));   // CNF=00, MODE=10

    while (1) {
        int btn_state = (GPIOA->IDR & (1 << 0)); // Read PA0

        if (btn_state == 0) {    // Button pressed
            GPIOA->ODR |= (1 << 1);   // LED ON
        }
        else {
            GPIOA->ODR &= ~(1 << 1);   // LED OFF
        }

        delay(50); // crude debounce
    }
}

void delay(int t) {
    for (int i = 0; i < 800 * t; i++){
    	__NOP();
    }
}
