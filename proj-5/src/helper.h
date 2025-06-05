#ifndef _helper_h
#define _helper_h

///////////////////
// HELPER FUNCTIONS
///////////////////

void led_init();
void green_led();
void yellow_led();
void red_led();
void flash_led();
void turn_off_leds();
void led_test();

void adc_init();
int adc_read();
int get_audio_level();
int get_one_reading();

#endif /* _helper_h */