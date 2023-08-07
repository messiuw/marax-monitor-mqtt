#include "espwifi.h"

EspWifi::EspWifi()
{
    initialize();
}

void EspWifi::initialize(void)
{
    // m_debug.println("Start connection");
    // m_debug.print("Connect to:");
    // m_debug.println(ssid);
    if (!connectionActive)
    {
        WiFi.persistent(true);
        WiFi.mode(WIFI_STA);
        if (WiFi.begin(SSID, PWD) != WL_CONNECT_FAILED)
        {
            // m_debug.println("Waiting for connection...");
            connectionActive = (WiFi.waitForConnectResult() == WL_CONNECTED);
        }
    }
}

void EspWifi::wifiDiscon(void)
{
    WiFi.disconnect();
    connectionActive = false;
}
