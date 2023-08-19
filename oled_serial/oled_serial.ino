#include <Arduino.h>
#include <U8g2lib.h>
#include <SoftwareSerial.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
byte incomingByte[1];

const byte rxPin = 2;
const byte txPin = 3;

char textLine[30];
int currentLine = 0;
int countLines = 0;

// Set up a new SoftwareSerial object
SoftwareSerial cncSerial(rxPin, txPin);

void setup(void) {
  Serial.begin(115200);
  cncSerial.begin(115200);

  pinMode(13, OUTPUT);

  u8g2.begin();
}

void loop(void) {
  if (Serial.available() > 0) {
    /* @desc Serial input, i.e. via web serial API. 
     *       Incoming g-code lines from a browser.
     */
    String serialMessage = Serial.readString();
    countLines++;

    /* @desc Display output
     *       Control output on oled display  
     *       fill 6 lines, then clear
     */
    if (currentLine > 51) {
      u8g2.clearBuffer();
      currentLine = 0;
    }
    currentLine += 10;
    char* msg = serialMessage.c_str();
    u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
    u8g2.drawStr(0, currentLine, msg);
    u8g2.sendBuffer();  // transfer internal memory to the display
    delay(10);

    /* @desc Soft serial output 
     *       Send g-code lines to control the cnc shield.
     */
    cncSerial.println(serialMessage);
  }
}
