#include <lgt/io.h>
#include <lgt/interrupt.h>

#define	_reset()    do { ECCR |= (1<<ERN); } while(0);
#define	_swm_on()   do { ECCR |= (1<<EWEN); ECCR |= (1<<SWM); } while(0);
#define	_swm_off()  do { ECCR |= (1<<EWEN); ECCR &= ~(1<<SWM); } while(0);

void e2prom_init() {
	ECCR = (1<<EWEN);					// Разрешение записи в регистр
	ECCR = (1<<EEN)|(1<<CP1)|(1<<CP0);	// Вкл, E2PROM=1кБ, FLASH=30кБ
}	

uint8_t e2prom_read_byte(void *addr) {
	EEAR = (uint16_t)addr;
	EECR |= (1 << EERE);
	_NOP(); _NOP();
	return EEDR;
}	

void e2prom_write_byte(void *addr, uint8_t value) {
	uint8_t	sreg = SREG;
	EEAR = (uint16_t)addr;
	EEDR = value;
	cli();
	EECR = (1<<EEMPE);
	EECR = (1<<EEPE);
	SREG = sreg;
}	

void e2prom_write_swm(void *addr, uint32_t *data, uint16_t size) {
	_reset();
	_swm_on();
	EEAR = (uint16_t)addr & 0x003f;		// 1kB
	for(uint16_t i = 0; i < size; i++ ) {
		E2PD0 = (uint8_t)(data[i] >> 0);
		E2PD1 = (uint8_t)(data[i] >> 8);
		E2PD2 = (uint8_t)(data[i] >> 16);
		E2PD3 = (uint8_t)(data[i] >> 24);
		
		if(i==(size-1)) _swm_off(); // last

		uint8_t sreg = SREG;
		cli();
		EECR = (1<<EEPM2)|(1<<EEMPE);
		EECR = (1<<EEPM2)|(1<<EEPE);
		SREG = sreg;
	}
}

void e2prom_read_swm(void *addr, uint32_t *data, uint16_t size) {
	_reset();
	_swm_on();
	EEAR = (uint16_t)addr & 0x003f;		// 1kB;
	for(uint16_t i = 0; i < size; i++) 	{
		EECR |= (1 << EERE);
		_NOP(); _NOP(); 
		
		data[i] = (uint32_t)E2PD0;
		data[i] |= (uint32_t)E2PD1 << 8;
		data[i] |= (uint32_t)E2PD2 << 16;
		data[i] |= (uint32_t)E2PD3 << 24;
	}
	_swm_off();
}

//void e2prom_read_block(void *addr, uint8_t *data, uint16_t size) {
//    uint16_t i;
//    uint32_t u32;
//    uint8_t *current_addr = (uint8_t *)addr;
//
//    uint16_t offset = (uintptr_t)current_addr % 4;					// Обработка невыровненных байт в начале
//    if (offset != 0) {										        // Если смещены
//        e2prom_read_swm(current_addr - offset, &u32, 1);			// Чтение 32-битного слова, содержащего невыровненные байты
//        for (i = 0; i < 4 - offset && i < size; i++) {				// Копируем только нужные байты
//            data[i] = (u32 >> ((offset + i) * 8)) & 0xFF;
//        }
//        current_addr += (4 - offset);								// Обновляем указатели и размер
//        data += (4 - offset);
//        size -= (4 - offset);
//    }
//    for (i = 0; i < size / 4; i++) {								// Чтение выровненных данных по 32 бита (4 байта)
//        e2prom_read_swm(current_addr, &u32, 1);
//        data[i * 4 + 0] = (u32 >>  0) & 0xFF;
//        data[i * 4 + 1] = (u32 >>  8) & 0xFF;
//        data[i * 4 + 2] = (u32 >> 16) & 0xFF;
//        data[i * 4 + 3] = (u32 >> 24) & 0xFF;
//        current_addr += 4;
//    }
//    if (size % 4 != 0) {											// Чтение оставшихся байтов, если size не кратен 4
//        e2prom_read_swm(current_addr, &u32, 1);
//        for (i = 0; i < size % 4; i++) {
//            data[(size / 4) * 4 + i] = (u32 >> (i * 8)) & 0xFF;
//        }
//    }
//}


