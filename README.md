# SmartHome
## Project Overview
### Title: Smart Home Automation System
### Objective: Design and implement a smart home system that controls lights, TV, air conditioning, and temperature sensors using PIC18F4620 microcontrollers.
### Components:
Reception area: Lights, TV, air conditioner, and LM35 temperature sensor
Two rooms: Lights, air conditioner, and LM35 temperature sensor
User interface: Character LCD display and 3x4 keypad
### Drivers Used:
MCAL (Microcontroller Abstraction Layer):
GPIO (General Purpose Input/Output): For controlling lights and other digital devices.
Interrupt handling: To handle external events (e.g., keypad input).
UART (Universal Asynchronous Receiver-Transmitter): For communication between microcontrollers.
EEPROM (Electrically Erasable Programmable Read-Only Memory): For storing configuration data.
ADC (Analog-to-Digital Converter): To read temperature values from the LM35 sensor.
### HAL (Hardware Abstraction Layer):
Character LCD: Display system status, room temperatures, and messages.
Keypad: Accept user input for controlling devices.
LED: Indicate system status (e.g., power on, device active).
LM35: Measure room temperatures.
### Simulation Environment: Proteus
### IDE Used: MPLAB X IDE
### Implementation Details
