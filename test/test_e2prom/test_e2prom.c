//#include <stddef.h>
#include <unity.h>
#include <lgt/io.h>
#include <lgt/clk.h>
#include <lgt/e2prom.h>
#include <util/delay.h>
#include <lgt/ports.h>

#define LED 			POB.B5
#define LED_INIT 		PDB.B5 = 1

void setUp(void) {
	LED = 1;
}

void tearDown(void) {
	LED = 0;
}

// Переменные в E2PROM
#define E2P_INIT_BYTE 0x12
#define E2P_INIT_WORD 0x3456
#define E2P_INIT_DWORD 0x6789abcd
#define E2P_INIT_FLOAT 3.14f
#define E2P_INIT_DOUBLE 2.718281828459045
#define BLOCK_DATA 0x5C
#define BLOCK_SIZE 32

E2PROM uint8_t e2p_byte = E2P_INIT_BYTE;
E2PROM uint16_t e2p_word = E2P_INIT_WORD;
E2PROM uint32_t e2p_dword = E2P_INIT_DWORD;
E2PROM float e2p_float = E2P_INIT_FLOAT;
E2PROM double e2p_double = E2P_INIT_DOUBLE;
E2PROM uint8_t e2p_block[BLOCK_SIZE] = {BLOCK_DATA};

// ============================================
// Тест инициализации данных
// ============================================

void test_read_init_byte(void) {
	uint8_t read_byte = e2prom_read_byte(&e2p_byte);
	TEST_ASSERT_EQUAL_HEX8(E2P_INIT_BYTE, read_byte);
}

void test_read_init_word(void) {
	uint16_t read_word = e2prom_read_word(&e2p_word);
	TEST_ASSERT_EQUAL_HEX16(E2P_INIT_WORD, read_word);
}

void test_read_init_dword(void) {
	uint32_t read_dword = e2prom_read_dword(&e2p_dword);
	TEST_ASSERT_EQUAL_HEX32(E2P_INIT_DWORD, read_dword);
}

void test_read_init_float(void) {
	float read_float = e2prom_read_float(&e2p_float);
	TEST_ASSERT_FLOAT_WITHIN(0.0001f, E2P_INIT_FLOAT, read_float);
}

void test_read_init_double(void) {
	double read_double = e2prom_read_double(&e2p_double);
	TEST_ASSERT_DOUBLE_WITHIN(0.000000000000001, E2P_INIT_DOUBLE, read_double);
}

// ============================================
// Тесты для базовых типов
// ============================================

void test_write_read_byte(void) {
    uint8_t test_values[5] = {0x00, 0x55, 0xAA, 0xFF, 0x55};
    uint8_t read_values[5] = {0};

	for (int i = 0; i < 5; i++) {
        e2prom_write_byte(&e2p_block[i], test_values[i]);
        read_values[i] = e2prom_read_byte(&e2p_block[i]);
    }
    TEST_ASSERT_EQUAL_HEX8_ARRAY(test_values, read_values, 5);
}

void test_write_read_word(void) {
    uint16_t test_values[5] = {0x0000, 0x1234, 0xCAFA, 0xDEAD, 0x6789};
    uint16_t read_values[5] = {0};
	for (int i = 0; i < 5; i++) {
		e2prom_write_word((uint16_t*)&e2p_block[i*2], test_values[i]);
		read_values[i] = e2prom_read_word((const uint16_t*)&e2p_block[i*2]);
	}
	TEST_ASSERT_EQUAL_HEX16_ARRAY(test_values, read_values, 5);
}

void test_write_read_dword(void) {
    uint32_t test_values[5] = {0x00000000, 0x12345678, 0x87654321, 0xABCDEF00, 0x00FEDCBA};
    uint32_t read_values[5] = {0};
	for (int i = 0; i < 5; i++) {
		e2prom_write_dword((uint32_t*)&e2p_block[i*4], test_values[i]);
		read_values[i] = e2prom_read_dword((const uint32_t*)&e2p_block[i*4]);
	}
	TEST_ASSERT_EQUAL_HEX32_ARRAY(test_values, read_values, 5);
}