// void e2prom_read_block(void *addr, uint8_t *data, uint16_t size) {
//     uint16_t i;
//     uint32_t u32;
//     uint8_t *current_addr = (uint8_t *)addr;

//     D("addr=%p, size=%d", addr, size);

//     uint16_t offset = (uintptr_t)current_addr % 4;					// Обработка невыровненных байт в начале
//     D("offset=%d", offset);

//     if (offset != 0) {										        // Если смещены
//     	D("offset != 0");
//         e2prom_read_swm(current_addr - offset, &u32, 1);			// Чтение 32-битного слова, содержащего невыровненные байты
//         D("u32=%08lx", u32);
//         for (i = 0; i < 4 - offset && i < size; i++) {				// Копируем только нужные байты
//             data[i] = (u32 >> ((offset + i) * 8)) & 0xFF;
//         }
//         current_addr += (4 - offset);								// Обновляем указатели и размер
//         data += (4 - offset);
//         size -= (4 - offset);
//     }
//     for (i = 0; i < size / 4; i++) {								// Чтение выровненных данных по 32 бита (4 байта)
//     	D("read");
//         e2prom_read_swm(current_addr, &u32, 1);
//         D("u32=%08lx", u32);
//         data[i * 4 + 0] = (u32 >>  0) & 0xFF;
//         data[i * 4 + 1] = (u32 >>  8) & 0xFF;
//         data[i * 4 + 2] = (u32 >> 16) & 0xFF;
//         data[i * 4 + 3] = (u32 >> 24) & 0xFF;
//         current_addr += 4;
//     }
//     if (size % 4 != 0) {											// Чтение оставшихся байтов, если size не кратен 4
//     	D("last");
//         e2prom_read_swm(current_addr, &u32, 1);
//         D("u32=%08lx", u32);
//         for (i = 0; i < size % 4; i++) {
//             data[(size / 4) * 4 + i] = (u32 >> (i * 8)) & 0xFF;
//         }
//     }
// }

void e2prom_write_block(void *addr, uint8_t *data, uint16_t size) {
    uint16_t i;
    uint32_t temp_data;
    uint8_t *current_addr = (uint8_t *)addr;

    // Обработка невыровненных байтов в начале
    uint16_t offset = (uintptr_t)current_addr % 4;
    if (offset != 0) {
        // Чтение текущего 32-битного слова, чтобы сохранить существующие данные
        e2prom_read_swm(current_addr - offset, &temp_data, 4);

        // Обновляем только нужные байты
        for (i = 0; i < 4 - offset && i < size; i++) {
            temp_data &= ~(0xFF << ((offset + i) * 8)); // Очищаем биты
            temp_data |= (data[i] << ((offset + i) * 8)); // Устанавливаем новые биты
        }

        // Записываем обновленное 32-битное слово
        e2prom_write_swm(current_addr - offset, &temp_data, 4);

        // Обновляем указатели и размер
        current_addr += (4 - offset);
        data += (4 - offset);
        size -= (4 - offset);
    }

    // Запись выровненных данных по 32 бита (4 байта)
    for (i = 0; i < size / 4; i++) {
        temp_data = ((uint32_t)data[i * 4 + 3] << 24) | ((uint32_t)data[i * 4 + 2] << 16) | ((uint32_t)data[i * 4 + 1] << 8) | ((uint32_t)data[i * 4])	;
        e2prom_write_swm(current_addr, &temp_data, 4);
        current_addr += 4;
    }

    // Запись оставшихся байтов, если size не кратен 4
    if (size % 4 != 0) {
        // Чтение текущего 32-битного слова, чтобы сохранить существующие данные
        e2prom_read_swm(current_addr, &temp_data, 4);

        // Обновляем только нужные байты
        for (i = 0; i < size % 4; i++) {
            temp_data &= ~(0xFF << (i * 8)); // Очищаем биты
            temp_data |= (data[(size / 4) * 4 + i] << (i * 8)); // Устанавливаем новые биты
        }

        // Записываем обновленное 32-битное слово
        e2prom_write_swm(current_addr, &temp_data, 4);
    }
}
