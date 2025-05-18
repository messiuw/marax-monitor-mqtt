#ifndef MQTT_H
#define MQTT_H

#include <ESP8266WiFi.h>
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

    bool isMaraOn(void);

    bool connectionActive = false;

private:
    WiFiClient espClient;
    // MQTT Client
    PubSubClient client;

    DisplayData &displayData;

    bool isOn = false;
    static constexpr const char *server = "192.168.178.103";
    static constexpr const uint16_t port = 1883;
    static constexpr const char *TOPIC_MODE = "marax/mode";
    static constexpr const char *TOPIC_CURRENT_STEAM_TEMP = "marax/bo_temperature";
    static constexpr const char *TOPIC_TARGET_STEAM_TEMP = "marax/bo_target_temperature";
    static constexpr const char *TOPIC_CURRENT_HX_TEMP = "marax/hx_temperature";
    static constexpr const char *TOPIC_HEATING_STATE = "marax/heating_state";
    static constexpr const char *TOPIC_PUMP_STATE = "marax/pump_state";
    static constexpr const char *TOPIC_MONITOR_VERSION = "marax/monitor_version";
    static constexpr const char *TOPIC_MARAX_POWER_STATE = "marax/power";

    void send_int_val(const char *topic, const uint8_t &value);
    void reconnect(void);
    void onMessageReceived(char *topic, byte *payload, unsigned int length);
};

#endif // MQTT_H
