/*
 * i2c.h
 *
 *  Created on: Apr 24, 2021
 *      Author: bjornnelson
 */

#ifndef I2C_H_
#define I2C_H_

void i2c_init(void);

void i2c_start(void);
void i2c_read_setup(uint8_t dev, uint8_t address);
uint8_t i2c_repeated_read(uint8_t);

uint8_t i2c_read_byte(uint8_t dev, uint8_t address);
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif /* I2C_H_ */
