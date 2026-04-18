#include <lgt/io.h>
#include <lgt/interrupt.h>
#include <string.h>
#include "e2prom.h"

#define	_reset()    do { ECCR |= (1<<ERN); } while(0);
#define	_swm_on()   do { ECCR |= (1<<EWEN); ECCR |= (1<<SWM); } while(0);
#define	_swm_off()  do { ECCR |= (1<<EWEN); ECCR &= ~(1<<SWM); } while(0);

void e2prom_init() {
	ECCR = (1<<EWEN);					// Разрешение записи в регистр
	ECCR = (1<<EEN)|(1<<CP1)|(1<<CP0);	// Вкл, E2PROM=1кБ, FLASH=30кБ
}	

uint8_t e2prom_read_byte(const uint8_t *p) {
	EEAR = (uint16_t)p; 				// адрес в регистры EEARH/L
	EECR = 0; 							// 8-битный режим
	EECR |= (1 << EERE); 				// запуск операции чтения
	_NOP(); _NOP(); 					// ждем результат
	return EEDR;
}

void e2prom_write_byte(uint8_t *p, uint8_t value) {
	EEAR = (uint16_t)p; 				// адрес в регистры EEARH/L
	EEDR = value; 						// новые данные
	EECR = (1 << EEMPE); 				// 8-битный режим, разрешаем запись
	EECR |= (1 << EEPE); 				// В течение четырёх тактов установите EEPE = 1.
}	

inline uint16_t e2prom_read_word(const uint16_t *p) {
	uint16_t result = 0;
	e2prom_read_block((void*)&result, (const void*)p, sizeof(uint16_t));
	return result;
}

inline void e2prom_write_word(uint16_t *p, uint16_t value) {
	e2prom_write_block(&value, (void*)p, sizeof(uint16_t));
}

inline uint32_t e2prom_read_dword(const uint32_t *p) {
	uint32_t result = 0;
	e2prom_read_block((void*)&result, (const void*)p, sizeof(uint32_t));
	return result;
}

inline float e2prom_read_float(const float *p){
	float result = 0;
	e2prom_read_block((void*)&result, (const void*)p, sizeof(float));
	return result;
}

inline double e2prom_read_double(const double *p) {
	double result = 0;
	e2prom_read_block((void*)&result, (const void*)p, sizeof(double));
	return result;
}

inline void e2prom_write_dword(uint32_t *p, uint32_t value) {
	e2prom_write_block(&value, (void*)p, sizeof(uint32_t));
}

inline void e2prom_write_float(float *p, float value) {
	e2prom_write_block(&value, (void*)p, sizeof(float));
}

inline void e2prom_write_double(double *p, double value) {
	e2prom_write_block(&value, (void*)p, sizeof(double));
}

void e2prom_read_aligned_dword(uint32_t *dst, const uint32_t *src, size_t n) {
	EECR = (1<<EEPM2); 								// 32-битный режим чтения/записи E2PROM
	uint16_t dword_addr = (uint16_t)src;
	for(uint16_t i = 0; i < n; i++) {				// Чтение данных по 32 бита (4 байта) в цикле
		EEAR = dword_addr;							// Установка адреса
		EECR |= (1 << EERE);						// Запуск операции чтения
		_NOP(); _NOP();								// Ждем результат

		dst[i] = E2PD0;								// Сохранение результата в массив
		dst[i] |= (uint32_t)E2PD1 << 8;
		dst[i] |= (uint32_t)E2PD2 << 16;
		dst[i] |= (uint32_t)E2PD3 << 24;

		dword_addr += sizeof(uint32_t);				// Переход к следующему (4 байта)
	}
}

