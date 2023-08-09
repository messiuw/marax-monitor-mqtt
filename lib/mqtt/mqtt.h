#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "DisplayData.h"

class Mqtt
{
public:
    Mqtt(DisplayData &displayData);

    void connect(void);
    void loop(void);
    void send(const char *topic, const char *payload);
    void stop(void);

    void sendMaraData(void);

    bool connectionActive = false;

private:
    WiFiClient espClient;
    // MQTT Client
    PubSubClient client;

    DisplayData &displayData;

    static constexpr const char *server = "xxxx";
    static constexpr const uint16_t port = 1883;
    static constexpr const char *username = "xxxx";
    static constexpr const char *password = "xxxx";
    static constexpr const char *TOPIC_MODE = "marax/mode";
    static constexpr const char *TOPIC_CURRENT_STEAM_TEMP = "marax/steam/temp/current";
    static constexpr const char *TOPIC_TARGET_STEAM_TEMP = "marax/steam/temp/target";
    static constexpr const char *TOPIC_CURRENT_HX_TEMP = "marax/hx/temp/current";
    static constexpr const char *TOPIC_HEATING_STATE = "marax/heating/state";
    static constexpr const char *TOPIC_PUMP_STATE = "marax/pump/state";

    void send_int_val(const char *topic, const uint8_t &value);
    void reconnect(void);
};

#endif // MQTT_H
