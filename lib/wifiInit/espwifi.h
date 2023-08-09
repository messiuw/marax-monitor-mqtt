#ifndef ESPWIFI_H
#define ESPWIFI_H

#include <WiFi.h>

class EspWifi
{
public:
    EspWifi();

    void wifiDiscon(void);
    void loop(void);
    bool connectionActive = false;

private:
    void initialize(void);

    static constexpr const char *SSID = "xxxx";
    static constexpr const char *PWD = "xxxx";
};

#endif // ESPWIFI_H