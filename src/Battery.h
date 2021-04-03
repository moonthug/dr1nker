//
// Created by Alex Coulcher
//

#ifndef DR1NKER_BATTERY_H
#define DR1NKER_BATTERY_H

#include <Arduino.h>

class Battery {
private:
  int _pin;
public:
  Battery(int pin);

  float getPercent();
};

#endif //DR1NKER_BATTERY_H
