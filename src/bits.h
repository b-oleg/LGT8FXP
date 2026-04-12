#ifndef _BITS_H_
#define _BITS_H_

#include <lgt/io.h>

typedef struct {
	uint8_t Bit0 :1;
	uint8_t Bit1 :1;
	uint8_t Bit2 :1;
	uint8_t Bit3 :1;
	uint8_t Bit4 :1;
	uint8_t Bit5 :1;
	uint8_t Bit6 :1;
	uint8_t Bit7 :1;
} bits_t;

#ifdef PORTA
#define POA (*((volatile bits_t*)&PORTA))
#define PIA (*((volatile bits_t*)&PINA))
#define PDA (*((volatile bits_t*)&DDRA))
#endif

#ifdef PORTB
#define POB (*((volatile bits_t*)&PORTB))
#define PIB (*((volatile bits_t*)&PINB))
#define PDB (*((volatile bits_t*)&DDRB))
#endif

#ifdef PORTC
#define POC (*((volatile bits_t*)&PORTC))
#define PIC (*((volatile bits_t*)&PINC))
#define PDC (*((volatile bits_t*)&DDRC))
#endif

#ifdef PORTD
#define POD (*((volatile bits_t*)&PORTD))
#define PID (*((volatile bits_t*)&PIND))
#define PDD (*((volatile bits_t*)&DDRD))
#endif

#endif // _BITS_H_