void e2prom_write_aligned_dword(const uint32_t *src, uint32_t *dst, size_t n) {
	_swm_on();
	uint16_t dword_addr = (uint16_t)dst;
	for(uint16_t i = 0; i < n; i++ ) {
		EEAR = dword_addr;
		E2PD0 = (uint8_t)(src[i] & 0xFF); 			// Запись данных в регистры E2PD0-3
		E2PD1 = (uint8_t)((src[i] >> 8) & 0xFF);
		E2PD2 = (uint8_t)((src[i] >> 16) & 0xFF);
		E2PD3 = (uint8_t)((src[i] >> 24) & 0xFF);

		if(i==(n-1)) _swm_off();					// Выключаем SWM на последней итерации, чтобы завершить операцию записи

		EECR = (1 << EEPM2) | (1 << EEMPE);			// 32-битный режим, разрешаем запись
		EECR |= (1 << EEPE);						// Запуск операции записи
		
		dword_addr += sizeof(uint32_t);
	}
}

void e2prom_read_block(void *dst, const void *src, size_t n) {
	uint16_t current_addr = (uintptr_t)src;
	uint8_t offset = current_addr & 0x03;
	uint16_t bytes_processed = 0;
	uint8_t *data = (uint8_t*)dst;
    
    if (n == 0) return;
    
    // unaligned bytes
    if (offset != 0) {
        uintptr_t aligned_addr = current_addr & ~0x03;
        uint32_t temp_dword;
        uint8_t bytes_to_copy = (n < (4 - offset)) ? n : (4 - offset);
        
        e2prom_read_aligned_dword(&temp_dword, (uint32_t*)aligned_addr, 1);
        memcpy(data, ((uint8_t*)&temp_dword) + offset, bytes_to_copy);
        
        bytes_processed = bytes_to_copy;
        current_addr += bytes_processed;
        data += bytes_processed;
    }
    
    // aligned dwords
    if (bytes_processed < n) {
        uint16_t remaining = n - bytes_processed;
        uint16_t dword_count = remaining / 4;
        
        while (dword_count > 0) {
            uint32_t temp_dword;
            e2prom_read_aligned_dword(&temp_dword, (uint32_t*)current_addr, 1);
            memcpy(data, &temp_dword, 4);
            
            bytes_processed += 4;
            current_addr += 4;
            data += 4;
            dword_count--;
        }
    }
    
    // remaining unaligned bytes
    if (bytes_processed < n) {
        uint16_t remaining = n - bytes_processed;
        uint32_t last_dword;
        
        e2prom_read_aligned_dword(&last_dword, (uint32_t*)current_addr, 1);
        memcpy(data, &last_dword, remaining);
    }
}

void e2prom_write_block(const void *src, void *dst, size_t n) {
	uint16_t current_addr = (uintptr_t)dst;
    uintptr_t end_addr = current_addr + n;
    uint8_t *data_ptr = (uint8_t*)src;
    
    if (n == 0) return;
    
    // unaligned bytes
    if (current_addr & 0x03) {
        uintptr_t aligned_start = current_addr & ~0x03;
        uint32_t temp_dword;
        uint8_t bytes_to_boundary = 4 - (current_addr & 0x03);
        uint8_t chunk_size = (n < bytes_to_boundary) ? n : bytes_to_boundary;
        
        e2prom_read_aligned_dword(&temp_dword, (uint32_t*)aligned_start, 1);
        memcpy(((uint8_t*)&temp_dword) + (current_addr & 0x03), data_ptr, chunk_size);
        e2prom_write_aligned_dword(&temp_dword, (uint32_t*)aligned_start, 1);
        
        current_addr += chunk_size;
        data_ptr += chunk_size;
    }
    
    // aligned dwords
    while (current_addr + 4 <= end_addr) {
        uint32_t temp_dword;
        memcpy(&temp_dword, data_ptr, 4);
        e2prom_write_aligned_dword(&temp_dword, (uint32_t*)current_addr, 1);
        
        current_addr += 4;
        data_ptr += 4;
    }
    
    // remaining unaligned bytes
    if (current_addr < end_addr) {
        uint32_t temp_dword;
        uint8_t remaining = end_addr - current_addr;
        
        e2prom_read_aligned_dword(&temp_dword, (uint32_t*)current_addr, 1);
        memcpy(&temp_dword, data_ptr, remaining);
        e2prom_write_aligned_dword(&temp_dword, (uint32_t*)current_addr, 1);
    }
}
