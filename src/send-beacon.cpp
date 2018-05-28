#include "Particle.h"

class SendBeacon {
public:
  SendBeacon(int port) {
    this->port = port;

    socket.begin(port);

    String deviceID = System.deviceID();
    length = deviceID.length();
    data = new uint8_t[length + 1];
    deviceID.getBytes(data, length + 1);

    address = WiFi.localIP();
    address[3] = 255;
  }

  void send() {
    socket.beginPacket(address, port);
    socket.write(data, length);
    socket.endPacket();
  }

  ~SendBeacon() {
    delete data;
  }

private:
  int port;
  UDP socket;
  IPAddress address;
  uint8_t *data;
  size_t length;
};
