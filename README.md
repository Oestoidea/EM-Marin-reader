# EM-Marin reader

EM-Marin reader (EM4100 and EM4102) on Arduino, RDM6300 and OLED (125kHz) for intercom systems.

## Equipment

1. Arduino Nano v3.0 or Mini Pro (with 3.3V)
2. RDM6300 ([fritzing part](./fritzing-scheme/RDM6300.fzpz)) with external antenna
3. OLED 0.91" 128×32 I2C SSD1306

## RDM6300 Module

When the module is connected to the COM-port and RFID tag brought closer to the antenna the port immediately transferred its identifier.

![Arduino_Nano_RDM6300_oled_photo](./pics/Arduino_Nano_RDM6300_oled_2.png)

## Display

Connect OLED and RDM6300 to Arduino Nano as shown on the picture.

![Arduino_Nano_RDM6300_oled_scheme](./fritzing-scheme/Arduino_Nano_RDM6300_oled_bb.png)

On display you can see 10-digit RFID-number and its ASCII code.

## Arduino Nano

Install [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) and [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) libraries in Arduino IDE. This scanner based on [Test sketch for RFID module RDM6300 125 kHz](http://forum.arduino.ua/viewtopic.php?id=345) (Russian) written by Yojeh (Йожэг).

## Connection Map

| Arduino Nano | RDM6300       |
| ------------ | ------------- |
| D10          | Tx            |
| 5V           | 5V            |
| GND          | GND           |

| Arduino Nano | I2C OLED      |
| ------------ | ------------- |
| A5 (19)      | SCK           |
| A4 (18)      | SDA           |
| 3V3          | VCC           |
| GND          | GND           |

And also connect ANT1 and ANT2 to external antenna (without polarity).

## Implementation

Prototype is assembled in a clear acrylic case for Raspberry Pi, but can be built more compactly.

![Arduino_Nano_RDM6300_oled_photo](./pics/Arduino_Nano_RDM6300_oled.png)