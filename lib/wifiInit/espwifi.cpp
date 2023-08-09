#include "espwifi.h"

EspWifi::EspWifi()
{
    initialize();
}

void EspWifi::initialize(void)
{
    Serial.println("Start connection");
    Serial.print("Connect to:");
    Serial.println(SSID);
    if (!connectionActive)
    {
        WiFi.persistent(true);
        WiFi.mode(WIFI_STA);
        if (WiFi.begin(SSID, PWD) != WL_CONNECT_FAILED)
        {
            Serial.println("Waiting for connection...");
            while (WiFi.status() != WL_CONNECTED)
            {
                Serial.print('.');
                delay(500);
            }
            Serial.println("Wifi connected!");
            connectionActive = true;
            WiFi.setAutoReconnect(true);
        }
    }
}

void EspWifi::wifiDiscon(void)
{
    WiFi.disconnect();
    connectionActive = false;
}

void EspWifi::loop(void)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.reconnect();
        delay(5000U);
    }
}
