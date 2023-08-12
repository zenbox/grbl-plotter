#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
byte incomingByte[1];

void setup(void) {
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  u8g2.begin();
}

void loop(void) {
  if (Serial.available() > 0) {
    // int serialMessage = Serial.parseInt();
    String serialMessage = Serial.readString();
Serial.println(serialMessage);
char* msg = serialMessage.c_str();
oled(msg);

  }
}
void oled(char msg) {
  u8g2.clearBuffer();                  // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
  u8g2.drawStr(0, 10, msg);            // write something to the internal memory
  u8g2.sendBuffer();                   // transfer internal memory to the display
  delay(1000);
}
