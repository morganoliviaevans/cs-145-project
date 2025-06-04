#ifndef _helper_h
#define _helper_h

///////////////////
// HELPER FUNCTIONS
///////////////////

void adc_init();
uint16_t adc_read();
uint16_t get_audio_level();
void green_led();
void yellow_led();
void red_led();
void flash_led();

#endif /* _helper_h */