#include <M5Stack.h>
#include "qrcode.h"
//https://github.com/ricmoo/qrcode

void setup() {
  Serial.begin(115200);
  M5.begin();
  // Lcd display
  M5.Lcd.setTextColor(TFT_BLACK, TFT_WHITE);
  M5.Lcd.fillScreen(TFT_WHITE);
  // Start time
  uint32_t dt = millis();
  // Create the QR code
  QRCode qrcode;
  uint8_t version = 6;
  uint8_t qrcodeData[qrcode_getBufferSize(version)];
  qrcode_initText(&qrcode, qrcodeData, version, 0, "Kongduino|HONG KONG|http://kongduino.wordpress.com|KONGDUINO@GMAIL.COM");
  // Delta time
  dt = millis() - dt;
  Serial.print(F("QR Code Generation Time: "));
  Serial.print(dt);
  Serial.print("\n");
  // Top quiet zone
  Serial.print("\n\n\n\n");
  uint8_t thickness = 220 / qrcode.size;
  uint16_t lineLength = qrcode.size * thickness;
  uint8_t xOffset = (320 - (lineLength)) / 2;
  uint8_t yOffset = (240 - (lineLength)) / 2;
  for (uint8_t y = 0; y < qrcode.size; y++) {
    // Left quiet zone
    Serial.print("        ");
    // Each horizontal module
    for (uint8_t x = 0; x < qrcode.size; x++) {
      // Print each module (UTF-8 \u2588 is a solid block)
      bool q = qrcode_getModule(&qrcode, x, y);
      Serial.print(q ? "\u2588\u2588" : "  ");
      if (q) {
        M5.Lcd.fillRect(x * thickness + xOffset, y * thickness + yOffset, thickness, thickness, TFT_BLACK);
      }
    }
    Serial.write('\n');
  }
  // Bottom quiet zone
  Serial.print("\n\n\n\n");
}

void loop() {
}
