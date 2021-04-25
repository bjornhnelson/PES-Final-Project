#ifndef LED_H_
#define LED_H_

#include "main.h"

// Red LED is connected to PORT B, pin 18
#define RED_LED_PIN 18
#define RED_LED_PIN_CTRL_REG PORTB->PCR[RED_LED_PIN]

// Green LED is connected to PORT B, pin 19
#define GREEN_LED_PIN 19
#define GREEN_LED_PIN_CTRL_REG PORTB->PCR[GREEN_LED_PIN]

// Blue LED is connected to PORT D, pin 1
#define BLUE_LED_PIN 1
#define BLUE_LED_PIN_CTRL_REG PORTD->PCR[BLUE_LED_PIN]

// counter needed for having 1000 Hz PWM frequency
#define PWM_PERIOD 48000

// used to adjust the duty cycle
#define RED_PWM TPM2->CONTROLS[0].CnV
#define GREEN_PWM TPM2->CONTROLS[1].CnV
#define BLUE_PWM TPM0->CONTROLS[1].CnV

/* Purpose: sets up the three LEDs for PWM control
 *
 * period = MOD counter value
 */
void init_led_PWM(uint16_t period);

/* Purpose: updates the LEDs to shine at specified brightness values
 *
 * red_value = brightness of red LED (0-255)
 * green_value = brightness of green LED (0-255)
 * blue_value = brightness of blue LED (0-255)
 */
void set_led_PWM(uint8_t red_value, uint8_t green_value, uint8_t blue_value);

#endif
