# cs-145-project
CS 145 - Embedded Systems Project

## Overview

This project uses the ATmega32 microcontroller, an 8-bit LED strip and sound decibel detector. The device provides immediate visual feedback to monitor ambient sound levels in real-time. The device assists gamers--often unaware of their own volume due to noise-canceling headphones--in self-regulating their speaking volume during gameplay. The device offers a simple, non-intrusive cue system to help maintain household harmony.

## Hardware Setup

- ATmega32 Microcontroller
- WS2812 RGB LED Stick – used to visually represent volume level (green, yellow, red, white)
- SparkFun Sound Decibel Detector – detects presence and amplitude of sound
- Power Supply – can be powered through USB via the Arduino Uno Programmer or battery-powered through a (regulated 5V) 9V battery.
- 3D-Printed Circuit Housing

## System Functionality

The sound detector continuously captures real-time audio levels and sends amplitude data to the ATmega32. Based on this audio input:

- The LED strip lights up green for an acceptable volume, yellow for elevated volume, and red for excessive volume.
- If the user remains in the red zone for an extended period of time or frequently re-enters it, the system activates a white flashing pattern to interrupt gameplay and encourage behavioral correction.

This feedback loop helps the gamer recognize when their voice exceeds acceptable levels and promotes quieter behavior during gaming sessions. 

## Future Implementations

Future implementations will develop a reward-based system that tracks a user’s sound history over multiple sessions. Users who consistently stay in the green or yellow range may be temporarily spared from flashing when briefly entering red. This feature could potentially integrate with cloud storage and would encourage sustained good behavior through positive reinforcement.