#include "_alfred.cpp"

Alfred *myself;

void setup() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Device ID: ");
  Serial.println(System.deviceID());

  myself = new Alfred();
}

void loop() {
  myself->update();

  // We'll only update at approx. 1Hz.
  delay(1000);
}
