/**
 * @file    timer.c
 * @brief   API for the SysTick timer
 */

#include "timer.h"
#include "core_cm0plus.h"

// global variables accessed in interrupt service routine
static volatile ticktime_t g_now = 0;
static ticktime_t g_timer = 0;

void init_systick() {
	// set control & status register to use 48 MHz clock. Then interrupt 1000 times per second.
	SysTick->LOAD = SYSTEM_FREQ/DESIRED_FREQ - 1; // counter value for 1000 Hz

	// configure interrupts
	NVIC_SetPriority(SysTick_IRQn, 3);
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	NVIC_EnableIRQ(SysTick_IRQn);

	SysTick->VAL = 0; // clear timer
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk; // enable interrupts, enable timer, use 48 MHz system clock

	g_now = 0;
	g_timer = 0;

	LOG("SysTick initialized\r\n");
}

void SysTick_Handler() {
	g_now++;
}

ticktime_t now() {
	return g_now;
}

void reset_timer() {
	g_timer = g_now;
}

ticktime_t get_timer() {
	return g_now - g_timer;
}

void tick_delay(ticktime_t num_ticks) {
	ticktime_t cur = g_now;
	while ((g_now - cur) < num_ticks);
}

