/*
 * bmp280.c
 *
 *  Created on: Dec 17, 2023
 *      Author: tomec
 */


#include "bmp280.h"
#include "main.h"
#include "spi.h"

#define APPEND_RW_1(addr) 0x80 | addr

static bmp280_calib_data_t g_calib_data;
static bmp280_write_mode_t g_write_mode = normal_mode;

// data buffer for writing data to registers
static uint8_t data_buf[2];
void BMP280_Write(uint8_t reg, uint8_t data);

#define CS_PIN_LOW() HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET)

#define CS_PIN_HIGH() HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET)

uint8_t bmp280_read_8(uint8_t addr)
{
	uint8_t buf[2];
	buf[0] = APPEND_RW_1(addr);
	CS_PIN_LOW();
	HAL_SPI_TransmitReceive(&hspi1, buf, buf, 2, 10);
	CS_PIN_HIGH();

 	return buf[1];
}

uint16_t bmp280_read_16(uint8_t addr)
{
	uint8_t buf[3];
	buf[0] = APPEND_RW_1(addr);
	CS_PIN_LOW();
	HAL_SPI_TransmitReceive(&hspi1, buf, buf, 3, 10);
	CS_PIN_HIGH();

 	return ((buf[1] << 8) | buf[2]);
}


// private functions
void read_calib_data()
{
	g_calib_data.dig_T1 = bmp280_read_16(dig_t1);
	g_calib_data.dig_T2 = bmp280_read_16(dig_t2);
	g_calib_data.dig_T3 = bmp280_read_16(dig_t3);

	g_calib_data.dig_P1 = bmp280_read_16(dig_p1);
	g_calib_data.dig_P2 = bmp280_read_16(dig_p2);
	g_calib_data.dig_P3 = bmp280_read_16(dig_p3);
	g_calib_data.dig_P4 = bmp280_read_16(dig_p4);
	g_calib_data.dig_P5 = bmp280_read_16(dig_p5);
	g_calib_data.dig_P6 = bmp280_read_16(dig_p6);
	g_calib_data.dig_P7 = bmp280_read_16(dig_p7);
	g_calib_data.dig_P8 = bmp280_read_16(dig_p8);
	g_calib_data.dig_P9 = bmp280_read_16(dig_p9);
}


void BMP280_Write(uint8_t reg, uint8_t data)
{

}

// API
void BMP280_global_config_write(bmp280_write_mode_t write_mode)
{
	g_write_mode = write_mode;
}

// returns non-0 on error
uint8_t BMP280_init()
{
	uint8_t ret = 0;

	// first, read id:
	uint8_t id = bmp280_read_8(chip_id);


	if(BMP280_ID != id)
	{
		ret = 1;
	}

	// read calibration data for further computations
	read_calib_data();

	return ret;
}
