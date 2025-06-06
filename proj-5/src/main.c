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

int main() {

    led_init();
    typedef enum {LISTENING, FLASH} AudioState;
    AudioState audio_state = LISTENING;
    float audio_level = 0;
    int red_counter = 0;
    int red_max = 3;
    // Set PA1 as input
    AUDIO_DDR &= ~(1 << AUDIO_PIN);
    adc_init();
    avr_wait(500);

    while(1) {
        // LISTENING State
        if (audio_state == LISTENING) {
            // Get audio level from ADC
            audio_level = get_audio_level();
            // If sound level is at acceptable volume, LED is green
            if (audio_level <= 20) {
                // Set LED to green
                green_led();
            }

            // If sound level is at elevated volume, LED is yellow
            if (audio_level > 20 && audio_level <= 40) {
                // Set LED to yellow
                yellow_led();
            }

            // If sound level is at excessive volume, LED is red
            if (audio_level > 40) {
                // Set LED to red
                red_led();
                red_counter++;
                // If it has been 3 infractions at excessive volume, enter FLASH state
                if (red_counter > red_max) {
                    audio_state = FLASH;
                }
            }
        } 
        // FLASH State
        if (audio_state == FLASH) {
            // Reset our counter while in FLASH state
            red_counter = 0;
            // Commence FLASH sequence for 30 seconds
            int i = 0;
            while (i < 60) {
                flash_led();
            }
            // Go back to LISTEN state
            audio_state = LISTENING;
        } 
    }
}