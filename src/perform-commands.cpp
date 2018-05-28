#include "Particle.h"

class PerformCommands {
public:
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
};
