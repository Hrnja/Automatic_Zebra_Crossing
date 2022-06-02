# Automatic_Zebra_Crossing
Design of microprocessor systems using STM32F407_HAL_API

SPECIFICATION
-------------------------------------------------------------

Equipment:

1. STM32F407 discovery board
2. Servo motor (2x)
3. DC motor (2x)
4. L298N Motor Driver
5. Traffic Light
6. 9V Battery

Functionality:

The system consists of road and zebra. First, when the red light is on, the dc motor starts to rotate and runs the zebra so pedestrians can cross the street. At the same time, the first servo motor pulls up the ramp on the street so cars can’t pass and other servo pull-down ramp so pedestrians can pass. When the traffic light switches from red to green, the first servo pulls down the ramp for car passing and the other servo pulls up the ramp for pedestrians so they can’t pass through the street. DC motor stops running the zebra so the car can cross easily.
