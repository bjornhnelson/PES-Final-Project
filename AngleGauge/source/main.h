#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

// LOG used for only calling print statements in debug mode (source: lecture slides)
#ifdef DEBUG
#  define LOG PRINTF
#else
#  define LOG(...)
#endif

// RGB brightness values of the LED in each state
#define RED_COLOR 0xFF0000
#define GREEN_COLOR 0x00FF00
#define BLUE_COLOR 0x0000FF

#define BYTE_MASK 0xFF

// each color value represents brightness and has a range of 0-255
typedef struct color_t {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} color_t;

/* Purpose: runs the default KL25Z SDK initialization functions,
 *          which provide UART functionality for debug messages
 */
void init_system();


/* Purpose: checks if two colors have identical RGB values
 * Returns: 1 if colors are the same, 0 if not
 */
int colors_match(color_t c1, color_t c2);

/* Purpose: polls the slider every 100 ms over a specified duration
 * Returns: 1 if slider touched during time period, 0 if not
 *
 * timeout = number of ticks/ms to do slider polling
 */
int poll_slider(int timeout);

/* Purpose: calls the supporting functions to run the overall program
 * Returns: 0
 */
int main();

#endif
