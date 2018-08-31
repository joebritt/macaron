Macaron is an Arduino shield based on the Petit Biscuit educational Arduino board.

Inspired by Saandial’s Petit Biscuit 
(https://www.tindie.com/products/saandial/petit-biscuit-arduino-programming/). 

Petit Biscuit was designed by Saandial as a tool for introductory embedded programming
using the Arduino IDE. There are 2 versions.

The "saveur fraise" model has:
  16 LEDs (4 red, 4 yellow, 4 green, 4 blue)
  2 momentary pushbuttons
  Atmel ATMega328P with Arduino bootloader
  Reset button
  Crystal
  Header for FTDI-style serial interface

The "saveur vanille" model has mostly the same parts, but these differences:
  Only 15 LEDs (3 red, 4 yellow, 4 green, 4 blue)
  Potentiometer
  Slide switch

I think these were great little boards for teaching basic embedded programming. It's very
easy to see how the I/O pins connect to the LEDs, switches, and potentiometer, and easy to
understand how the software interacts with and controls them. 
Saandial, thank you for designing these!!

I decided to build my own version for my kids (and myself :-), partly because I had some small
linear potentiometers I wanted to use and partly because I wanted to try some interesting
looking surface mount high-efficiency LEDs.

The result is Macaron, a bit of a hybrid of the Vanille and Fraise Petit Biscuits, and built
as an Arduino Shield.

Some notes:

The LEDs are all on dedicated I/O pins, so they can always be directly controlled.
The LED on the linear potentiometer slider is connected to the Arduino TX line. It will flicker
when there is serial traffic. You can also just turn the TX line (1) into an digital output
and control it directly.

The potentiometer is connected to A5. There is also a button between A5 and ground. Normally you
will use analogRead( A5 ) to get the slider position (0-1023). If you push the A5 button, it will
pull A5 to ground, and you'll read 0. You can use the very cool Arduino map() function to map the
0-1023 value onto any other range you want -- or even reverse the range.

The other button is simply connected to digital pin 2, so you can just configure it as an input
with pullup and use digitalRead(2) to get it's state. If it's down, it will read as 0 (or false).

Though designed as an Uno shield, Macaron can also be used with an Arduino Mega, which will provide 
additional I/O pins so more things can be added. 

The board uses very bright high-efficiency LEDs from Avago/Broadcom and a linear potentiometer from Bourns. 

All parts are available from Mouser.  Mouser part numbers below: 

630-ALMD-EG2E-XZ002 Red LED 
630-ALMD-EL2E-XZ002 Amber LED 
630-ALMD-CM2F-12002 Green LED 
630-ALMD-CB2E-UV002 Blue LED 
652-PTL30-10G1-103B2 10K linear (slide) potentiometer with LED 

Headers are normal 0.1" single row.
2 tactile buttons are generic.


