#include "stm32f0xx.h"
#include "gpio.h"

//------------------------------Функция настройки портов ввода/вывода-------------------------------------------

void GPIO_init(void)
{
	RCC->AHBENR |= (1 << 17); 			// Тактирование порта A
	RCC->AHBENR |= (1 << 18); 			// Тактирование порта B
	RCC->AHBENR |= (1 << 19);  			// Тактирование порта C
	
	// Настройка выводов ультразвукового датчика и пьезоэлемента
	
	// Настройка вывода PA6 (Вывод ECHO)
	
	GPIOA->MODER |= (1 << 13); 			// Установка вывода PA6 как альтернативная функция
	GPIOA->OTYPER |= (1 << 6);    	// Установка вывода в режим open-drain
	GPIOA->PUPDR |= (1 << 12);  		// Установка вывода с подтяжкой к питанию
	GPIOA->AFR[0] |= 1 << 6 * 4;		// Альтернативаня функция AF1
	
	// Настройка вывода PA7 (Вывод TRIG)
	
	GPIOA->MODER |= (1 << 14);     		// Установка вывода PA7 как выход
	GPIOA->OTYPER &= ~(1 << 7);    		// Установка вывода в режим push-pull
	GPIOA->OSPEEDR &= ~(1 << 14);  		// Установка вывода со скоростью работы Low
	GPIOA->PUPDR &= ~(1 << 14);    		// Установка вывода без подтяжки к земле или питанию
	
	// Настройка вывода PA8 (Вывод пьезоэлемента)
	
	GPIOA->MODER |= (1 << 16);     		// Установка вывода PA8 как выход
	GPIOA->OTYPER &= ~(1 << 8);    		// Установка вывода в режим push-pull
	GPIOA->OSPEEDR &= ~(1 << 16);  		// Установка вывода со скоростью работы Low
	GPIOA->PUPDR &= ~(1 << 16);    		// Установка вывода без подтяжки к земле или питанию
	
	// Настройка светодиодов на плате STM32F0
	
	// Настройка вывода PC8 (Синий светодиод)
	
	GPIOC->MODER |= (1 << 16);     		// Установка вывода PC8 как выход
	GPIOC->OTYPER &= ~(1 << 8);    		// Установка вывода в режим push-pull
	GPIOC->OSPEEDR &= ~(1 << 16);  		// Установка вывода со скоростью работы Low
	GPIOC->PUPDR &= ~(1 << 16);    		// Установка вывода без подтяжки к земле или питанию
	
	// Настройка вывода PC9 (зеленый светодиод)
	
	GPIOC->MODER |= (1 << 18);     		// Установка вывода PC9 как выход
	GPIOC->OTYPER &= ~(1 << 9);    		// Установка вывода в режим push-pull
	GPIOC->OSPEEDR &= ~(1 << 18);  		// Установка вывода со скоростью работы Low
	GPIOC->PUPDR &= ~(1 << 18);    		// Установка вывода без подтяжки к земле или питанию
	
	// Настройка выводов SPI для дисплея

	// Настройка вывода MOSI (PB15)

	GPIOB->MODER |= (1U << 31); 				// Установка вывода PB15 как альтернативная функция
	GPIOB->OTYPER &= ~(1 << 15);    		// Установка вывода в режим push-pull
	GPIOB->AFR[1] |= 0 << (15 - 8) * 4;	// Альтернативная функция согласно даташиту
	
	// Настройка вывода SCK (PB13)
	
	GPIOB->MODER |= (1 << 27); 					// Установка вывода PB13 как альтернативная функция
	GPIOB->OTYPER &= ~(1 << 13);    		// Установка вывода в режим push-pull
	GPIOB->AFR[1] |= 0 << (13 - 8) * 4;	// Альтернативная функция согласно даташиту
	
	// Настройка вывода NSS (PB12)
	
	GPIOB->MODER |= (1 << 24); 					// Установка вывода PB12 как выход
	GPIOB->OSPEEDR &= ~(1 << 24);   		// Установка вывода со скоростью работы Low
	GPIOB->PUPDR |= (1 << 24); 					// Установка подтяжки вывода к питанию
	GPIOB->OTYPER &= ~(1 << 12);    		// Установка вывода в режим push-pull
	
	// Настройка выводов дисплея
	
	// Настройка вывода RST (PA0)
	
	GPIOA->MODER |= (1 << 0);     		// Установка вывода PA0 как выход
	GPIOA->OTYPER &= ~(1 << 0);    		// Установка вывода в режим push-pull
	GPIOA->OSPEEDR &= ~(1 << 0);  		// Установка вывода со скоростью работы Low
	GPIOA->PUPDR &= ~(1 << 0);    		// Установка вывода без подтяжки к земле или питанию

	// Настройка вывода DC (PA1)
	
	GPIOA->MODER |= (1 << 2);     		// Установка вывода PA1 как выход
	GPIOA->OTYPER &= ~(1 << 1);    		// Установка вывода в режим push-pull
	GPIOA->OSPEEDR &= ~(1 << 2);  		// Установка вывода со скоростью работы Low
	GPIOA->PUPDR &= ~(1 << 2);    		// Установка вывода без подтяжки к земле или питанию
	
	// Настройка вывода BL (PA2)
	
	GPIOA->MODER |= (1 << 4);     		// Установка вывода PA2 как выход
	GPIOA->OTYPER &= ~(1 << 2);    		// Установка вывода в режим push-pull
	GPIOA->OSPEEDR &= ~(1 << 4);  		// Установка вывода со скоростью работы Low
	GPIOA->PUPDR &= ~(1 << 4);    		// Установка вывода без подтяжки к земле или питанию
}
