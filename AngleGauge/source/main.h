#ifndef MAIN_H_
#define MAIN_H_


/* Purpose: runs the default KL25Z SDK initialization functions,
 *          which provide UART functionality for debug messages
 */
void init_system();

/* Purpose: determines if two angles are within a certain range of each other
 * Returns: 1 if true, 0 if false
 *
 * cur_angle = angle 1
 * desired_angle = angle 2
 * max_offset = max difference between angle 1 and angle 2 in +/- direction
 */
int angle_match(float cur_angle, float desired_angle, float max_offset);

/* Purpose: calls the supporting functions to run the overall program
 * Returns: 0
 */
int main();

#endif
