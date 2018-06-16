#include "Quantum.h"
#include "Roomba.h"

Quantum alfred(perform);

void perform(uint8_t command) {
  Serial.printf("Received: %d\n", command);

  switch (command) {
    case 1:
      Serial.println("ON command received.");
      Roomba::wake();
      Roomba::start();
      delay(400);
      break;
    case 2:
      Serial.println("CLEAN command received.");
      Roomba::clean();
      break;
    case 3:
      Serial.println("DOCK command received.");
      Roomba::dock();
      break;
    case 4:
      Serial.println("SLEEP command received.");
      Roomba::sleep();
      delay(100);
      break;
    case 255:
      Serial.println("RESET command received.");
      Roomba::_reset();
      System.enterSafeMode();
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

  Roomba::begin();
  alfred.begin();
}

void loop() {
}
