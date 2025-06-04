#ifndef _helper_h
#define _helper_h

///////////////////
// HELPER FUNCTIONS
///////////////////

void adc_init();
int adc_read();
int get_audio_level();
void green_led();
void yellow_led();
void red_led();
void flash_led();
void turn_off_leds();

#endif /* _helper_h */