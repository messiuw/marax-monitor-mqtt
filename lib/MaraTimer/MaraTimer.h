#ifndef MARATIMER_H
#define MARATIMER_H

#include <Arduino.h>
#include "DisplayData.h"

class MaraTimer
{
public:
    MaraTimer(DisplayData &displayData);
    void start(void) { timerActive = true; };
    void stop(void) { timerActive = false; };
    void updateDisplayData(void);
    void run(void);

private:
    static constexpr uint8_t MAX_DISPLAY_TIMER_VALUE = 99U;

    bool timerActive = false;
    uint8_t lastTimer = 0U;
    unsigned long lastMillis = 0U;
    uint8_t seconds = 0U;
    DisplayData &displayData;
};

#endif // MARATIMER_H