//
// Created by Alex Coulcher.
//

#ifndef DR1NKER_WATERLEVEL_H
#define DR1NKER_WATERLEVEL_H

#include <Arduino.h>

class WaterLevel {
private:
  int _pin;
public:
  WaterLevel(int pin);

  float getPercent();
};


#endif //DR1NKER_WATERLEVEL_H
