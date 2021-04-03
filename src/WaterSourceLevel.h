//
// Created by Alex Coulcher.
//

#ifndef DR1NKER_WATERSOURCELEVEL_H
#define DR1NKER_WATERSOURCELEVEL_H

#include <Arduino.h>

class WaterSourceLevel {
private:
  int _pin;
public:
  WaterSourceLevel(int pin);

  float getPercent();
};


#endif //DR1NKER_WATERSOURCELEVEL_H
