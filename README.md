# CandySortMachine
The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology.
Supervisor: Marek Kraft/Michał Fularz/Tomasz Mańkowski/Adam Bondyra

## Overview
This project is used in our candy sorting machine.
## Tools
    Hardware:
        - AVR Microcontroller Atmega8A
        - TCS3200D Color Sensor
        - Redox L360 Servo
        - Redox S90 Servo
        - Usart-USB FT232 (Debug)

    Software:
        - Atmel Studio 7.0
        - Tool to save program on microchip flash memory by USBasp like e.g.
        - MkAvrCalculator
## How to compile
In order to run this program on microprocessor, it is needed to build it to hex file, and save into flash memory using applications like MkAvrCalculator, SinaProg.
## How to run
Connect components as follows:
	
|TCS3200D Color Sensor|Atmega8A|
| ----- | ----- |
|OUT|PD2|
|S0|PC0|
|S1|PC1|
|S2|PC2|
|S3|PC3|

|Usart-USB FT232|Atmega8A|
| ----- | ----- |
|RXD|PD1|

|REDOX L360|Atmega8A|
| ----- | ----- |
|SIGNAL|PB1|

|REDOX S90|Atmega8A|
| ----- | ----- |
|SIGNAL|PB3|

## Known issues
Unefficient color detection.
## Future improvements
Make the values returned by the sensor more accurate.
## License
Candy Sort Machine is licensed under MIT license.
## Credits
| [Dawid Białek](https://github.com/DawidBialek)| [Kacper Cieślewicz](https://github.com/KacperCieslewicz)|
| ------ | ------ |
