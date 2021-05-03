/**
 * @file    main.c
 * @brief   Application entry point
 */

#include "main.h"
#include "led.h"
#include "timer.h"
#include "tsi.h"
#include "i2c.h"
#include "mma8451.h"
#include "MKL25Z4.h"

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255

#define MIDPOINT_ANGLE 45
#define MAX_ANGLE 180

#define ANGLE_OFFSET 1.5 // margin of error in either direction for certain angle


void init_system() {
	/* Init board hardware for UART */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
		/* Init FSL debug console. */
		BOARD_InitDebugConsole();
	#endif

	init_systick();
	init_led_PWM();
	init_touch_sensor();
	i2c_init();
	init_mma();
	PRINTF("All systems initialized\r\n");
}

int angle_match(float cur_angle, float desired_angle, float max_offset) {
	return ((cur_angle > desired_angle-max_offset) && (cur_angle < desired_angle+max_offset));
}

int main() {

    init_system(); // initializes UART and peripherals

    // get polling interval from user
    int delay_time = 100;
    PRINTF("Please specify refresh time interval in ms (default=100): ");
    SCANF("%d", &delay_time);
    PRINTF("%d\r\n", delay_time);

	PRINTF("Start Digital Angle Gauge\r\n");

	// slider scan data
	int touch_location;

	// roll and pitch values accounting for offset
	float roll_actual;
	float pitch_actual;

	// accelerometer roll and pitch values when slider was last touched
	float roll_offset = 0;
	float pitch_offset = 0;

    while (1) {
    	// get data from the accelerometer, save in global variables: roll, pitch
    	read_full_xyz();
    	convert_xyz_to_roll_pitch();

    	// run a slider touch scan, update offset variables if touched
    	touch_location = get_touch_location();
    	if (touch_location == left) {
    		PRINTF("** Reset Roll **\r\n");
    		roll_offset = roll;
    	}
    	else if (touch_location == right) {
    		PRINTF("** Reset Pitch **\r\n");
    		pitch_offset = pitch;
    	}

    	// roll and pitch absolute values, accounting for offset
		roll_actual = fabsf(roll - roll_offset);
		pitch_actual = fabsf(pitch - pitch_offset);

		// output data over UART
		PRINTF("Roll: %.2f  Pitch: %.2f\r\n", roll_actual, pitch_actual);

		// calculate brightness for LED
		uint8_t roll_out = roll_actual * MAX_BRIGHTNESS / MAX_ANGLE;
		uint8_t pitch_out = pitch_actual * MAX_BRIGHTNESS / MAX_ANGLE;

		// approximately 45 degree angle on either x or y axis
		if (angle_match(roll_actual, MIDPOINT_ANGLE, ANGLE_OFFSET) || angle_match(pitch_actual, MIDPOINT_ANGLE, ANGLE_OFFSET)) {
			set_led_PWM(roll_out, MAX_BRIGHTNESS, pitch_out); // green led on
		}
		// all other angles
		else {
			set_led_PWM(roll_out, MIN_BRIGHTNESS, pitch_out); // green led off
		}

		// delay for specified number of milliseconds (polling interval)
		tick_delay(delay_time);
    }

    return 0 ;
}
