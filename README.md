Lidar Mapper module.

This module was designed to be the eyes of a drone that is being developed by a project group for the Open Innovation course at Fontys University Eindhoven.
In this repo you will find two folders. MappingSystem and mapper_esp32.
both of these hold a version for the mapping program that uses an MG90S mini servo and a Grove TF mini Lidar.
to make a map of 180 degrees.

MappingSystems holds a version that is made in C++ and designed to be used on a raspberry 3B+.
NOTE: the program also works on a raspberry 3B but in order for it to work, in /src/Uart.cpp on line 83 "/dev/ttyS0"
needs to be changed to "/dev/ttyAMA0".

The map created is an array of (default set to 5) uint16_t's, each at an equal distance of eachother divided over 180 degrees.

mapper_esp32 holds a version made in C designed for an esp32 microcontroller using esp_idf.
it's current version does not store a map but simply prints out the distance at each angle.

NOTE: the esp32 only has a 3.3V supply so the servo and sensor will need an exteral 5V supply in order to function correctly.