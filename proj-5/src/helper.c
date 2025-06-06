#include "helper.h"
#include "avr.h"
#include <stdio.h>
#include <stdlib.h>
#include "ws2812_config.h" // LED strip config
#include "light_ws2812.h"  // LED strip library

///////////////////
// HELPER FUNCTIONS
///////////////////

////////////////////////////////////////// LEDS //////////////////////////////////////////

//Code implementations for future interations with LED strips are commented out

int GREEN_LED = 1;
int YELLOW_LED = 3;
int RED_LED = 5;
int FLASH1_LED = 0;
int FLASH2_LED = 1;
int FLASH3_LED = 2;
// struct cRGB leds[8]; // Pre-built struct from light_ws2812 library with internal uint8_t r, g, b

void led_init() {
    // Set GREEN, YELLOW, RED LED pins to output
    DDRD |= (1 << PIN1) | (1 << PIN3) | (1 << PIN5);
    // Set FLASH1, FLASH2, FLASH3 LED pins to output
    DDRB |= (1 << PIN0) | (1 << PIN1) | (1 << PIN2);
    // DDRD |= (1 << PD5);  // Make PD5 output
}

void green_led_on() {
    SET_BIT(PORTD, GREEN_LED);  // Turn on the green LED

    // // Set LEDs 0-7 to green
    // for (int i = 0; i < 8; ++i) {
    //     leds[i].r = 255;
    //     leds[i].g = 0;
    //     leds[i].b = 0;
    // }
    // ws2812_setleds(leds, 8); // Send to LED strip
}

void green_led_off() {
    CLR_BIT(PORTD, GREEN_LED);  
}

void yellow_led_on() {
    SET_BIT(PORTD, YELLOW_LED); // Turn on the yellow LED
    // // Set LEDs 0-3 to green
    // for (int i = 0; i < 4; ++i) {
    //     leds[i].r = 0;
    //     leds[i].g = 255;
    //     leds[i].b = 0;
    // }
    // // Set LEDs 4-7 to yellow
    // for (int i = 4; i < 8; ++i) {
    //     leds[i].r = 255;
    //     leds[i].g = 255;
    //     leds[i].b = 0;
    // }
    // ws2812_setleds(leds, 8); // Send to LED strip
}

void yellow_led_off() {
    CLR_BIT(PORTD, YELLOW_LED);
}

void red_led_on() {
    SET_BIT(PORTD, RED_LED);
    // // Set all LEDs to red
    // for (int i = 0; i < 8; ++i) {
    //     leds[i].r = 255;
    //     leds[i].g = 0;
    //     leds[i].b = 0;
    // }
    // ws2812_setleds(leds, 8); // Send to LED strip
}

void red_led_off() {
    CLR_BIT(PORTD, RED_LED);
}

void flash_led() {
    // Ensure all LEDs are off before flashing
    turn_off_leds();
    avr_wait(500); // Wait for 500 ms before flashing
    // Turn on entire RGB LED for full white
    SET_BIT(PORTB, FLASH1_LED); // Turn on the red LED
    SET_BIT(PORTB, FLASH2_LED); // Turn on the blue LED
    SET_BIT(PORTB, FLASH3_LED); // Turn on the green LED
    avr_wait(500);
    // Flash all LEDs
    // for (int i = 0; i < 8; ++i) {
    //     leds[i].r = 255;
    //     leds[i].g = 255;
    //     leds[i].b = 255;
    // }
    // ws2812_setleds(leds, 8); // Send to strip
}

void turn_off_leds() {
    CLR_BIT(PORTB, FLASH1_LED);  // Turn off the RBG LED
    CLR_BIT(PORTB, FLASH2_LED); // Turn off the RGB LED
    CLR_BIT(PORTB, FLASH3_LED);  // Turn off the RGB LED
    CLR_BIT(PORTD, GREEN_LED);    // Turn off the green LED
    CLR_BIT(PORTD, YELLOW_LED); // Turn off the yellow LED
    CLR_BIT(PORTD, RED_LED);    // Turn off the red LED
    // for (int i = 0; i < 8; ++i) {
    //     leds[i].r = 0;
    //     leds[i].g = 0;
    //     leds[i].b = 0;
    // }
    // ws2812_setleds(leds, 8); // Send to LED strip
}

void led_test() {
    // turn_off_leds();
    // avr_wait(2000);
    // Set all leds to red
    // for (int i = 0; i < 8; ++i) {
    //     leds[i].r = 255;
    //     leds[i].g = 0;
    //     leds[i].b = 0;
    // }
    // ws2812_setleds(leds, 8); // Send to LED strip
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