#include <Arduino.h>
#include <RunnableLed.h>

RunnableLed ledOnboard = RunnableLed(
    LED_BUILTIN, // pin your LED is connected to
    HIGH // "on" state for the LED
);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    ledOnboard.flashIndefinitely(
        1000 // delay time in milliseconds
    );
}

void loop() {
    // other logic

    yield();
    ledOnboard.run(); 
}