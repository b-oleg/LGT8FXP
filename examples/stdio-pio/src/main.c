#include <lgt/io.h>
#include <lgt/clk.h>
#include <lgt/ports.h>
#include <lgt/pgmspace.h>
#include <util/delay.h>

#include <stdio.h>

int uart_getchar(FILE *stream) {
	loop_until_bit_is_set(UCSR0A, RXC0);
	char c = UDR0;
	return c;
}

static int uart_putchar(char c, FILE *stream) {
	if (c == '\n') uart_putchar('\r', stream);
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

void uart_init(uint32_t baud) {
	UBRR0 = (uint16_t) ((F_CPU + baud * 4L) / (baud * 8L) - 1); // +0.5 for round
	UCSR0A = (1 << U2X0);
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);	// Enable TX and RX
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);	// Set frame format: 8data, 1stop bit
}

#define D(str, ...)	printf_P(PSTR(str "\n"), ##__VA_ARGS__)

int main() {
    clk_set_oscm();			// external crystal
	uart_init(1000000);		// 1mbit
	stdout = stdin = &uart_stdout;

	PDB.B5 = 1; 			// PB5 - output

	D("\nHello, World!");
	D("stdio example with printf and scanf");

	printf_P(PSTR("Value: %d, Hex: 0x%X, Float: %.2f\n"), 123, 0xABCD, 3.14);

	char key;

	while (1) {
    	printf_P(PSTR("\nPress any key: "));
	    scanf("%c", &key);
        POB.B5 = 1;
		printf_P(PSTR("\nYou entered: '%c' (0x%02X)\n"), key, key);
        POB.B5 = 0;
    }
    return 0;
}

