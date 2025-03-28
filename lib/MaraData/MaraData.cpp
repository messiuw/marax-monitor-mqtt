#include <Arduino.h>
#include <SoftwareSerial.h>
#include "MaraData.h"

SoftwareSerial mySerial(D5, D6);

MaraData::MaraData(DisplayData &displayData) : displayData(displayData)
{
    initialize();
}

// Initialize display and serial connections
void MaraData::initialize()
{    
    mySerial.begin(9600);
    memset(rxBuffer, 0, BUFFER_SIZE);
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
    Serial.println("Get MaraX data...");
    const char startChar[] = {'C', 'V', '+'};

    while (mySerial.available() >= 26)
    {
        char rcv = mySerial.read();
        if ((rcv == startChar[0]) || (rcv == startChar[1]) || (rcv == startChar[2]))
        {
            startCharReceived = true;
            tmpIndex = 0U;
            Serial.println("Start received...");
        }
        if (startCharReceived)
        {
            if (rcv != '\n')
                if (tmpIndex < BUFFER_SIZE)
                {
                    rxBuffer[tmpIndex++] = rcv;
                }
                else
                {
                    Serial.println("BufferIndex full! Clearing...");
                    tmpIndex = 0U;
                    memset(rxBuffer, 0, BUFFER_SIZE);
                    startCharReceived = false;
                }
            else
            {
                tmpIndex = 0U;
                Serial.println(rxBuffer);
                char *ptr = strtok(rxBuffer, ",");
                size_t idx = 0U;
                while (ptr != NULL && idx < MARADATA_MAX_ELEMENT_NUM)
                {
                    strncpy(maraData[idx], ptr, MARADATA_MAX_ELEMENT_SIZE - 1);
                    maraData[idx][MARADATA_MAX_ELEMENT_SIZE - 1U] = '\0'; // Ensure null-terminated
                    idx++;
                    ptr = strtok(NULL, ",");
                }
                updateDisplayData();
                memset(rxBuffer, 0, BUFFER_SIZE);
                startCharReceived = false;
                break;
            }
        }
    }
}

void MaraData::updateDisplayData(void)
{
    Serial.println("Save MaraX data to displayData...");
    displayData.mode = maraData[MODE][0];
    displayData.current_steam_temp = atoi(&maraData[CURRENT_STEAM_TEMP][0]);
    displayData.target_steam_temp = atoi(&maraData[TARGET_STEAM_TEMP][0]);
    displayData.current_hx_temp = atoi(&maraData[CURRENT_HX_TEMP][0]);
    displayData.countdown_boost = atoi(&maraData[COUNTDOWN_BOOST][0]);
    displayData.heating_state = atoi(&maraData[HEATING_STATE][0]);
    displayData.pump_state = atoi(&maraData[PUMP_STATE][0]);
}
