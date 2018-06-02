#include "Particle.h"
#include "Roomba.h"

#define BRC_PIN     D0
#define BAUD_RATE   115200

void Roomba::begin() {
  pinMode(BRC_PIN, OUTPUT);
  Serial1.begin(BAUD_RATE);
  sleep();
}

void Roomba::send(unsigned char byte) {
  Serial1.write(byte);
}

void Roomba::wake() {
  digitalWrite(BRC_PIN, HIGH);
  delay(100);
  digitalWrite(BRC_PIN, LOW);
  delay(100);
  digitalWrite(BRC_PIN, HIGH);
  delay(100);
  digitalWrite(BRC_PIN, LOW);
}

void Roomba::sleep() {
  send(133);
}

void Roomba::_reset() {
  send(7);
}

void Roomba::start() {
  send(128);
}

void Roomba::stop() {
  send(173);
}

void Roomba::clean() {
  send(135);
}

void Roomba::dock() {
  send(143);
}
