#include "helper.h"
#include "avr.h"
#include <stdio.h>
#include <stdlib.h>

///////////////////
// HELPER FUNCTIONS
///////////////////

// Initialize ADC
void adc_init() {
    ADMUX = (1 << REFS0) | (1 << MUX0);                 // AVCC as ref, ADC1
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, prescaler 64
}

// Read ADC
uint16_t adc_read() {
    ADCSRA |= (1 << ADSC);                              // Start conversion
    while (ADCSRA & (1 << ADSC));                       // Wait for it to finish
    return ADCW;                                        // Return 10-bit result
}

uint16_t get_audio_level() {
    uint16_t level = adc_read();
    // Optionally add smoothing or scaling
    return level;
}

void green_led() {

}

void yellow_led() {

}

void red_led() {

}

void flash_led() {
    
}