#ifndef _LGT_CLK_H_
#define _LGT_CLK_H_

typedef enum {
	CLK_RCM = 0x1,	// Enable Internal RCM
	CLK_RCK = 0x2,	// Enable Internal RCK
	CLK_OSCM = 0x4,	// Enable External OSCM
	CLK_OSCK = 0x8	// Enable External OSCK
} clk_t;

void clk_set_enable(clk_t clk);
void clk_set_disable(clk_t clk);

typedef enum {
	MCLK_RCM = 0,	// MCLK = Internal RCM
	MCLK_OSCM,		// MCLK = External High Speed OSC
	MCLK_RCK,		// MCLK = Internal RCK
	MCLK_OSCK		// MCLK = External Low Speed OSC
} mclk_t;

void clk_set_mclk(mclk_t mclk);

typedef enum {
	CLKDIV_1 = 0,	// Clock Divider = 1
	CLKDIV_2,		// Clock Divider = 2
	CLKDIV_4,		// Clock Divider = 4
	CLKDIV_8,		// Clock Divider = 8
	CLKDIV_16,		// Clock Divider = 16
	CLKDIV_32,		// Clock Divider = 32
	CLKDIV_64,		// Clock Divider = 64
	CLKDIV_128,		// Clock Divider = 128
	CLKDIV_256,		// Clock Divider = 256
	CLKDIV_512		// Clock Divider = 512
} clk_div_t;

void clk_set_div(clk_div_t clk_div);

void clk_set_oscm();

#endif // _LGT_CLK_H_
