#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <SoftwareSerial.h>
#define STX 2
#define ETX 3

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

SoftwareSerial softSerial(10, 11); // recommended pins for RX on Mega: 10, 11, 12...
int rx_counter;
byte rx_data[14], rx_data_temp[14]; // 1+10+2+1

void setup() {
  rx_counter = 0; // init counter
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Ready...");
  display.display();
  delay(1000);
  Serial.println("Ready...");
  softSerial.begin(9600);
  rx_data_temp;
}

void loop() {
  if (softSerial.available() > 0) {
    rx_data[rx_counter] = softSerial.read();
    if (rx_counter == 0 && rx_data[0] != STX) {
      Serial.println("Out of sync!"); // do not increment rx_counter
    } else {
      rx_counter++;
    }
    if (rx_counter >= 14) {
      rx_counter = 0; // reset counter
      if (rx_data[0] == STX && rx_data[13] == ETX) { // packet starts with STX and ends with ETX
        byte calc_checksum = 0;
        for (int i = 0; i < 6; i++) { // data with checksum
          calc_checksum ^= ascii_char_to_num(rx_data[i*2+1]) * 16 + ascii_char_to_num(rx_data[i*2+2]);
        }
        if (!equal()) {
          if (calc_checksum == 0) {
            Serial.print("ID: ");
            display.clearDisplay();
            display.setCursor(0,0);
            for (int i = 1; i <= 10; i++) {
              Serial.write(rx_data[i]);
              display.print((char)rx_data[i]);
            }
            display.println("  ASCII:");
            for (int i = 1; i <= 10; i++) {
              display.print(rx_data[i]);
            }
            display.display();
            Serial.println();
            memcpy(rx_data_temp, rx_data, 14);
          } else {
            Serial.println("Checksum ERROR!");
          }
        }
      } else {
          Serial.println("Incorrect packet!");
      }
    } 
  }
}

// convert a single hex character to its byte value using ASCII table (see https://ru.wikipedia.org/wiki/ASCII)
byte ascii_char_to_num(byte a) {
  a -= '0'; // 0..9
  if (a > 9) a -= 7; // A..F
  return a;
}

bool equal(void) {
  for (int i = 1; i <= 10; i++)
    if (rx_data[i] != rx_data_temp[i])
      return false;
  return true;
}
