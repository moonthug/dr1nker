//
// Created by Alex Coulcher.
//

#include "WaterSourceLevel.h"

WaterSourceLevel::WaterSourceLevel(int pin) {
  _pin = pin;
}

float WaterSourceLevel::getPercent() {
  return map(analogRead(_pin), 0.0f, 4095.0f, 0, 100);
}