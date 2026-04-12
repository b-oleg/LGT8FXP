#include <lgt/io.h>
#include <lgt/clk.h>
#include <avr/cpufunc.h>
#include <util/delay.h>

void clk_set_enable(clk_t clk) {
	uint8_t reg = PMCR | clk;
	PMCR = (1 << PMCE);
	PMCR = reg;
}

void clk_set_disable(clk_t clk) {
	uint8_t reg = PMCR & (~clk);
	PMCR = (1 << PMCE);
	PMCR = reg;
}

void clk_set_mclk(mclk_t mclk) {
	uint8_t reg = (PMCR & 0x9f) | ((mclk & 0x3) << 5);
	PMCR = (1 << PMCE);
	PMCR = reg;
}

void clk_set_div(clk_div_t clk_div) {
	uint8_t clkpr = 0x80 | (clk_div & 0xf);
	CLKPR = (1 << WCE);
	CLKPR = clkpr;
}

void clk_set_oscm() {
	clk_set_enable(CLK_OSCM);	// enable clock source
	_delay_ms(1);				// wait for clock stable
	clk_set_mclk(MCLK_OSCM);	// set main clock
	_NOP();
	_NOP();
	clk_set_div(CLKDIV_1);		// set divider
}