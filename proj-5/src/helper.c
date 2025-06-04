#include "helper.h"
#include "avr.h"
#include <stdio.h>
#include <stdlib.h>

///////////////////
// HELPER FUNCTIONS
///////////////////

#define RED_LED_ PD2
#define BLUE_LED PD5
#define GREEN_LED PD4

uint16_t read;

// Initialize ADC
void adc_init() {
    ADMUX = (1 << REFS0) | (1 << MUX0);                 // AVCC as ref, ADC1
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, prescaler 64
}

// Read ADC
int adc_read() {
    ADCSRA |= (1 << ADSC);                              // Start conversion
    while (ADCSRA & (1 << ADSC));                       // Wait for it to finish
    return ADCW;                                        // Return 10-bit result
}

int get_audio_level() {
    int level = adc_read();
    // Optionally add smoothing or scaling
    return level;
}

//Testing with individual LEDs
void green_led() {
    turn_off_leds(); // Ensure all LEDs are off before turning on the green LED
    PORTD |= (1 << GREEN_LED); // Turn on the green LED
}

void yellow_led() {
    turn_off_leds(); // Ensure all LEDs are off before turning on the yellow LED
    PORTD |= (1 << BLUE_LED);
}

void red_led() {
    turn_off_leds(); // Ensure all LEDs are off before turning on the red LED
    PORTD |= (1 << RED_LED_); // Turn on the red LED
}

void flash_led() {
    turn_off_leds(); // Ensure all LEDs are off before flashing
    PORTD |= (1 << RED_LED_) | (1 << BLUE_LED) | (1 << GREEN_LED); // Turn on all LEDs
    avr_wait(500); // Wait for 500 ms
}

void turn_off_leds() {
    PORTD &= ~((1 << RED_LED_) | (1 << BLUE_LED) | (1 << GREEN_LED)); // Turn off all LEDs
}