void test_write_read_float(void) {
	float test_values[5] = {0.0f, 1.23f, -4.56f, 3.14f, -2.71f};
	float read_values[5] = {0};
	for (int i = 0; i < 5; i++) {
		e2prom_write_float((float*)&e2p_block[i*4], test_values[i]);
		read_values[i] = e2prom_read_float((const float*)&e2p_block[i*4]);
	}
	for (int i = 0; i < 5; i++) {
		TEST_ASSERT_FLOAT_WITHIN(0.0001f, test_values[i], read_values[i]);
	}
}

void test_write_read_double(void) {
	double test_values[5] = {0.0, 1.23, -4.56, 3.141592653589793, -2.718281828459045};
	double read_values[5] = {0};
	for (int i = 0; i < 5; i++) {
		e2prom_write_double((double*)&e2p_block[i*8], test_values[i]);
		read_values[i] = e2prom_read_double((const double*)&e2p_block[i*8]);
	}
	for (int i = 0; i < 5; i++) {
		TEST_ASSERT_DOUBLE_WITHIN(0.000000000000001, test_values[i], read_values[i]);
	}
}

// ============================================
// Тесты для e2prom_write_block
// ============================================

// Запись по выровненному адресу (4 байта)
void test_write_aligned_4bytes(void) {
    uint8_t *aligned_addr = (uint8_t *)&e2p_block[0];
    uint8_t test_data[4] = {0x01, 0x02, 0x03, 0x04};
    uint8_t read_buffer[4];

    e2prom_write_block(test_data, aligned_addr, 4);
    e2prom_read_block(read_buffer, aligned_addr, 4);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(test_data, read_buffer, 4);
}

// Запись по невыровненному адресу (смещение 1)
void test_write_unaligned_offset1(void) {
	uint8_t *unaligned_addr = (uint8_t *)&e2p_block[1];
    uint8_t test_data[3] = {0x11, 0x22, 0x33};
    uint8_t read_buffer[3];

    e2prom_write_block(test_data, unaligned_addr, 3);
    e2prom_read_block(read_buffer, unaligned_addr, 3);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(test_data, read_buffer, 3);
}

// Запись блока больше 4 байт с невыровненным началом
void test_write_large_unaligned(void) {
	uint8_t *unaligned_addr = (uint8_t *)&e2p_block[2];
    uint8_t test_data[10] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22, 0x33, 0x44};
    uint8_t read_buffer[10];

    e2prom_write_block(test_data, unaligned_addr, 10);
    e2prom_read_block(read_buffer, unaligned_addr, 10);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(test_data, read_buffer, 10);
}

// Запись 1 байта по невыровненному адресу
void test_write_single_byte_unaligned(void) {
    uint8_t *unaligned_addr = (uint8_t *)&e2p_block[3];  // Смещение 3
    uint8_t test_data[] = {0x77};
    uint8_t read_buffer[1];

    e2prom_write_block(test_data, unaligned_addr, 1);
    e2prom_read_block(read_buffer, unaligned_addr, 1);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(test_data, read_buffer, 1);
}

// Запись с сохранением соседних байтов
void test_write_preserve_neighbors(void) {
    uint8_t *base_addr = 0;

    // Записываем начальные данные
    uint8_t initial_data[6] = {0x55, 0x66, 0x77, 0x88, 0x99, 0xAA};
    e2prom_write_block(initial_data, (void*)base_addr, 6);

    // Записываем только середину
    uint8_t middle_data[2] = {0x12, 0x34};
    e2prom_write_block(middle_data,  (void*)(base_addr + 2), 2);

    // Проверяем результат
    uint8_t expected[6] = {0x55, 0x66, 0x12, 0x34, 0x99, 0xAA};
    uint8_t read_buffer[6];
    e2prom_read_block(read_buffer, (void*)base_addr, 6);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, read_buffer, 6);
}

// ============================================
// Тесты для e2prom_read_block
// ============================================

// Чтение с выровненного адреса
void test_read_aligned(void) {
    uint8_t *addr = (uint8_t*)6;
    uint8_t expected[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    uint8_t read_buffer[8];

    e2prom_write_block(expected, (void*)addr, 8);
    e2prom_read_block(read_buffer, (void*)addr, 8);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, read_buffer, 8);
}

// Чтение с невыровненного адреса
void test_read_unaligned(void) {
    uint8_t *base_addr = (uint8_t*)16;
    uint8_t source_data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint8_t expected[] = {0x03, 0x04, 0x05, 0x06, 0x07};  // Читаем с адреса+2
    uint8_t read_buffer[5];

    e2prom_write_block(source_data, (void*)base_addr, 8);
    e2prom_read_block(read_buffer, (void*)(base_addr + 2), 5);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, read_buffer, 5);
}

