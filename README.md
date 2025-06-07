# CS 145 - Embedded Systems Final Project

## Overview

This project uses the ATmega32 MCU, four discrete indicator LEDs, and sound decibel detector to provide immediate visual feedback for monitoring ambient sound levels in real-time. The device assists gamers—often unaware of their own volume due to noise-canceling headphones—in self-regulating their speaking volume during gameplay. It offers a simple, non-intrusive cue system to help maintain household harmony.

## Hardware Setup

- ATmega32 Microcontroller
- Four LEDs: Green, Yellow, Red (for volume level), and RGB (for flashing alert)
- SparkFun Sound Decibel Detector – detects presence and amplitude of sound
- Power Supply – 9V battery-powered, regulated to 5V
- 3D-Printed Circuit Housing

## System Functionality

The sound detector continuously captures real-time audio levels and sends amplitude data to the ATmega32. Based on this audio input:

- The green LED activates for an acceptable volume level
- The yellow LED activates for an elevated volume level
- The red LED signals excessive volume
- If the user remains in the red zone for an extended period of time or frequently re-enters it, the system activates the RGB LED in a white flashing pattern to interrupt gameplay and encourage behavioral correction.

This feedback loop helps the gamer recognize when their voice exceeds acceptable levels and promotes quieter behavior during gaming sessions. 

## Future Implementations

We initially planned to use a WS2812 RGB LED strip to represent sound levels more dynamically, but encountered library and microcontroller timing incompatibilities when attempting to integrate with the ATmega32. As a workaround, we replaced the LED strip with individual LEDs for this version.

For future implementations, we plan to:

- Streamline the circuit with a more compact design by using a LilyGo MCU that supports the Arduino and WS2812 libraries for simplified LED control
- Enclose the circuit within a 3D-printed housing enclosure featuring an ON/OFF switch and USB to USB-C power for better user convenience
- Extend functionality with a reward-based system that tracks user sound history, incentivizes quiet behavior, and potentially integrates with cloud storage for cross-session feedback and customization
