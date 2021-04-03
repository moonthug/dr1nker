//
// Created by Alex Coulcher.
//

#include "Log.h"

Log::Log(PubSubClient *mqttClient, String topic) {
  _mqttClient = mqttClient;
  _topic = topic;
}

void Log::logBoot(int &bootCount) {
  time_t now;
  time(&now);

  String output;

  StaticJsonDocument<200> doc;
  doc["event"] = "boot";
  doc["time"] = now;
  JsonObject data = doc.createNestedObject("data");
  data["count"] = bootCount;
  serializeJson(doc, output);

  Serial.print("log: ");
  Serial.println(output);

  _mqttClient->publish(String(_topic + "/boot").c_str(), output.c_str());
  _mqttClient->publish(String(_topic + "/boot-count").c_str(), String(bootCount).c_str());
}

void Log::logTopup(int &waterLevel, int &waterSourceLevel, int &previousWaterLevel,
                   int &previousSourceLevel, int &pumpDuration) {
  time_t now;
  time(&now);

  String output;

  StaticJsonDocument<200> doc;
  doc["event"] = "topup";
  doc["time"] = now;
  JsonObject data = doc.createNestedObject("data");
  data["prevWaterLevel"] = previousWaterLevel;
  data["prevWaterSourceLevel"] = previousSourceLevel;
  data["waterLevel"] = waterLevel;
  data["waterSourceLevel"] = waterSourceLevel;
  data["pumpDuration"] = pumpDuration;

  serializeJson(doc, output);

  Serial.print("log: ");
  Serial.println(output);

  _mqttClient->publish(String(_topic + "/topup").c_str(), output.c_str());
  _mqttClient->publish(String(_topic + "/prev-water-level").c_str(), String(previousWaterLevel).c_str());
  _mqttClient->publish(String(_topic + "/topup/prev-water-source-level").c_str(), String(previousWaterLevel).c_str());
  _mqttClient->publish(String(_topic + "/topup/water-level").c_str(), String(waterLevel).c_str());
  _mqttClient->publish(String(_topic + "/topup/water-source-level").c_str(), String(waterSourceLevel).c_str());
  _mqttClient->publish(String(_topic + "/topup/pump-duration").c_str(), String(pumpDuration).c_str());
}