#include <Arduino.h>
#include <HardwareSerial.h>
#include "MaraData.h"

MaraData::MaraData(DisplayData &displayData) : displayData(displayData)
{
    initialize();
}

// Initialize display and serial connections
void MaraData::initialize()
{
    Serial.begin(9600);
    Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
    Serial1.write(0x11);
}

// Method to get data from Maria coffee machine
void MaraData::getMaraData(void)
{
    /*
  Example Data: C1.06,116,124,093,0840,1,0\n every ~400-500ms
  Length: 26
  [Pos] [Data] [Describtion]
  0)      C     Coffee Mode (C) or SteamMode (V)
  -        1.06  Software Version
  1)      116   current steam temperature (Celsisus)
  2)      124   target steam temperature (Celsisus)
  3)      093   current hx temperature (Celsisus)
  4)      0840  countdown for 'boost-mode'
  5)      1     heating element on or off
  6)      0     pump on or off
*/
    unsigned long m_Serial1Timeout = 0U;
    uint8_t m_tmp_index = 0U;
    char m_buffer[BUFFER_SIZE];
    memset(m_buffer, 0, BUFFER_SIZE);

    while (Serial1.available())
    {
        m_Serial1Timeout = millis();
        char rcv = Serial1.read();
        if (rcv != '\n')
            m_buffer[m_tmp_index++] = rcv;
        else
        {
            m_tmp_index = 0U;
            Serial.println(m_buffer);
            char *ptr = strtok(m_buffer, ",");
            size_t idx = 0U;
            while (ptr != NULL && idx < MARADATA_MAX_ELEMENT_NUM)
            {
                strncpy(maraData[idx], ptr, MARADATA_MAX_ELEMENT_SIZE - 1);
                maraData[idx][MARADATA_MAX_ELEMENT_SIZE - 1U] = '\0'; // Ensure null-terminated
                idx++;
                ptr = strtok(NULL, ",");
            }
        }
    }
    if (millis() - m_Serial1Timeout > 6000)
    {
        m_Serial1Timeout = millis();
        Serial1.write(0x11);
    }
}

void MaraData::updateDisplayData(void)
{
    displayData.mode = maraData[MODE][0];
    displayData.current_steam_temp = atoi(&maraData[CURRENT_STEAM_TEMP][0]);
    displayData.target_steam_temp = atoi(&maraData[TARGET_STEAM_TEMP][0]);
    displayData.current_hx_temp = atoi(&maraData[CURRENT_HX_TEMP][0]);
    displayData.countdown_boost = atoi(&maraData[COUNTDOWN_BOOST][0]);
    displayData.heating_state = atoi(&maraData[HEATING_STATE][0]);
    displayData.pump_state = atoi(&maraData[PUMP_STATE][0]);
}
