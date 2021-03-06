/**
 * @file    tsi.c
 * @brief   functions for controlling the capacitive touch slider
 */

#include "MKL25Z4.h"
#include "tsi.h"

#define SLIDER_TOUCH_THRESHOLD 100 // minimum scan value needed to register as a touch press
#define SLIDER_CENTER_DIVIDER 550 // midpoint scan value between left and right portions of slider

#define SCAN_OFFSET 540  // offset for scan range
#define SCAN_DATA TSI0->DATA & 0xFFFF // the scan result bits held in TSI0_DATA_TSICNT

void init_touch_sensor() {
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK; // enable clock for TSI Port B 16 and 17

	TSI0->GENCS = TSI_GENCS_OUTRGF_MASK |  // out of range flag, set to 1 to clear
				  TSI_GENCS_MODE(0u) |  // capacitive sensing (non-noise mode)
				  TSI_GENCS_REFCHRG(0u) | // set reference oscillator charge
				  TSI_GENCS_DVOLT(0u) | // set oscillator voltage rails
				  TSI_GENCS_EXTCHRG(0u) | // set electrode oscillator charge
				  TSI_GENCS_PS(0u) | // set electrode prescaler value
				  TSI_GENCS_NSCN(31u) | // set number of scans per electrode
				  TSI_GENCS_TSIEN_MASK | // TSI module enable bit
				  TSI_GENCS_STPE_MASK | // enables TSI in low power mode
				  TSI_GENCS_EOSF_MASK ; // end of scan flag, set to 1 to clear
}

int scan_touch_sensor() {
	int scan; // low to high capacitance from left to right
	TSI0->DATA = TSI_DATA_TSICH(10u); // use channel 10 of the TSI
	TSI0->DATA |= TSI_DATA_SWTS_MASK; // setup software trigger for scan
	scan = SCAN_DATA; // save the current value from running a scan
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; // reset end of scan flag
	return scan - SCAN_OFFSET; // return scan value with offset adjustment
}

int get_touch_location() {
	int result = scan_touch_sensor();

	if (result < SLIDER_TOUCH_THRESHOLD)
		return none;
	if (result < SLIDER_CENTER_DIVIDER)
		return left;
	if (result >= SLIDER_CENTER_DIVIDER)
		return right;
}
