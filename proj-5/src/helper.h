#ifndef _helper_h
#define _helper_h

///////////////////
// HELPER FUNCTIONS
///////////////////

void led_setup();
void adc_init();
int adc_read();
int get_audio_level();
void green_led();
void blue_led();
void red_led();
void flash_led();
void turn_off_leds();
int get_one_reading();

#endif /* _helper_h */