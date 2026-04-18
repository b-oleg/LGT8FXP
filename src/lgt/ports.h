#ifndef _BITS_H_
#define _BITS_H_

#include <lgt/io.h>

typedef struct {
	uint8_t B0 :1;
	uint8_t B1 :1;
	uint8_t B2 :1;
	uint8_t B3 :1;
	uint8_t B4 :1;
	uint8_t B5 :1;
	uint8_t B6 :1;
	uint8_t B7 :1;
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

#ifdef PORTE
#define POE (*((volatile bits_t*)&PORTE))
#define PIE (*((volatile bits_t*)&PINE))
#define PDE (*((volatile bits_t*)&DDRE))
#endif

#ifdef PORTF
#define POF (*((volatile bits_t*)&PORTF))
#define PIF (*((volatile bits_t*)&PINF))
#define PDF (*((volatile bits_t*)&DDRF))
#endif

#endif // _BITS_H_
