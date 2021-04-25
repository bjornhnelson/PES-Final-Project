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


void init_system() {
	/* Init board hardware for UART */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
		/* Init FSL debug console. */
		BOARD_InitDebugConsole();
	#endif
}

int colors_match(color_t c1, color_t c2) {
	return (c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue);
}

int poll_slider(int timeout) {
	ticktime_t cur_time;
	int slider_value;
	while ((cur_time = get_timer()) < timeout) {
		if (cur_time % 100 == 0) { // poll every 100 ms
			slider_value = scan_touch_sensor();

			if (slider_value > SLIDER_TOUCH_THRESHOLD) { // touch detected
				LOG("Slider pressed at t_msec = %d\r\n", now());
				return 1; // go to next state immediately
			}

		}
	}
	return 0;
}

int main() {

    init_system(); // initializes UART
    PRINTF("Start Digital Angle Gauge\r\n");
    init_systick();
    init_led_PWM(PWM_PERIOD);
    init_touch_sensor();

    i2c_init();
    init_mma();

    while (1) {
    	read_full_xyz();
    	convert_xyz_to_roll_pitch();
    }



//    while(1) {
//    	set_led_PWM(255, 0, 0);
//    	tick_delay(2000);
//    	set_led_PWM(0, 255, 0);
//    	tick_delay(2000);
//    	set_led_PWM(0, 0, 255);
//    	tick_delay(2000);
//    	set_led_PWM(255, 255, 255);
//    	tick_delay(2000);
//    	set_led_PWM(0, 0, 0);
//    	tick_delay(2000);
//    }

    return 0 ;
}
