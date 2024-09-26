#include <Arduino.h>
#include <RunnableLed.h>

bool hasFlashed = false;

RunnableLed ledOnboard = RunnableLed(
    LED_BUILTIN, // led pin
    HIGH // "on" state for led pin
);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    ledOnboard.off();
}

void loop() {
    // flash three times after 5 seconds
    if (millis() > 5000) {
        ledOnboard.flashTimes(3, 50);
        hasFlashed = true;
    }

    // other logic

    yield();
    ledOnboard.run();
}