#include "Particle.h"

class ReceiveCommands {
public:
  ReceiveCommands(int port, void perform (uint8_t)) {
    this->perform = perform;

    server = new TCPServer(port);

    server->begin();
  }

  void forwardReceived(uint8_t *data, size_t size) {
    for (size_t idx = 0; idx < size; ++idx) {
      perform(data[idx]);
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
  void (*perform) (uint8_t);
  TCPServer *server;
  TCPClient client;
};
