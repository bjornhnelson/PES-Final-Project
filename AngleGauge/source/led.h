#ifndef LED_H_
#define LED_H_

#include <stdint.h>

/* Purpose: sets up the three LEDs for PWM control, uses macro for PWM period
 *
 */
void init_led_PWM();

/* Purpose: updates the LEDs to shine at specified brightness values
 *
 * red_value = brightness of red LED (0-255)
 * green_value = brightness of green LED (0-255)
 * blue_value = brightness of blue LED (0-255)
 */
void set_led_PWM(uint8_t red_value, uint8_t green_value, uint8_t blue_value);

#endif
