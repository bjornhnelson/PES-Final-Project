/*
 * i2c.h
 *
 *  Created on: Apr 24, 2021
 *      Author: bjornnelson
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

/* Purpose: initializes the i2c as master, so a connection can later be made with accelerometer
 */
void i2c_init();

/* Purpose: temporarily stalls if there are too many locks detected
 */
void i2c_busy();

/* Purpose: executes a delay after each read/written byte
 */
void i2c_wait();

/* Purpose: sends the start sequence frame of bytes
 */
void i2c_start();

/* Purpose: reads a single byte
 * Returns: byte that was read
 *
 * dev = dev address
 * address = location to read from
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);

/* Purpose: writes a single byte
 *
 * dev = dev address
 * address = location to write to
 * data = byte to be written
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);

#endif /* I2C_H_ */
