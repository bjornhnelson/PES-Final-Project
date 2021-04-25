#ifndef TIMER_H_
#define TIMER_H_

#include "main.h"

typedef uint32_t ticktime_t; // time since boot, in msec (1 kHz)
							 // 32 bits holds ~50 days of time

#define SYSTEM_FREQ 48000000
#define DESIRED_FREQ 1000

/*
 * Purpose: Initializes the ticktime counters. Immediately after this function
 * returns, a call to now() will return 0, and a call to reset_timer() will return 0.
 */
void init_systick(); // initialize the timing system

/*
 * Purpose: access global timer variable
 * Returns: time since init_systick() was called, in msec
 */
ticktime_t now(); // returns time since startup, in sixteenths of a second

/*
 * Purpose: Resets the timer. Immediately after this function returns, a call
 * to get_timer() will return 0.
 */
void reset_timer(); // resets timer to 0; doesn't affect now() values

/*
 * Purpose: access global timer variable
 * Returns: time since the latter of init_ticktime() or reset_timer()
 * was called, in msec
 */
ticktime_t get_timer(); // returns ticks since the last call to reset_timer()

/*
 * Purpose: delay a specified number of ticks (1 tick = 1 ms)
 *
 * num_ticks = number of SysTick timer ticks that pass before function returns
 */
void tick_delay(ticktime_t num_ticks);

#endif
