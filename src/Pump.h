//
// Created by Alex Coulcher.
//

#ifndef DR1NKER_PUMP_H
#define DR1NKER_PUMP_H

#include <Arduino.h>

class Pump {
private:
  int _pin;
  unsigned long _pumpStartMillis;
  unsigned long _lastRunDuration;

public:
  Pump(int pin);

  void run();
  void run(int durationMs);

  void stop();

  bool runLongerThan(unsigned long value);

  unsigned long getLastRunDuration();
};

#endif //DR1NKER_PUMP_H
