/*
 * bmp280.h
 *
 *  Created on: 17 gru 2023
 *      Author: tomec
 */

#ifndef INC_BMP280_H_
#define INC_BMP280_H_

#include <stdint.h>

typedef struct {
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
} bmp280_calib_data_t;

typedef enum {
	force_mode,
	normal_mode
} bmp280_write_mode_t;

// registers

typedef enum {
	dig_p9 = 0x9E,
	dig_p8 = 0x9C,
	dig_p7 = 0x9A,
	dig_p6 = 0x98,
	dig_p5 = 0x96,
	dig_p4 = 0x94,
	dig_p3 = 0x92,
	dig_p2 = 0x90,
	dig_p1 = 0x8E,
	dig_t3 = 0x8C,
	dig_t2 = 0x8A,
	dig_t1 = 0x88,
	chip_id = 0XD0,
	reset = 0xE0,
	status = 0xF3,
	ctrl_meas = 0xF4,
	config = 0xF5,
	press_msb = 0xF7,
	press_lsb = 0xF8,
	press_xlsb = 0xF9,
	temp_msb = 0xFA,
	temp_lsb = 0xFB,
	temp_xlsb = 0xFC
} bmp280_reg_addresses_t;


// DEFINES
#define BMP280_ID 0x58


// function declarations
void BMP280_global_config_write(bmp280_write_mode_t write_mode);
uint8_t BMP280_init();

#endif /* INC_BMP280_H_ */
