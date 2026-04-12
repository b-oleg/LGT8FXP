#include <lgt/io.h>
#include <lgt/clk.h>
#include <util/delay.h>

int main() {
    clk_set_oscm();
	
    DDRB = 0xff;

    while (1) {
        PORTB ^= 0xff;
        _delay_ms(50);
    }
    return 0;
}

