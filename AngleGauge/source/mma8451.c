/*
 * mma8451.c
 *
 *  Created on: Apr 24, 2021
 *      Author: bjornnelson
 *
 *      Code inspired by Dean: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/I2C-Demo/src/mma8451.c
 */


#include "MKL25Z4.h"
#include "mma8451.h"
#include "i2c.h"
#include "timer.h"
#include <math.h>

#define MMA_ADDR 0x3A

#define REG_XHI 0x01
#define REG_YHI 0x03
#define REG_ZHI	0x05

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A

#define WHOAMI 0x1A

#define COUNTS_PER_G (4096.0)
#define M_PI (3.14159265)

// global variable initializations
int16_t acc_X=0, acc_Y=0, acc_Z=0;
float roll=0.0, pitch=0.0;

//initializes mma8451 sensor
//i2c has to already be enabled
int init_mma() {
	//set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

void read_xyz() {
	// sign extend byte to 16 bits - need to cast to signed since function
	// returns uint8_t which is unsigned
	acc_X = (int8_t) i2c_read_byte(MMA_ADDR, REG_XHI);
	tick_delay(1); // 1 ms delay between reads
	acc_Y = (int8_t) i2c_read_byte(MMA_ADDR, REG_YHI);
	tick_delay(1); // 1 ms delay between reads
	acc_Z = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZHI);
}

void convert_xyz_to_roll_pitch() {
	float ax = acc_X/COUNTS_PER_G;
	float ay = acc_Y/COUNTS_PER_G;
	float az = acc_Z/COUNTS_PER_G;
	roll = atan2(ay, az)*180/M_PI;
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/M_PI;
}
