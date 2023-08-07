#include <Arduino.h>
#include <Wire.h>
#include "OledDisplay.h"

OledDisplay::OledDisplay(DisplayData &displayData)
    : displayData(displayData), display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
}

void OledDisplay::initialize()
{
    display_handler.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    delay(1000U);
    display_handler.clearDisplay();
    display_handler.setTextSize(1);
    display_handler.setTextColor(WHITE);
    display_handler.setCursor(0, 0);
}

// Method to update the display with coffee machine data
void OledDisplay::updateView(void)
{
    display_handler.clearDisplay();
    display_handler.setTextColor(WHITE);

    updateHeater();
    updatePump();
    updateSteam();
    updateTimer();
    updateMode();
}

void OledDisplay::updateTimer(void)
{
    if (displayData.timer_sec > SHOW_NEW_TIMER_THRESHOLD)
    {
        String actual = String(displayData.timer_sec);
        if (actual.length() < 2)
            actual = "0" + actual;
        display_handler.print(actual);
    }
    else if (displayData.lastTimer_sec > SHOW_NEW_TIMER_THRESHOLD)
    {
        String last = String(displayData.lastTimer_sec);
        if (last.length() < 2)
            last = "0" + last;
        display_handler.print(last);
    }
    else
    {
        display_handler.print("00");
    }
}

void OledDisplay::updateMode(void)
{
    display_handler.setTextSize(1U);
    display_handler.setCursor(120, 2);
    display_handler.print(displayData.mode);
    display_handler.display();
}

void OledDisplay::updateSteam(void)
{
    display_handler.setCursor(2, 50);
    display_handler.setTextSize(2U);
    display_handler.print(displayData.current_steam_temp);
    display_handler.setTextSize(1U);
    display_handler.print((char)247);
    display_handler.setTextSize(1U);
    display_handler.print("C");
    display_handler.drawLine(55, 0, 55, 68, WHITE);
    display_handler.setCursor(65, 15);
    display_handler.setTextSize(5U);
}
void OledDisplay::updatePump(void)
{
    display_handler.print("P");
    if (displayData.pump_state == 0)
        display_handler.drawRect(40, 28, 10, 10, WHITE);
    else
        display_handler.fillRect(40, 28, 10, 10, WHITE);
}

void OledDisplay::updateHeater(void)
{
    display_handler.setCursor(2, 30);
    display_handler.print("H");
    if (displayData.heating_state == 0)
        display_handler.drawCircle(17, 33, 6, WHITE);
    else
        display_handler.fillCircle(17, 33, 5, WHITE);
    display_handler.setCursor(30, 30);
}

void OledDisplay::updateHx(void)
{
    display_handler.setCursor(2, 2);
    display_handler.setTextSize(2U);
    display_handler.print(displayData.current_hx_temp);
    display_handler.setTextSize(1U);
    display_handler.print((char)247);
    display_handler.setTextSize(1U);
    display_handler.print("C");
}
