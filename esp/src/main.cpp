#include "DHTCtrl.h"
#include "MQTTCtrl.h"
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "cJSON.h"
#include "PubData.h"
#include "FanCtrl.h"
#include "SwitchCtrl.h"

void setup()
{
  Serial.begin(9600);
  MQTT_init();
  FanInit();
  DHT_Init();
  Sub_init();
  SwitchInit();
}

void loop()
{
  Sub_loop();
  Pub_loop();
  delay(1000);  //发布与订阅间隔一秒
}
