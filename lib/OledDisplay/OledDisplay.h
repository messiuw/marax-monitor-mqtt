#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OledDisplay
{
public:
    OledDisplay();
    void initialize();
    void updateView(String *maraData);

private:
    static const uint8_t SCREEN_WIDTH = 128U; // Width in px
    static const uint8_t SCREEN_HEIGHT = 64U; // Height in px
    static const int8_t OLED_RESET = -1;
    static const uint8_t SCREEN_ADDRESS = 0x3C; // or 0x3D Check datasheet or Oled Display
    static const uint8_t BUFFER_SIZE = 50U;
    static const uint8_t RXD2 = 16U;
    static const uint8_t TXD2 = 17U;

    Adafruit_SSD1306 m_display;

    long m_lastMillis;
    int m_seconds;
    int m_lastTimer;
    char m_buffer[BUFFER_SIZE];
    int m_tmp_index;
    int m_pumpState;
};

#endif // OLED_DISPLAY_H