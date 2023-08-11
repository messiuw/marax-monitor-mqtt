# MaraX Monitior with MQTT - Visualisation for the Lelit Mara X (V2) with an automatic Shot-Timer

This project is for anyone who wants to make their Lelit Mara X (V2) espresso machine smarter. Fortunately the MaraX has a serial interface providing some data that can be read!
The project is a fork from [https://github.com/SaibotFlow/marax-monitor](https://github.com/SaibotFlow/marax-monitor).
Inspirations came also from [https://github.com/alexrus/marax_timer](https://github.com/alexrus/marax_timer) and from
[https://github.com/Vin-X-Mod/OLED-Splash-Screen-LOGO/tree/main](https://github.com/Vin-X-Mod/OLED-Splash-Screen-LOGO/tree/main).

![Display](https://github.com/belectronic/marax-monitor-mqtt/blob/main/assets/DisplayInAction.png?raw=true)

## Versioning

I use a [Pythonscript](https://github.com/belectronic/marax-monitor-mqtt/blob/main/lib/Version/version_gen.py) for generating a *version.hpp*
for transmitting a version via MQTT. If you don't need that, or if you don't have python installed please remove the line ```extra_scripts = pre:lib\Version\version_gen.py*``` in [platformio.ini](https://github.com/belectronic/marax-monitor-mqtt/blob/main/platformio.ini).

## Parts

- ESP32 Node MCU (You can use any other equivalent board)
- USB Cable with power supply for ESP32
- Jumper-Wires
- 0,96" SSD1306 OLED Display
- 3D printed case [https://www.thingiverse.com/thing:2937731](https://www.thingiverse.com/thing:2937731)

## Structure & Connections

![Connection](https://github.com/belectronic/marax-monitor-mqtt/blob/main/assets/esp_oled_connection.jpg?raw=true)

## The Interface

The MaraX has a 6-PIN Connector for the serial interface on the bottom. We only use **PIN-3** (Mara RX - Black Wire - Green Rectangle) and **PIN-4** (Mara TX - Orange Wire - White Rectangle). For testing you can use the jumper-wires later you should replace them with temperature protected cables.

- **PIN3 Mara** to  **TX2**
- **PIN4 Mara** to **RX2**

RX Mara to TX2 ESP32 and TX Mara to RX2 ESP32

![MaraX Bottom](https://github.com/belectronic/marax-monitor-mqtt/blob/main/assets/Bottom.png?raw=true)

The connector for serial interface itself

![Marax Connector](https://github.com/belectronic/marax-monitor-mqtt/blob/main/assets/Connector.png?raw=true)
  
  ***Note**: A Reed sensor on the vibration pump is not necessary for the MaraX anymore as the interface provides the pump status information now.*

## The Data

You will receive the following data each ~400ms.

Example Data: **C1.06,116,124,093,0840,1,0\n**

- The delimitter is: **,**
- The end of data is: **\n**
- Length: **26**

|Data|Description |
|--|--|
| + | Machine-Mode (Model 2022): + = CoffeeMode; C = SteamMode |
| 1.06 | Firmware |
| 116 | Current Steam Temperature in Celsius |
| 124| Target Steam Temperature in Celsius |
| 093| Curent Hx Temperature in Celsius |
| 0840| Countdown Boost-Mode |
| 1| Heat state (0 = off; 1= on) |
| 0| Pump state (0 = off; 1= on) |

## Display Wiring

|Pin Display|Pin ESP32|
|--|--|
| VIN | 3.3V |
| GND| GND |
| SCL| D22 |
| SDA| D21 |

The address selection is 0x3D or 0x3C. You can recognize it by the solder bridge on the back side

![BackSideDisplay](https://github.com/belectronic/marax-monitor-mqtt/blob/main/assets/Backside.png?raw=true)

## WIFI & MQTT

By editing the credentials in [espwifi.h](https://github.com/belectronic/marax-monitor-mqtt/blob/main/lib/wifiInit/espwifi.h) and
[mqtt.h](https://github.com/belectronic/marax-monitor-mqtt/blob/main/lib/mqtt/mqtt.h) you can transmit the MaraX data to your MQTT server.

Here are the preconfigured topics:

| Topic | Payload Datatype | Description |
|--|--|--|
| marax/mode | Char | Machine-Mode |
| marax/steam/temp/current | Int | Current Steam Temperature in Celsius |
| marax/steam/temp/target | Int | Target Steam Temperature in Celsius |
| marax/hx/temp/current | Int | Curent Hx Temperature in Celsius |
| marax/heating/state | Int | Heating state |
| marax/pump/state | Int | Pump state |

## Libaries

- Wire.h (OLED)
- Adafruit_GFX.h (OLED)
- Adafruit_SSD1306.h (OLED)
- PubSubClient (MQTT)
