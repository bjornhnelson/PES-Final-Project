#ifndef TSI_H_
#define TSI_H_

#define SCAN_OFFSET 540  // offset for scan range
#define SCAN_DATA TSI0->DATA & 0xFFFF // the scan result bits held in TSI0_DATA_TSICNT

#define SLIDER_TOUCH_THRESHOLD 100 // minimum scan value needed to register as a touch press
#define SLIDER_LEFT_DIVIDER 400 // midpoint scan value between left and center portion of slider
#define SLIDER_RIGHT_DIVIDER 700 // midpoint scan value between center and right portion of slider
#define SLIDER_CENTER_DIVIDER 550

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

#endif
