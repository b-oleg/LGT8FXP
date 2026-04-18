#include "unity_config.h"
#include <lgt/io.h>
#include <lgt/clk.h>
#include <avr/interrupt.h>

#define baud 1000000l

volatile uint32_t unity_ms_counter = 0;

ISR(TIMER0_COMPA_vect) {
    unity_ms_counter++;
}

void unityOutputStart() {
	// Внешний высокочастотный кварц
	clk_set_oscm();

	// Инициализация UART для вывода результатов тестов
    UBRR0 = (uint16_t) ((F_CPU + baud * 4L) / (baud * 8L) - 1);
    UCSR0A = (1 << U2X0);
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // Инициализация Timer0 для измерения времени (1 мс)
    TCCR0A = (1 << WGM01); // CTC mode
    TCCR0B = (1 << CS02); // Prescaler 256
    OCR0A = 117; // Для 1 мс при 30MHz / 256 = 117 187,5
    TIMSK0 = (1 << OCIE0A); // Enable compare interrupt
    sei(); // Enable global interrupts
}

void unityOutputChar(char c) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

void unityOutputFlush(){}

void unityOutputComplete() {}

uint32_t unityClockMs() {
    return unity_ms_counter;
}
