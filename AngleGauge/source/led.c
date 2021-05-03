/**
 * @file    led.c
 * @brief   functions for controlling the LED
 */

#include "MKL25Z4.h"
#include "led.h"

// counter needed for having 1000 Hz PWM frequency
#define PWM_PERIOD 48000

// Red LED is connected to PORT B, pin 18
#define RED_LED_PIN 18
#define RED_LED_PIN_CTRL_REG PORTB->PCR[RED_LED_PIN]

// Green LED is connected to PORT B, pin 19
#define GREEN_LED_PIN 19
#define GREEN_LED_PIN_CTRL_REG PORTB->PCR[GREEN_LED_PIN]

// Blue LED is connected to PORT D, pin 1
#define BLUE_LED_PIN 1
#define BLUE_LED_PIN_CTRL_REG PORTD->PCR[BLUE_LED_PIN]

// used to adjust the duty cycle
#define RED_PWM TPM2->CONTROLS[0].CnV
#define GREEN_PWM TPM2->CONTROLS[1].CnV
#define BLUE_PWM TPM0->CONTROLS[1].CnV


void init_led_PWM() {
	// send clock to GPIO ports B (red & green) and D (blue)
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	// enable TPM timers
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK | SIM_SCGC6_TPM0_MASK;

	// enable FTM timers for each color
	RED_LED_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;
	RED_LED_PIN_CTRL_REG |= PORT_PCR_MUX(3); // FTM2_CH0 = Mux Alt 3

	GREEN_LED_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;
	GREEN_LED_PIN_CTRL_REG |= PORT_PCR_MUX(3); // FTM2_CH1 = Mux Alt 3

	BLUE_LED_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;
	BLUE_LED_PIN_CTRL_REG |= PORT_PCR_MUX(4); // FTM0_CH1 = Mux Alt 4

	// Configure TPM
	// Set clock source for tpm: 48 MHz
	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	// load the counter and mod
	// PWM frequency = 1000 Hz
	// System Clock / (Prescaler * Desired PWM Frequency) - 1 = MOD Counter
	// 48000000 / (1 * 1000) - 1 = 47999
	TPM2->MOD = PWM_PERIOD-1;
	TPM0->MOD = PWM_PERIOD-1;

	// Prescalar set to 1
	TPM2->SC = TPM_SC_PS(0);
	TPM0->SC = TPM_SC_PS(0);

	// Continue operation in debug mode
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	TPM0->CONF |= TPM_CONF_DBGMODE(3);

	// Set all channels to edge-aligned low-true PWM
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; // red
	TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; // green
	TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; // blue

	// Set initial duty cycle to 0
	RED_PWM = 0;
	GREEN_PWM = 0;
	BLUE_PWM = 0;

	// Start TPM
	TPM2->SC |= TPM_SC_CMOD(1);
	TPM0->SC |= TPM_SC_CMOD(1);

}

void set_led_PWM(uint8_t red_value, uint8_t green_value, uint8_t blue_value) {
	// division done last, to maintain accuracy of int values
	RED_PWM = (red_value * PWM_PERIOD) / 0xFF;
	GREEN_PWM = (green_value * PWM_PERIOD) / 0xFF;
	BLUE_PWM = (blue_value * PWM_PERIOD) / 0xFF;
}
