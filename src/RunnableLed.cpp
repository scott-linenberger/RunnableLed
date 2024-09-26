#include "RunnableLed.h"

void RunnableLed::run() {
    yield();
    
    // act on state
    switch (stateCurr) {
        case RUNNABLE_LED_OFF:
            if (statePrev == stateCurr) {
                return; // nothing to do, LED is already OFF
            }

            // states don't match, turn LED OFF, update states
            digitalWrite(pinLed, !pinStateOn);
            statePrev = RUNNABLE_LED_OFF;
            break;

        case RUNNABLE_LED_ON:
            if (statePrev == stateCurr) {
                return; // nothing to do, LED is already ON
            }

            // states don't match, turn LED ON, update states
            digitalWrite(pinLed, pinStateOn);
            statePrev = RUNNABLE_LED_ON;            
            break;

        case RUNNABLE_LED_FLASHING_INDEF:
            /* if the flash delay timeout has expired */
            if (millis() - tsFlashStart >= msDelayFlash) {
                currPinState = !currPinState; // toggle pin state
                digitalWrite(pinLed, currPinState); // write state to the pin
                tsFlashStart = millis(); // update the timestamp
            }
            break;

        case RUNNABLE_LED_FLASHING_TIMES:
            /* if the number of flashes has NOT been reached */
            if (countFlashes < numFlashes) {
                if (millis() - tsFlashStart >= msDelayFlash) {
                    /* check if the flash timestamp has expired */
                    currPinState = !currPinState; // toggle pin state
                    digitalWrite(pinLed, currPinState); // write state to the pin
                    tsFlashStart = millis(); // update the timestamp
                    
                    if (currPinState != pinStateOn) {
                        countFlashes++; // increment flash counter when led is ON 
                    }
                }
            }

            if (countFlashes >= numFlashes) {
                // flash count reached, turn LED OFF
                stateCurr = RUNNABLE_LED_OFF; // set state to OFF
                statePrev = RUNNABLE_LED_FLASHING_TIMES;
                _isFinished = true;
            }

            break;

        default:
            break;
    }
}

void RunnableLed::off() {
    stateCurr = RUNNABLE_LED_OFF;
    digitalWrite(pinLed, !pinStateOn);
}

void RunnableLed::on() {
    stateCurr = RUNNABLE_LED_ON;
    digitalWrite(pinLed, pinStateOn);
}

void RunnableLed::flashIndefinitely(uint16_t _msDelayFlash) {
    // set current pin state to "ON" & write state to pin
    currPinState = pinStateOn;
    digitalWrite(pinLed, currPinState);

    // reset timestamp
    tsFlashStart = millis();

    // update state -> flashing indefinitely
    msDelayFlash = _msDelayFlash;
    stateCurr = RUNNABLE_LED_FLASHING_INDEF;
}

void RunnableLed::flashTimes(uint8_t _numFlashes, uint16_t _msDelayFlash) {
    if (_numFlashes == 0) {
        return;
    }

    // set current pin state to "ON" & write state to pin
    currPinState = pinStateOn;
    digitalWrite(pinLed, currPinState);

    // reset timestamp
    tsFlashStart = millis();

    // update state -> flashing times
    countFlashes = 0;
    msDelayFlash = _msDelayFlash;
    numFlashes = _numFlashes;
    _isFinished = false;

    stateCurr = RUNNABLE_LED_FLASHING_TIMES;
}

bool RunnableLed::isFinished() {
    return _isFinished;
}