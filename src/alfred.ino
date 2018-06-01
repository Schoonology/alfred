#include "Quantum.h"

Quantum alfred(perform);

void perform(uint8_t command) {
  switch (command) {
    case 0:
      Serial.println("NULL command received.");
      break;
    case 1:
      Serial.println("ON command received.");
      break;
    case 255:
      Serial.println("RESET command received.");
      break;
  }
}

void setup() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Device ID: ");
  Serial.println(System.deviceID());

  alfred.begin();
}

void loop() {
}
