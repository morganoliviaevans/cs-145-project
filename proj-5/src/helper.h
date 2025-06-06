#ifndef _helper_h
#define _helper_h

///////////////////
// HELPER FUNCTIONS
///////////////////

void led_init();
void green_led_on();
void yellow_led_on();
void red_led_on();
void green_led_off();
void yellow_led_off();
void red_led_off();
void flash_led();
void turn_off_leds();
void led_test();

void adc_init();
int adc_read();
int get_audio_level();
int get_one_reading();

#endif /* _helper_h */