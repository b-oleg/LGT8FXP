#ifndef _E2PROM_H_
#define _E2PROM_H_

#include <stdint.h>
#include <stddef.h>

#define E2PROM			__attribute__((section(".e2prom")))
#define _ATTR_PURE_		__attribute__((__pure__))

void e2prom_init();

uint8_t e2prom_read_byte(const uint8_t *p) _ATTR_PURE_;
uint16_t e2prom_read_word(const uint16_t *p) _ATTR_PURE_;
uint32_t e2prom_read_dword(const uint32_t *p) _ATTR_PURE_;
float e2prom_read_float(const float *p) _ATTR_PURE_;
double e2prom_read_double(const double *p) _ATTR_PURE_;
void e2prom_read_block(void *dst, const void *src, size_t n);
void e2prom_read_aligned_dword(uint32_t *dst, const uint32_t *src, size_t n);

void e2prom_write_byte(uint8_t *p, uint8_t value);
void e2prom_write_word(uint16_t *p, uint16_t value);
void e2prom_write_dword(uint32_t *p, uint32_t value);
void e2prom_write_float(float *p, float value);
void e2prom_write_double(double *p, double value);
void e2prom_write_block(const void *src, void *dst, size_t n);
void e2prom_write_aligned_dword(const uint32_t *src, uint32_t *dst, size_t n);

#endif /* _E2PROM_H_ */
