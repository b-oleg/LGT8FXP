#ifndef E2PROM_H_
#define E2PROM_H_

#include <stdint.h>

#define E2PROM __attribute__((section(".e2prom")))

void e2prom_init();
uint8_t e2prom_read_byte(void *addr);
void e2prom_write_byte(void *addr, uint8_t value);

void e2prom_write_swm(void *addr, uint32_t *data, uint16_t size);
void e2prom_read_swm(void *addr, uint32_t *data, uint16_t size);

//void e2prom_read_block(void *addr, uint8_t *data, uint16_t size);
void e2prom_write_block(void *addr, uint8_t *data, uint16_t size);

#endif /* E2PROM_H_ */
