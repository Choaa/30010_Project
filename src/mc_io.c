#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "mc_io.h"
#include <stdlib.h>
#include <stdio.h>

#define ESC 0x1B

int16_t readIO() {

    // Enable clock for PA
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;

    // Joystick up
    GPIOA->MODER &= ~(0x00000003 << (4 * 2));
    GPIOA->MODER |= (0x00000000 << (4 * 2));

    GPIOA->PUPDR &= ~(0x00000003 << (4 * 2));
    GPIOA->PUPDR |= (0x00000002 << (4 * 2));

    uint16_t valu = GPIOA->IDR & (0x0001 << 4);

    // Enable clock for PB
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
    // Joystick down
    GPIOB->MODER &= ~(0x00000003 << (0 * 2));
    GPIOB->MODER |= (0x00000000 << (0 * 2));

    GPIOB->PUPDR &= ~(0x00000003 << (0 * 2));
    GPIOB->PUPDR |= (0x00000002 << (0 * 2));

    uint16_t vald = GPIOB->IDR & (0x0001 << 0);

    // Joystick center
    GPIOB->MODER &= ~(0x00000003 << (5 * 2));
    GPIOB->MODER |= (0x00000000 << (5 * 2));

    GPIOB->PUPDR &= ~(0x00000003 << (5 * 2));
    GPIOB->PUPDR |= (0x00000002 << (5 * 2));

    uint16_t valc = GPIOB->IDR & (0x0001 << 5);

    // Enable clock for PC
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC;

    // Joystick right
    GPIOC->MODER &= ~(0x00000003 << (0 * 2));
    GPIOC->MODER |= (0x00000000 << (0 * 2));

    GPIOC->PUPDR &= ~(0x00000003 << (0 * 2));
    GPIOC->PUPDR |= (0x00000002 << (0 * 2));

    uint16_t valr = GPIOC->IDR & (0x0001 << 0);
    if (valr > 0)
        valr = valr + 2;

    // Joystick left
    GPIOC->MODER &= ~(0x00000003 << (1 * 2));
    GPIOC->MODER |= (0x00000000 << (1 * 2));

    GPIOC->PUPDR &= ~(0x00000003 << (1 * 2));
    GPIOC->PUPDR |= (0x00000002 << (1 * 2));

    uint16_t vall = GPIOC->IDR & (0x0001 << 1);

    return (valu + vald + valc + valr + vall);
}

void RGB_init() {

    // BLUE - A9
    // Enable clock for PA
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;

    GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2));
    GPIOA->OSPEEDR |= (0x00000002 << (9 * 2));

    GPIOA->OTYPER &= ~(0x0001 << (9));
    GPIOA->OTYPER |= (0x0000 << (9));

    GPIOA->MODER &= ~(0x00000003 << (9 * 2));
    GPIOA->MODER |= (0x0000001 << (9 * 2));

    // RED - B4
    // Enable clock for PB
    RCC->AHBENR |= RCC_AHBPeriph_GPIOB;

    GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2));
    GPIOB->OSPEEDR |= (0x00000002 << (4 * 2));

    GPIOB->OTYPER &= ~(0x0001 << (4));
    GPIOB->OTYPER |= (0x0000 << (4));

    GPIOB->MODER &= ~(0x00000003 << (4 * 2));
    GPIOB->MODER |= (0x0000001 << (4 * 2));

    // GREEN - C7
    // Enable clock for PC
    RCC->AHBENR |= RCC_AHBPeriph_GPIOC;

    GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2));
    GPIOC->OSPEEDR |= (0x00000002 << (7 * 2));

    GPIOC->OTYPER &= ~(0x0001 << (7));
    GPIOC->OTYPER |= (0x0000 << (7));

    GPIOC->MODER &= ~(0x00000003 << (7 * 2));
    GPIOC->MODER |= (0x0000001 << (7 * 2));
}

void RGB_set(int color) {

    if (color == 0) {
        GPIOA->ODR |= (0x0001 << 9);
        GPIOB->ODR |= (0x0001 << 4);
        GPIOC->ODR |= (0x0001 << 7);
    }
    else if (color == 1) {
        GPIOA->ODR |= (0x0001 << 9);
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOC->ODR |= (0x0001 << 7);
    }
    else if (color == 2) {
        GPIOA->ODR |= (0x0001 << 9);
        GPIOB->ODR |= (0x0001 << 4);
        GPIOC->ODR &= ~(0x0001 << 7);
    }
    else if (color == 3) {
        GPIOA->ODR &= ~(0x0001 << 9);
        GPIOB->ODR |= (0x0001 << 4);
        GPIOC->ODR |= (0x0001 << 7);
    }
    else if (color == 4) {
        GPIOA->ODR |= (0x0001 << 9);
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOC->ODR &= ~(0x0001 << 7);
    }
    else if (color == 5) {
        GPIOA->ODR &= ~(0x0001 << 9);
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOC->ODR |= (0x0001 << 7);
    }
    else if (color == 6) {
        GPIOA->ODR &= ~(0x0001 << 9);
        GPIOB->ODR |= (0x0001 << 4);
        GPIOC->ODR &= ~(0x0001 << 7);
    }
    else if (color == 7) {
        GPIOA->ODR &= ~(0x0001 << 9);
        GPIOB->ODR &= ~(0x0001 << 4);
        GPIOC->ODR &= ~(0x0001 << 7);
    }
}

void time_init() {
    RCC->APB1ENR |= RCC_APB1Periph_TIM2;
    TIM2->CR1 = 0x000000000000000;
    TIM2->ARR = 0x9C3FF;
    TIM2->PSC = 0x0000;

    TIM2->DIER |= 0x0001;

    NVIC_SetPriority(TIM2_IRQn, 0);
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM2->CR1 |= 0x01;
}

struct time {
    int hs;
};

volatile struct time timer;

void time_set(int hs) {
    timer.hs = hs;
}

void time_update() {
    int hs = timer.hs + 1;
    timer.hs = hs;
}

int flag2 = 0;

void flag2_update() {
    if (flag2 == 0) {
        flag2 = 1;
    }
    else if (flag2 == 1) {
        flag2 = 0;
    }
}

int get_flag2() {
    return flag2;
}

int get_hs() {
    return timer.hs;
}

void TIM2_IRQHandler(void) {
    time_update();
    flag2_update();
    TIM2->SR &= ~0x0001;
}
