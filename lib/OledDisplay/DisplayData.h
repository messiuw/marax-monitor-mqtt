#ifndef DISPLAYDATA_H
#define DISPLAYDATA_H

#include <Arduino.h>

struct DisplayData
{
    uint8_t timer_sec;
    uint8_t lastTimer_sec;
    char mode;
    uint8_t current_steam_temp;
    uint8_t target_steam_temp;
    uint8_t current_hx_temp;
    uint8_t countdown_boost;
    uint8_t heating_state;
    uint8_t pump_state;
};

#endif // DISPLAYDATA_H