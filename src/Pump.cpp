//
// Created by Alex Coulcher.
//

#include "Pump.h"

Pump::Pump(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void Pump::run() {
  return run(5);
}

void Pump::run(int durationMs) {
  _pumpStartMillis = millis();
  digitalWrite(_pin, HIGH);
}

void Pump::stop() {
  _lastRunDuration = millis() - _pumpStartMillis;
  digitalWrite(_pin, LOW);
}

bool Pump::runLongerThan(unsigned long value) {
  return value < millis() - _pumpStartMillis;
}

unsigned long Pump::getLastRunDuration() {
  return _lastRunDuration;
}