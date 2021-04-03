//
// Created by Alex Coulcher.
//

#include "WaterLevel.h"

WaterLevel::WaterLevel(int pin) {
  _pin = pin;
}

float WaterLevel::getPercent() {
  return map(analogRead(_pin), 0.0f, 4095, 0, 100);
}