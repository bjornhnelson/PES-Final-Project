/*
 * mma8451.h
 *
 *  Created on: Apr 24, 2021
 *      Author: bjornnelson
 */

#ifndef MMA8451_H_
#define MMA8451_H_

#include <stdint.h>

/*
 *
 */
int init_mma();


/*
 *
 */
void read_xyz();

/*
 *
 */
void convert_xyz_to_roll_pitch();

// global variables for saving data
extern float roll, pitch;
extern int16_t acc_X, acc_Y, acc_Z;

#endif /* MMA8451_H_ */
