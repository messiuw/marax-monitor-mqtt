#ifndef MARA_DATA_H
#define MARA_DATA_H

#include <Adafruit_SSD1306.h>

class MaraData
{
public:
    MaraData();
    void initialize();
    void getMaraData();

private:
    static const uint8_t BUFFER_SIZE = 50U;
    static const uint8_t RXD2 = 16U;
    static const uint8_t TXD2 = 17U;

    Adafruit_SSD1306 m_display;
    String *m_lastMaraData;
    long m_lastMillis;
    int m_seconds;
    int m_lastTimer;
    long m_Serial1Timeout;
    char m_buffer[BUFFER_SIZE];
    int m_tmp_index;
    int m_pumpState;
};

#endif // MARA_DATA_H