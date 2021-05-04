/*
 * i2c.h
 *
 *  Created on: Apr 24, 2021
 *      Author: bjornnelson
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void i2c_init();

void i2c_busy();

void i2c_wait();

void i2c_start();

uint8_t i2c_read_byte(uint8_t dev, uint8_t address);

void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif /* I2C_H_ */
