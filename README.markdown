Christian Reyes

Carnegie Mellon University
05-833 Gadgets, Sensors, and Activity Recognition in Human-Computer Interaction

2/23/2012

Project 1: LED 8x8 Matrix Game

------------ Snake Nunchuck -----------------

Classic snake game implemented on Arduino.

Uses the Wii Nunchuck joystick as the interaction device. User moves
around the grid and eats the food which is running all over the board.

The game ends when the snake eats itself.

------------ Wii Nunchuck ------------------

I used the "WiiChuck" Wii Nunchuck Adapter: 

http://todbot.com/blog/2008/02/18/wiichuck-wii-nunchuck-adapter-available/

The most recent WiiChuck library can be found at:

https://github.com/todbot/wiichuck_adapter

The WiiChuck communicates over I2C which uses the SDA and SLC pins (A4 and A5) to
communicate with the Wii Nunchuck.

The Wii Nunchuck has a triple-axis accelerometer, two buttons, and a joystick. The
joystick is implemented using two potentiometers and thus gives you the ability to
read input for any angle.

Simply copy "nunchuck_funcs.h" into your project folder and #include "nunchuck_funcs.h"
it in to get access to the functions.
