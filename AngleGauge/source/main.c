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

#include <stdlib.h>


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
	init_led_PWM(PWM_PERIOD);
	init_touch_sensor();
	i2c_init();
	init_mma();
}

float calibrate_value(float a, float b) {
	if (a < b)
		return b-a;
	else
		return a-b;
}

int main() {

    init_system(); // initializes UART

    int delay_time = 1000;
    PRINTF("Please specify refresh time interval in ms (default=1000): ");
    SCANF("%d", &delay_time);
    PRINTF("%d\r\n", delay_time);

	PRINTF("Start Digital Angle Gauge\r\n");

	int slider_value;
	float roll_offset = 0;
	float pitch_offset = 0;

    while (1) {
    	read_full_xyz();
    	convert_xyz_to_roll_pitch();

    	slider_value = scan_touch_sensor();
		if (slider_value > SLIDER_TOUCH_THRESHOLD) { // touch detected
			if (slider_value < SLIDER_CENTER_DIVIDER) {
				PRINTF("** Reset Roll **\r\n");
				roll_offset = roll;
			}
			else {
				PRINTF("** Reset Pitch **\r\n");
				pitch_offset = pitch;
			}
			init_mma();
		}

		float roll_actual = calibrate_value(roll, roll_offset);
		float pitch_actual = calibrate_value(pitch, pitch_offset);
		PRINTF("Roll: %.2f  Pitch: %.2f\r\n", roll_actual, pitch_actual);

		uint8_t roll_out = roll_actual * 255 / 180;
		uint8_t pitch_out = pitch_actual * 255 / 180;

    	set_led_PWM(roll_out, 0, pitch_out);
    	tick_delay(delay_time);
    }

    return 0 ;
}
