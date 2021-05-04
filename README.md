# PES-Final-Project
Code for Final Project for PES, ECEN 5813, Spring 2021  

## Topic: Digital Angle Gauge  
In this project, the KL25Z is acting as a level using the MMA accelerometer on the board.  
Roll and pitch values are outputted using i2c onto the serial port.  
The roll axis corresponds to the longer edge of the board (0-180° range).  
The pitch axis corresponds to the shorter edge of the board (0-90° range).  
The LEDs, UART, and touch slider are also incorporated into the project.  

## Functionality  
- When the program starts, all sensors will be initialized.  
- Type in a time interval (100 ms recommended) for data readings. This number is echoed back after hitting enter.  
- Roll and pitch angles are outputted to a terminal. Angle range of both axes: 0-180 degrees.  
- The red LED is mapped to 0-180° roll angles, with the brightness ranging from 0-255 (off - full).  
- The blue LED is mapped to 0-90° pitch angles, with the brightness ranging from 0-255 (off - full).  
- The red and blue LEDs illuminate simultaneously, so purple color will be seen if both roll and pitch angles are non-zero.    
- At a 45° angle on either the roll or pitch axis, the LED color will be set to green.  
- To reset the roll angle to 0°, tap the left side of the capacitive touch slider at any time.  
- To reset the pitch angle to 0°, tap the right side of the capacitive touch slider at any time.  

## Test Outline (see YouTube link and photos in Testing directory)  

Demo Video: https://youtu.be/yYVCbn9hacQ  

I used a protractor to test a certain subset of angles, while verifying the output value and LED color.  
Example angles tested: 0°, 22°, 30°, 45°, 60°, 90°, 135°, 180°.  

I tested the reset functionality of the slider, and measured some of these same angles again.  

I also tested various refresh time intervals (100 ms, 500 ms, 1000 ms).

## References
KL25Z Reference Manual  
Dean Ch 8 I2C Code: https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/I2C-Demo  
MMA8451Q data sheet  
SysTick API from Howdy Pierce  
