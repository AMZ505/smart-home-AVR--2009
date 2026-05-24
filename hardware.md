# Hardware Description

## Main Components

* ATmega32 Microcontroller
* DS1307 RTC
* MQ-5 Gas Leakage Sensor
* Temperature Sensor
* Photocell Sensors
* Laser Protection Sensor
* 4x18 LCD Display
* Relay Driver Circuit
* USART Communication Interface

## Transmitter Board

The transmitter board acts as the main controller responsible for:

* sensor acquisition
* scheduling
* user interface
* security monitoring
* communication

## Receiver Board

The receiver board controls:

* lighting relays
* cooling systems
* alarm outputs
* auxiliary loads

## Sensors

### MQ-5 Gas Leakage Sensor

Used for combustible gas and smoke detection.

### Photocell Sensors

Used for indoor and outdoor light monitoring.

### Laser Protection Sensor

Used for intrusion detection.

## Power Supply

* Input Voltage: 12V DC
* Regulated Voltage: 5V DC

## Communication

USART serial communication at 9600 baud was used between the two boards.
