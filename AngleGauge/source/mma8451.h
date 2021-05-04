/*
 * mma8451.h
 *
 *  Created on: Apr 24, 2021
 *      Author: bjornnelson
 */

#ifndef MMA8451_H_
#define MMA8451_H_

#include <stdint.h>

// global variables for saving data
extern float roll, pitch;
extern int16_t acc_X, acc_Y, acc_Z;

/* Purpose: initializes the i2c connection with the accelerometer
 */
int init_mma();


/* Purpose: saves acceleration values for the x, y, and z axes into global variables
 */
void read_xyz();

/* Purpose: calculates the roll and pitch angles based on previously saved acceleration values
 */
void convert_xyz_to_roll_pitch();

#endif /* MMA8451_H_ */
