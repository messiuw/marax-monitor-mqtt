#include <Arduino.h>
#include <Wire.h>
#include "OledDisplay.h"

OledDisplay::OledDisplay()
    : m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
    m_seconds = 0;
    m_lastTimer = 0;
    m_tmp_index = 0;
    m_pumpState = 0;
    memset(m_buffer, 0, BUFFER_SIZE);
    // TODO add reset of all values
}

void OledDisplay::initialize()
{
    m_display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    delay(1000);
    m_display.clearDisplay();
    m_display.setTextSize(1);
    m_display.setTextColor(WHITE);
    m_display.setCursor(0, 0);
}

// Method to update the display with coffee machine data
void OledDisplay::updateView(String *maraData)
{
    m_display.clearDisplay();
    m_display.setTextColor(WHITE);
    // HX
    m_display.setCursor(2, 2);
    m_display.setTextSize(2);
    m_display.print(maraData[3].toInt());
    m_display.setTextSize(1);
    m_display.print((char)247);
    m_display.setTextSize(1);
    m_display.print("C");
    // Pump
    m_display.setCursor(2, 30);
    m_display.print("H");
    if (maraData[5].toInt() == 0)
        m_display.drawCircle(17, 33, 6, WHITE);
    else
        m_display.fillCircle(17, 33, 5, WHITE);
    m_display.setCursor(30, 30);
    // Heater
    m_display.print("P");
    if (maraData[6].toInt() == 0)
        m_display.drawRect(40, 28, 10, 10, WHITE);
    else
        m_display.fillRect(40, 28, 10, 10, WHITE);
    // Steam
    m_display.setCursor(2, 50);
    m_display.setTextSize(2);
    m_display.print(maraData[1].toInt());
    m_display.setTextSize(1);
    m_display.print((char)247);
    m_display.setTextSize(1);
    m_display.print("C");
    m_display.drawLine(55, 0, 55, 68, WHITE);
    m_display.setCursor(65, 15);
    m_display.setTextSize(5);
    // Timer
    if (m_seconds > 3)
    {
        String actual = String(m_seconds);
        if (actual.length() < 2)
            actual = "0" + actual;
        m_display.print(actual);
    }
    else if (m_lastTimer > 3)
    {
        String last = String(m_lastTimer);
        if (last.length() < 2)
            last = "0" + last;
        m_display.print(last);
    }
    else
    {
        m_display.print("00");
    }
    // Mode
    m_display.setTextSize(1);
    m_display.setCursor(120, 2);
    m_display.print(maraData[0].substring(0, 1));
    m_display.display();
}