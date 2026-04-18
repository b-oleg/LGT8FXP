#include <lgt/io.h>
#include <lgt/clk.h>
#include <lgt/ports.h>
#include <util/delay.h>

int main() {
    clk_set_oscm();			// external crystal
	
    PDB.B5 = 1; 			// PB5 - output

    while (1) {
        POB.B5 = 1;
        _delay_ms(500);
        POB.B5 = 0;
        _delay_ms(500);
    }
    return 0;
}

