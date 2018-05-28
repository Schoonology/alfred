#include "Particle.h"
#include "perform-commands.cpp"

class ReceiveCommands {
public:
  ReceiveCommands(int port) {
    server = new TCPServer(port);

    server->begin();
  }

  void forwardReceived(uint8_t *data, size_t size) {
    for (size_t idx = 0; idx < size; ++idx) {
      performer.perform(data[idx]);
    }
  }

  void pullNextPage() {
    uint8_t buffer[32];
    memset(buffer, 0, 32);
    size_t bytesRead = client.read(buffer, 32);

    forwardReceived(buffer, bytesRead);
  }

  void receive() {
    while (client.available()) {
      pullNextPage();
    }

    if (!client.connected()) {
      client = server->available();
    }
  }

  ~ReceiveCommands() {
    delete server;
  }

private:
  PerformCommands performer;
  TCPServer *server;
  TCPClient client;
};
