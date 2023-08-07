#include "MaraTimer.h"

MaraTimer::MaraTimer(DisplayData &displayData) : displayData(displayData)
{
}

void MaraTimer::run(void)
{
    if (timerActive)
    {
        constexpr unsigned long SECONDS_IN_MS = 1000U;
        if (millis() - lastMillis >= SECONDS_IN_MS)
        {
            lastMillis = millis();
            ++seconds;
            if (seconds > MAX_DISPLAY_TIMER_VALUE)
                seconds = 0U;
        }
    }
    else
    {
        if (seconds != 0U)
        {
            lastTimer = seconds;
        }
        seconds = 0U;
    }
}

void MaraTimer::updateDisplayData(void)
{
    displayData.lastTimer_sec = lastTimer;
    displayData.timer_sec = seconds;
}