// Чтение через границу 32-битных слов
void test_read_across_boundary(void) {
    uint8_t *base_addr = (uint8_t*)24;
    uint8_t source_data[] = {0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18};
    uint8_t expected[] = {0xD4, 0xE5, 0xF6, 0x07};  // Адрес+3, читаем 4 байта
    uint8_t read_buffer[4];

	e2prom_write_block(source_data, (void*)base_addr, 8);
    e2prom_read_block(read_buffer, (void*)(base_addr + 3), 4);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, read_buffer, 4);
}

// Чтение нулевого размера
void test_read_zero_size(void) {
    uint8_t *read_addr = (uint8_t*)32;
    uint8_t read_buffer[1] = {0};
    uint8_t expected[1] = {0};  // Не должно измениться

	e2prom_write_block((uint8_t[]){0xFF}, (void*)read_addr, 1);  // Записываем что-то
    e2prom_read_block(read_buffer, (void*)read_addr, 0);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, read_buffer, 1);
}

// ============================================
// Комплексные тесты
// ============================================

// Цикл записи и чтения различных размеров
void test_write_read_loop(void) {
    uint8_t *base_addr = (uint8_t*)64;

    for (uint16_t size = 1; size <= 20; size++) {
        for (uint8_t offset = 0; offset < 4; offset++) {
            uint8_t *addr = base_addr + offset;
            uint8_t test_data[20];
            uint8_t read_data[20];

            // Заполняем тестовыми данными
            for (uint16_t i = 0; i < size; i++) {
                test_data[i] = (uint8_t)(i & 0xFF);
            }

            // Записываем и читаем

            e2prom_write_block(test_data, (void*)addr, size);
            e2prom_read_block(read_data, (void*)addr, size);

			TEST_ASSERT_EQUAL_HEX8_ARRAY(test_data, read_data, size);
        }
    }
}

// Перекрывающиеся записи
void test_overlapping_writes(void) {
    uint8_t *base_addr = (uint8_t*)128;

    // Первая запись
    uint8_t data1[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    e2prom_write_block(data1, (void*)(base_addr + 1), 6);

    // Вторая запись (перекрывается)
    uint8_t data2[] = {0xFF, 0xEE, 0xDD, 0xCC};
    e2prom_write_block(data2, (void*)(base_addr + 3), 4);

    // Ожидаемый результат
    uint8_t expected_data[] = {0x01, 0x02, 0xFF, 0xEE, 0xDD, 0xCC, 0xFF, 0xFF};
    uint8_t read_buffer[8];

    e2prom_read_block(read_buffer, (void*)(base_addr + 1), 8);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_data, read_buffer, 8);
}

// Запуск всех тестов
int RUN_UNITY_TESTS(void) {
	UNITY_BEGIN();

	RUN_TEST(test_read_init_byte);
	RUN_TEST(test_read_init_word);
	RUN_TEST(test_read_init_dword);
	RUN_TEST(test_read_init_float);
	RUN_TEST(test_read_init_double);
	RUN_TEST(test_write_read_byte);
	RUN_TEST(test_write_read_word);
	RUN_TEST(test_write_read_dword);
	RUN_TEST(test_write_read_float);
	RUN_TEST(test_write_read_double);
	RUN_TEST(test_write_aligned_4bytes);
	RUN_TEST(test_write_unaligned_offset1);
	RUN_TEST(test_write_large_unaligned);
	RUN_TEST(test_write_single_byte_unaligned);
	RUN_TEST(test_write_preserve_neighbors);
	RUN_TEST(test_read_aligned);
	RUN_TEST(test_read_unaligned);
	RUN_TEST(test_read_across_boundary);
	RUN_TEST(test_read_zero_size);
	RUN_TEST(test_write_read_loop);
	RUN_TEST(test_overlapping_writes);

    return UNITY_END();
}

int main(void) {
	LED_INIT;
	e2prom_init();

    int result = RUN_UNITY_TESTS();

	while(1) {
		LED = !LED;
		if (result == 0) {
			_delay_ms(100);
		} else {
			_delay_ms(1000);
		}
	}

    return 0;
}
