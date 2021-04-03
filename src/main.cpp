#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "time.h"

#include "config.h"

#include "Log.h"
#include "Battery.h"
#include "Pump.h"
#include "WaterLevel.h"
#include "WaterSourceLevel.h"

#define AWAKE_LED_PIN 25
#define PUMP_RELAY_PIN 32
#define BATTERY_LEVEL_PIN 33
#define WATER_SOURCE_LEVEL_PIN 34
#define WATER_LEVEL_PIN 35

#define uS_TO_S 1000000  /* μs to seconds */
#define TIME_TO_SLEEP  60 /* 60 Seconds */
//#define TIME_TO_SLEEP  60 * 60 * 6 /* 6 Hours */

// state
bool isSleeping                 = false;

WiFiClient wiFiClient;
PubSubClient mqttClient(wiFiClient);

Log logger(&mqttClient, mqttTopic);
Battery battery(BATTERY_LEVEL_PIN);
Pump pump(PUMP_RELAY_PIN);
WaterLevel waterLevel(WATER_LEVEL_PIN);
WaterSourceLevel waterSourceLevel(WATER_SOURCE_LEVEL_PIN);

RTC_DATA_ATTR int bootCount = 0;

void setup() {
  pinMode(AWAKE_LED_PIN, OUTPUT);
  digitalWrite(AWAKE_LED_PIN, HIGH);

  Serial.begin(115200);
  while (!Serial) {};

  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  WiFi.begin(ssid, password);
  WiFi.setHostname("dr1nker");

  Serial.println("main: Connect to wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("main: waiting for connection...");
  }
  Serial.println("main: Wifi connected!");

  // mqtt
  Serial.println("main: Connect to MQTT...");
  mqttClient.setServer(mqttServerAddress, 1883);
  while (!mqttClient.connected()) {
    // Attempt to connect
    if (mqttClient.connect("ESP8266Client")) {
      Serial.println("main: MQTT Connected");
    } else {
      Serial.print("main: MQTT failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // @TODO
      delay(5000);
    }
  }

  // Setup Time server
  Serial.println("main: Fetch Time");
  configTime(0, 0, ntpServer);
  setenv("TZ", timezoneInfo, 1);
  tzset();

  logger.logBoot(bootCount);
}

void loop() {
  if (isSleeping) return;

  mqttClient.loop();

  Serial.print("Battery: ");
  Serial.print(battery.getPercent());
  Serial.println("%");

  int waterLevelValue = waterLevel.getPercent();
  int waterSourceLevelValue = waterSourceLevel.getPercent();

  Serial.print("Water Level: ");
  Serial.print(waterLevelValue);
  Serial.println("%");

  Serial.print("Water Source Level: ");
  Serial.print(waterSourceLevelValue);
  Serial.println("%");

  // Check Levels
  if (waterLevelValue < 10) {
    Serial.println("Run pump. Water level lower than 10%");
    pump.run();

    while (waterLevelValue <= 10 && !pump.runLongerThan(maxPumpTime)) {
      delay(10);
    }
    Serial.println("Stop Pump!");
    pump.stop();

    int currentWaterLevel = waterLevel.getPercent();
    int currentSourceLevel = waterSourceLevel.getPercent();

    int pumpDuration = pump.getLastRunDuration();
    logger.logTopup(currentWaterLevel, currentSourceLevel, waterLevelValue, waterSourceLevelValue, pumpDuration);
  }

  // Wait for mqtt
  delay(1000);

  // Sleep!
  Serial.print("main: Sleeping for " + String(TIME_TO_SLEEP) + " seconds");
  esp_sleep_enable_timer_wakeup( TIME_TO_SLEEP * uS_TO_S);
  Serial.flush();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  isSleeping = true;
  esp_deep_sleep_start();
}