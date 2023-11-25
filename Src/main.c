#include "stm32f0xx.h"
#include "clock.h"
#include "gpio.h"
#include "ultrasonic.h"
#include "lcd.h"
#include <stdio.h>

extern int duty;
char buff[8]; // Буфер для вывода строки
int distance = 0; 

unsigned char dist[] = "Расстояние";

int main(void)
{
	Set_Clock(); 			// Настройки тактирования МК
	GPIO_init(); 			// Инициализация портов ввода-вывода
	TIM6_init();			// Инициализация таймера 6 (для задержки)
	TIM3_init();			// Инициализация таймера 3(для ультразвукового датчика)
	SPI_init();				// Инициализация шины (для дисплея)
	
	// Настройки для дисплея
	
	GPIOA->BSRR |= (1 << 0); 					// Установка сигнала сброса в 1
	Delay_ms(10);
	GPIOA->BSRR |= ((1 << 0) << 16); 	// Установка сигнала сброса в 0
	Delay_ms(10);
	GPIOA->BSRR |= (1 << 0); 					// Установка сигнала сброса в 1
	
	GPIOA->BSRR |= ((1 << 1) << 16); 	// Установка сигнала DC в 0 (Подстветка выключена)
	GPIOA->BSRR |= (1 << 2); 					// Установка сигнала BL в 1 (Подсветка включена)

	SPI_send(0x21); // Расширенная настройка
	SPI_send(0xD0); // Установка напряжения 
	SPI_send(0x20); // Обычная настройка
	SPI_send(0x0C); // Нормальный режим работы дисплея
	
	while(1)
	{
		// Настройки ультразвукового датчика
		
		GPIOA->BSRR |= (1 << 7); 					// Установка сигнала TRIG в 1
		Delay_us(10);
		GPIOA->BSRR |= ((1 << 7) << 16);  // Установка сигнала TRIG в 0
		
		distance = duty / 58;						  // Значение дальности в см
		Delay_ms(10);
		
		if (distance > 5 && distance < 15)
		{
				GPIOC->BSRR |= (1 << 9); 					// Включаем зеленый светодиод
				GPIOC->BSRR |= (1 << 24); 				// Выключаем синий светодиод
				GPIOA->BSRR |= ((1 << 8) << 16);	// Выключаем пьезоэлемент	
		}
		
		else if (distance >= 15)
		{
				GPIOC->BSRR |= (1 << 8);					// Включаем синий светодиод
				GPIOA->BSRR |= ((1 << 8) << 16);	// Выключаем пьезоэлемент	
		}
		
		else
		{
				GPIOC->BSRR |= (1 << 25); 			// Выключаем зеленый светодиод 
				GPIOA->BSRR |= (1 << 8);				// Включаем пьезоэлемент	
		}
		
		lcd_print(0,0, FONT_1X, (unsigned char*)dist); // Вывод на дисплей расстояния до объекта
	  sprintf(buff, "= %d см", distance);
		lcd_print(0,1, FONT_2X, (unsigned char*)buff); // Вывод на дисплей надпись
		Lcd_update(); 																 // Обновление дисплея (отправка данных)
		Delay_ms(500);
		Lcd_clear();																	 // Очистка дисплея
	
		//SystemCoreClockUpdate(); // Проверка частоты работы МК
	}
}
