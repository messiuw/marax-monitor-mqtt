#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DisplayData.h"

class OledDisplay
{
public:
    OledDisplay(DisplayData &displayData);
    void initialize(void);
    void updateView(void);

private:
    static const uint8_t SCREEN_WIDTH = 128U; // Width in px
    static const uint8_t SCREEN_HEIGHT = 64U; // Height in px
    static const int8_t OLED_RESET = -1;
    static const uint8_t SCREEN_ADDRESS = 0x3C; // or 0x3D Check datasheet or Oled Display
    static const uint8_t BUFFER_SIZE = 50U;
    static const uint8_t RXD2 = 16U;
    static const uint8_t TXD2 = 17U;

    static const uint8_t SHOW_NEW_TIMER_THRESHOLD = 3U;

    DisplayData &displayData;

    Adafruit_SSD1306 display_handler;

    void updateLastTimer(void);
    void updateTimer(void);
    void updateMode(void);
    void updateSteam(void);
    void updatePump(void);
    void updateHeater(void);
    void updateHx(void);
};

#endif // OLED_DISPLAY_H