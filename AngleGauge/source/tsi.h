#ifndef TSI_H_
#define TSI_H_

// return values for get_touch_location() function
enum location {none, left, right};

/* Purpose: initializes the slider for readings
 * Returns: N/A
 */
void init_touch_sensor();

/* Purpose: runs a scan for touch input on the slider
 * Returns: the current value read by the slider
 *
 * 0-100 = no touch detected
 * 100-400 = left touch - red color
 * 400-700 = middle touch - green color
 * 700-1000 = right touch - blue color
 */
int scan_touch_sensor();

/*
 * Purpose: determines where slider was touched based on thresholds
 * Returns: integer enum corresponding to location
 */
int get_touch_location();

#endif
