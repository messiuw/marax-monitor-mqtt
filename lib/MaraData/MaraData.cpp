#include <Arduino.h>
#include <HardwareSerial.h>
#include "MaraData.h"

String maraData[5];

MaraData::MaraData()
{
    m_lastMaraData = maraData;
    m_seconds = 0;
    m_lastTimer = 0;
    m_Serial1Timeout = 0;
    m_tmp_index = 0;
    m_pumpState = 0;
    memset(m_buffer, 0, BUFFER_SIZE);
}

// Initialize display and serial connections
void MaraData::initialize()
{
    Serial.begin(9600);
    Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
    Serial1.write(0x11);
}

// Method to get data from Maria coffee machine
void MaraData::getMaraData()
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
    while (Serial1.available())
    {
        m_Serial1Timeout = millis();
        char rcv = Serial1.read();
        if (rcv != '\n')
            m_buffer[m_tmp_index++] = rcv;
        else
        {
            m_tmp_index = 0;
            Serial.println(m_buffer);
            char *ptr = strtok(m_buffer, ",");
            int idx = 0;
            while (ptr != NULL)
            {
                maraData[idx++] = String(ptr);
                ptr = strtok(NULL, ",");
            }
            m_lastMaraData = maraData;
        }
    }
    if (millis() - m_Serial1Timeout > 6000)
    {
        m_Serial1Timeout = millis();
        Serial1.write(0x11);
    }
}
