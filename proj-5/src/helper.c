#include "helper.h"
#include "avr.h"
#include <stdio.h>
#include <stdlib.h>

///////////////////
// HELPER FUNCTIONS
///////////////////

int RED_LED = 2;
int GREEN_LED = 4;
int BLUE_LED = 5;

void led_setup() {
    // Set RED, GREEN, BLUE LED pins to output
    DDRD |= (1 << PIN2) | (1 << PIN4) | (1 << PIN5);
}

// Initialize ADC
void adc_init() {
    ADMUX = (1 << REFS0);                 // AVCC as ref, ADC0
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, prescaler 64
}

// Read ADC
int adc_read() {
    ADCSRA |= (1 << ADSC);                              // Start conversion
    while (ADCSRA & (1 << ADSC));                       // Wait for it to finish
    return ADCW;                                        // Return 10-bit result
}

int get_audio_level() {
    int sum_levels = 0;
    for(int i = 0; i < 10; ++i) { // Take 10 readings for averaging
        avr_wait(10); // Wait for 10 ms between readings
        sum_levels += get_one_reading(); // Get one reading from ADC
    }
    int level = sum_levels / 5; // Average the readings
    // Optionally add smoothing or scaling
    return level;
}

int get_one_reading() {
    int reading = adc_read(); // Read the ADC value
    return reading;           // Return the ADC value
}

//Testing with individual LEDs
void green_led() {
    turn_off_leds(); // Ensure all LEDs are off before turning on the green LED
    SET_BIT(PORTD, GREEN_LED); // Turn on the green LED
}

void blue_led() {
    turn_off_leds(); // Ensure all LEDs are off before turning on the yellow LED
    SET_BIT(PORTD, BLUE_LED); // Turn on the blue LED for yellow
}

void red_led() {
    turn_off_leds(); // Ensure all LEDs are off before turning on the red LED
    SET_BIT(PORTD, RED_LED); // Turn on the red LED
}

void flash_led() {
    turn_off_leds(); // Ensure all LEDs are off before flashing
    SET_BIT(PORTD, RED_LED);   // Turn on the red LED
    SET_BIT(PORTD, BLUE_LED);  // Turn on the blue LED
    SET_BIT(PORTD, GREEN_LED); // Turn on the green LED
    avr_wait(500); // Wait for 500 ms
}

void turn_off_leds() {
    CLR_BIT(PORTD, RED_LED);   // Turn off the red LED
    CLR_BIT(PORTD, BLUE_LED);  // Turn off the blue LED
    CLR_BIT(PORTD, GREEN_LED); // Turn off the green LED
}