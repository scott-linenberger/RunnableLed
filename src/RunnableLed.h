#ifndef RUNNABLE_LED_H
#define RUNNABLE_LED_H

#include <Arduino.h>

enum RunnableLedState {
    RUNNABLE_LED_PRE_START,
    RUNNABLE_LED_ON,
    RUNNABLE_LED_OFF,
    RUNNABLE_LED_FLASHING_INDEF,
    RUNNABLE_LED_FLASHING_TIMES,
};

class RunnableLed {
    private:
        uint8_t pinLed;
        bool pinStateOn; // PIN STATE REQUIRED TO TURN THE LED ON

        /* state */
        RunnableLedState statePrev = RUNNABLE_LED_PRE_START;
        RunnableLedState stateCurr;
        bool currPinState;
        bool _isFinished;
        
        /* flash vars */
        uint8_t numFlashes;
        uint8_t countFlashes;
        unsigned long tsFlashStart;
        uint16_t msDelayFlash;

    public:
        RunnableLed(
            uint8_t _pinLed,
            bool _pinStateOn
        ): pinLed(_pinLed), pinStateOn(_pinStateOn) {};
        void run();
        void on();
        void off();
        void flashIndefinitely(uint16_t _msDelayFlash);
        void flashTimes(uint8_t _numFlashes, uint16_t _msDelayFlash);
        bool isFinished();
};

#endif