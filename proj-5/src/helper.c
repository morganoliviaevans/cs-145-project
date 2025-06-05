#include "helper.h"
#include "avr.h"
#include <stdio.h>
#include <stdlib.h>
#include "ws2812_config.h" // LED strip config
#include "light_ws2812.h"  // LED strip library

///////////////////
// HELPER FUNCTIONS
///////////////////

////////////////////////////////////////// LED STRIP //////////////////////////////////////////

struct cRGB leds[8]; // Pre-built struct from light_ws2812 library with internal uint8_t r, g, b

void led_init() {
    DDRD |= (1 << PD5);  // Make PD5 output
    turn_off_leds();
    avr_wait(2000);
}

void green_led() {
    // Ensure all LEDs are off before turning on green LEDs
    turn_off_leds();
    // Set LEDs 0-7 to green
    for (int i = 0; i < 8; ++i) {
        leds[i].r = 255;
        leds[i].g = 0;
        leds[i].b = 0;
    }
    ws2812_setleds(leds, 8); // Send to LED strip
}

void yellow_led() {
    // Ensure all LEDs are off before turning on yellow LEDs
    turn_off_leds();
    // Set LEDs 0-3 to green
    for (int i = 0; i < 4; ++i) {
        leds[i].r = 0;
        leds[i].g = 255;
        leds[i].b = 0;
    }
    // Set LEDs 4-7 to yellow
    for (int i = 4; i < 8; ++i) {
        leds[i].r = 255;
        leds[i].g = 255;
        leds[i].b = 0;
    }
    ws2812_setleds(leds, 8); // Send to LED strip
}

void red_led() {
    // Ensure all LEDs are off before turning on red LEDs
    turn_off_leds();
    // Set all LEDs to red
    for (int i = 0; i < 8; ++i) {
        leds[i].r = 255;
        leds[i].g = 0;
        leds[i].b = 0;
    }
    ws2812_setleds(leds, 8); // Send to LED strip
}

void flash_led() {
    // Ensure all LEDs are off before flashing
    turn_off_leds();
    // Flash all LEDs
    for (int i = 0; i < 8; ++i) {
        leds[i].r = 255;
        leds[i].g = 255;
        leds[i].b = 255;
    }
    ws2812_setleds(leds, 8); // Send to strip
    avr_wait(500);           // Wait for 500 ms
    turn_off_leds();         // Turn off LED strip
    avr_wait(500);           // Wait for 500 ms
}

void turn_off_leds() {
    for (int i = 0; i < 8; ++i) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
    ws2812_setleds(leds, 8); // Send to LED strip
}

void led_test() {
    turn_off_leds();
    avr_wait(2000);
    // Set all leds to red
    for (int i = 0; i < 8; ++i) {
        leds[i].r = 255;
        leds[i].g = 0;
        leds[i].b = 0;
    }
    ws2812_setleds(leds, 8); // Send to LED strip
}

////////////////////////////////////////// SOUND DETECTOR //////////////////////////////////////////

// Initialize ADC
void adc_init() {
    ADMUX = (1 << REFS0);                               // AVCC as ref, ADC0
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, prescaler 64
}

// Read ADC
int adc_read() {
    ADCSRA |= (1 << ADSC);        // Start conversion
    while (ADCSRA & (1 << ADSC)); // Wait for it to finish
    return ADCW;                  // Return 10-bit result
}

int get_audio_level() {
    int sum_levels = 0;
    for(int i = 0; i < 10; ++i) {        // Take 10 readings for averaging
        avr_wait(10);                    // Wait for 10 ms between readings
        sum_levels += get_one_reading(); // Get one reading from ADC
    }
    int level = sum_levels / 5;          // Average the readings

    return level;
}

int get_one_reading() {
    int reading = adc_read(); // Read the ADC value
    return reading;           // Return the ADC value
}