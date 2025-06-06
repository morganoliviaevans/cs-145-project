#include <stdio.h>
#include <avr.h>
#include <helper.h>

#define AUDIO_PORT PORTA
#define AUDIO_DDR DDRA
#define AUDIO_PIN PA1

/*
State Logic:
- LISTENING State:
    - Analyze audio levels
    - Adjust LED color based on audio level
    - If user enters and stays in red for longer than 5 seconds, go into FLASH state
- FLASH State:
    - Pause listening for audio level
    - Set timer to 30 seconds
    - Flash 'em for 30 seconds
    - Go back to LISTEN state
*/

//Code implementations for future interations with LED strips are commented out

int main() {

    led_init();
    typedef enum {LISTENING, FLASH} AudioState;
    AudioState audio_state = LISTENING;
    float audio_level = 0;
    int red_counter = 0;
    int red_max = 10; 
    int flash_duration = 5; // seconds
    AUDIO_DDR &= ~(1 << AUDIO_PIN);
    adc_init();
    avr_wait(1000);

    while(1) {
        // LISTENING State
        if (audio_state == LISTENING) {
            // Get audio level from ADC
            audio_level = get_audio_level();
            green_led_on();

            // If sound level is at elevated volume, turn on yellow LED
            if (audio_level >= 20) {
                // Set LED to yellow
                yellow_led_on();
            } else {
                // If sound level is below 20, turn off yellow LED
                yellow_led_off();
            }

            // If sound level is greater than 40, turn on red LED
            if (audio_level > 40) {
                // Set LED to red
                red_led_on();
                red_counter++;
                // If it has been max infractions at excessive volume, enter FLASH state
                if (red_counter > red_max) {
                    audio_state = FLASH;
                }
            } else {
                // If sound level is below 40, turn off red LED
                red_led_off();
            }
        } 
        // FLASH State
        if (audio_state == FLASH) {
            // Turn off all LEDs
            turn_off_leds();
            // Reset our counter while in FLASH state
            red_counter = 0;
            // Commence FLASH sequence for flash_duration seconds
            for(int i = 0; i < flash_duration; ++i) {
                flash_led();
            }
            turn_off_leds();
            // Go back to LISTEN state
            audio_state = LISTENING;
        } 
    }
}