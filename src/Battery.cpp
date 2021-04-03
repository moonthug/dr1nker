//
// Created by Alex Coulcher
//

#include "Battery.h"

Battery::Battery(int pin) {
  _pin = pin;
}

float Battery::getPercent() {
  return map(analogRead(_pin), 0.0f, 4095.0f, 0, 100);
}