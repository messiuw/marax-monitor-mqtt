#include "mqtt.h"
#include <map>
#include "MaraData.h"
#include "version.hpp"

Mqtt::Mqtt(DisplayData &displayData) : displayData(displayData)
{
    connect();
    send(TOPIC_MONITOR_VERSION, APP_VERSION);
}

void Mqtt::connect(void)
{
    if (!connectionActive)
    {
        Serial.println("Start connecting to mqtt server");
        client.setServer(server, port);
        client.setClient(espClient);

        client.setCallback([this](char *topic, byte *payload, unsigned int length) {
            this->onMessageReceived(topic, payload, length);
        });

        while (!client.connected())
        {
            Serial.println("Connecting...");
            if (client.connect("MaraxClient"))
            {
                Serial.println("connected!");
                client.subscribe(TOPIC_MARAX_POWER_STATE);
                connectionActive = true;
                break;
            }
            delay(500U);
        }
    }
}

void Mqtt::onMessageReceived(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    if (strcmp(topic, TOPIC_MARAX_POWER_STATE) == 0) {
        String message;
        for (unsigned int i = 0; i < length; i++) {
            message += (char)payload[i];
        }

        Serial.print("Message: ");
        Serial.println(message);

        if (message == "on") {
            isOn = true;
        } else {
            isOn = false;
        }
    }
}

void Mqtt::reconnect(void)
{
    // Loop until we're reconnected
    unsigned long retryTime = millis();
    static constexpr unsigned long MAX_RETRY_TIME = 10000U;
    while (!client.connected())
    {
        Serial.print("Attempting MQTT reconnection...");
        // Attempt to connect
        if (client.connect("MaraxClient") || ((millis() - retryTime) > MAX_RETRY_TIME))
        {
            Serial.println("connected or timeout");
            break;
        }
        delay(300U);
    }
}

void Mqtt::loop(void)
{
    if (!client.connected())
    {
        connectionActive = false;
        reconnect();
    }
    else
    {
        connectionActive = true;
        client.loop();
    }
}

void Mqtt::send(const char *topic, const char *payload)
{
    if (connectionActive)
    {
        client.publish(topic, payload);
    }
}

void Mqtt::send_int_val(const char *topic, const uint8_t &value)
{
    char msg[MaraData::MARADATA_MAX_ELEMENT_SIZE];
    itoa(value, msg, 10);
    send(topic, msg);
}

void Mqtt::sendMaraData(void)
{
    client.publish(TOPIC_MODE, reinterpret_cast<const uint8_t *>(&displayData.mode), 1, false);

    std::map<const char *, uint8_t> data_topic_map{
        {TOPIC_CURRENT_STEAM_TEMP, displayData.current_steam_temp},
        {TOPIC_TARGET_STEAM_TEMP, displayData.target_steam_temp},
        {TOPIC_CURRENT_HX_TEMP, displayData.current_hx_temp},
        {TOPIC_HEATING_STATE, displayData.heating_state},
        {TOPIC_PUMP_STATE, displayData.pump_state}};

    std::map<const char *, uint8_t>::iterator it;
    for (it = data_topic_map.begin(); it != data_topic_map.end(); it++)
    {
        send_int_val(it->first, it->second);
    }
}

void Mqtt::stop(void)
{
    espClient.stop();
    connectionActive = false;
}


bool Mqtt::isMaraOn(void) {
    return isOn;
}