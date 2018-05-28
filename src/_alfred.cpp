#include "Particle.h"
#include "send-beacon.cpp"
#include "receive-commands.cpp"

class Alfred {
public:
  Alfred(void perform (uint8_t)) {
    beacon = new SendBeacon(7777);
    receiver = new ReceiveCommands(7778, perform);
  }

  void update() {
    beacon->send();
    receiver->receive();
  }

  ~Alfred() {
    delete beacon;
    delete receiver;
  }

private:
  SendBeacon *beacon;
  ReceiveCommands *receiver;
};
