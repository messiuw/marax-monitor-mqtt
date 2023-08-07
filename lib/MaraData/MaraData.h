#ifndef MARA_DATA_H
#define MARA_DATA_H

#include <Adafruit_SSD1306.h>
#include "DisplayData.h"

class MaraData
{
public:
    MaraData(DisplayData &displayData);

    enum DataPos
    {
        MODE = 0U,
        CURRENT_STEAM_TEMP,
        TARGET_STEAM_TEMP,
        CURRENT_HX_TEMP,
        COUNTDOWN_BOOST,
        HEATING_STATE,
        PUMP_STATE,
        LAST_ELEMENT = PUMP_STATE,
    };

    static constexpr uint8_t MARADATA_MAX_ELEMENT_SIZE = 5U;

    void updateDisplayData(void);

private:
    static const uint8_t BUFFER_SIZE = 50U;
    static const uint8_t RXD2 = 16U;
    static const uint8_t TXD2 = 17U;

    static constexpr uint8_t MARADATA_MAX_ELEMENT_NUM = DataPos::LAST_ELEMENT + 1U;
    char maraData[MARADATA_MAX_ELEMENT_NUM][MARADATA_MAX_ELEMENT_SIZE];

    DisplayData displayData;

    void initialize(void);
    void getMaraData(void);
};

#endif // MARA_DATA_H