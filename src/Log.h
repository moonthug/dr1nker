//
// Created by Alex Coulcher.
//

#ifndef DR1NKER_LOG_H
#define DR1NKER_LOG_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#include "time.h"

class Log {
private:
  PubSubClient * _mqttClient;
  String _topic;
  tm _timeinfo;
public:
  Log(PubSubClient * mqttClient, String topic);
  void logBoot(int &bootCount);
  void logTopup(int &waterLevel, int &waterSourceLevel, int &previousWaterLevel, int &previousSourceLevel, int &pumpDuration);
};

#endif //DR1NKER_LOG_H
