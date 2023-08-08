// Includes
#include <Arduino.h>
#include "MaraData.h"
#include "OledDisplay.h"
#include "mqtt.h"
#include "espwifi.h"
#include "MaraTimer.h"

void setup()
{
    Serial.begin(9600);
    EspWifi espWifi;
}

void loop()
{
    DisplayData displayData = {};
    DisplayData displayDataOld = displayData;
    Mqtt mqtt(displayData);
    MaraData marax(displayData);
    MaraTimer timer(displayData);
    OledDisplay oled(displayData);

    while (true)
    {
        (displayData.pump_state == 1) ? timer.start() : timer.stop();
        timer.run();
        marax.getMaraData();
        timer.updateDisplayData();
        if (memcmp(&displayData, &displayDataOld, sizeof(DisplayData)) != 0)
        {
            displayDataOld = displayData;
            oled.updateView();
            mqtt.sendMaraData();
        }
    }
}