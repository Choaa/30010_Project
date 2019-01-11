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

void setLeeXd(int color) {

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

    switch(color) {
        case 0 : //BLACK
            GPIOA->ODR |= (0x0001 << 9);
            GPIOB->ODR |= (0x0001 << 4);
            GPIOC->ODR |= (0x0001 << 7);
            break;
        case 1 : //RED
            GPIOA->ODR |= (0x0001 << 9);
            GPIOB->ODR &= (0x0000 << 4);
            GPIOC->ODR |= (0x0001 << 7);
            break;
        case 2 : //GREEN
            GPIOA->ODR |= (0x0001 << 9);
            GPIOB->ODR |= (0x0001 << 4);
            GPIOC->ODR &= (0x0000 << 7);
            break;
        case 3 : //BLUE
            GPIOA->ODR &= (0x0000 << 9);
            GPIOB->ODR |= (0x0001 << 4);
            GPIOC->ODR |= (0x0001 << 7);
            break;
        case 4 : //REDGREEN
            GPIOA->ODR |= (0x0001 << 9);
            GPIOB->ODR &= (0x0000 << 4);
            GPIOC->ODR &= (0x0000 << 7);
            break;
        case 5 : //REDBLUE
            GPIOA->ODR &= (0x0000 << 9);
            GPIOB->ODR &= (0x0000 << 4);
            GPIOC->ODR |= (0x0001 << 7);
            break;
        case 6 : //BLUEGREEN
            GPIOA->ODR &= (0x0000 << 9);
            GPIOB->ODR |= (0x0001 << 4);
            GPIOC->ODR &= (0x0000 << 7);
            break;
        case 7 : //WHITE
            GPIOA->ODR &= (0x0000 << 9);
            GPIOB->ODR &= (0x0000 << 4);
            GPIOC->ODR &= (0x0000 << 7);
            break;
    }
}

void timer_init() {
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
    int h,m,s,hs;
};

volatile struct time mytime;

void time_init(int h, int m, int s, int hs) {
    mytime.h = h;
    mytime.m = m;
    mytime.s = s;
    mytime.hs = hs;
}

void time_update() {
    {
    int hs = mytime.hs + 1;
    mytime.hs = hs;
    if (hs % 100 == 0) {
        mytime.hs = 0;
        int s = mytime.s + 1;
        mytime.s = s;
        if (s % 60 == 0) {
            mytime.s = 0;
            int m = mytime.m + 1;
            mytime.m = m;
            if (m % 60 == 0) {
                mytime.m = 0;
                int h = mytime.h + 1;
                mytime.h = h;
            }
        }
    }
}
}

int get_hs() {
    return mytime.hs;
}

int get_s() {
    return mytime.s;
}

int get_m() {
    return mytime.m;
}

int get_h() {
    return mytime.h;
}

void TIM2_IRQHandler(void) {
    time_update();
    TIM2->SR &= ~0x0001;
}
