// Includes
#include <Arduino.h>
#include "MaraData.h"
#include "OledDisplay.h"
#include "mqtt.h"
#include "espwifi.h"
#include "MaraTimer.h"

void setup()
{
    EspWifi espWifi;
}

void loop()
{
    DisplayData displayData = {};
    Mqtt mqtt(displayData);
    MaraData marax(displayData);
    MaraTimer timer(displayData);
    OledDisplay oled(displayData);

    while (true)
    {
        (displayData.pump_state == 1) ? timer.start() : timer.stop();
        timer.run();
        marax.updateDisplayData();
        timer.updateDisplayData();
        oled.updateView();
        mqtt.sendMaraData();
    }
}