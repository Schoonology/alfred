#include "Particle.h"

class SendBeacon {
public:
  SendBeacon(int port) {
    this->port = port;

    socket.begin(port);

    address = WiFi.localIP();
    address[3] = 255;

    compileBeaconData();
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
  uint8_t digitToByte(char digit) {
    if (digit >= 'a') {
      return digit - 'a' + 10;
    } else {
      return digit - '0';
    }
  }

  // Writes each pair of `hex` digits as a single uint8 to `buf`,
  // up to `len` bytes in size. Sadly, this seems to be the only
  // way to get a Photon's deviceID as a string of bytes.
  void getBytesForHexString(String hex, uint8_t *buf, size_t len) {
    for (
      size_t hexIndex = 0, bufIndex = 0;
      hexIndex < hex.length() && bufIndex < len;
      hexIndex += 2, bufIndex += 1
    ) {
      buf[bufIndex] = (digitToByte(hex.charAt(hexIndex)) << 4)
        + digitToByte(hex.charAt(hexIndex + 1));
    }
  }

  void compileBeaconData() {
    String deviceID = System.deviceID();

    length = deviceID.length() / 2;
    data = new uint8_t[length];

    getBytesForHexString(deviceID, data, length);
  }

  int port;
  UDP socket;
  IPAddress address;
  uint8_t *data;
  size_t length;
};
