// Includes
#include <Arduino.h>
#include "MaraData.h"
#include "OledDisplay.h"

// Internals
long lastMillis;
int seconds = 0;
int lastTimer = 0;

// Mara Data
String maraData[7];
String *lastMaraData;

void setup()
{
}

void loop()
{
  // getMaraData();
  int pumpState = lastMaraData[6].toInt();
  if (pumpState == 1)
  {
    if (millis() - lastMillis >= 1000)
    {
      lastMillis = millis();
      ++seconds;
      if (seconds > 99)
        seconds = 0;
    }
  }
  else
  {
    if (seconds != 0)
      lastTimer = seconds;
    seconds = 0;
  }
  // updateView();
}
