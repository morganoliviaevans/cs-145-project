#include "avr.h"

void avr_init(void) {
    WDTCR = 15;
}

void avr_wait(unsigned short msec) {
    // Timer and counter control register 0 (stores prescaler)
    TCCR0 = 3;
    // Weird ass math
    while (msec--) {
        // Timer and counter register 0 (stores current value of timer, and ticks counted so far)
        TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001); // 256 - (8,000,000 / 64 = 125k) = 131
        SET_BIT(TIFR, TOV0);
        WDR();
        while (!GET_BIT(TIFR, TOV0));
    }
    TCCR0 = 0;
}