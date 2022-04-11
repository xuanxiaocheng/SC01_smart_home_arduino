#include <WiFi.h>
#include <PubSubClient.h>
#include <UTILS.H>
#include <iostream>
#include <ArduinoJson.h>
#include "APLink.h"
#include "FanCtrl.h"
#include <Preferences.h>
#include "SwitchCtrl.h"

int fanControl;
const char *ssid = "HiWiFi_3D2436";
const char *password = "209209209";
const char *mqttServer = "47.106.219.80";
const int mqttPort = 1883;
const char *mqttUser = "user";
const char *mqttPassword = "123456";
WiFiClient espClient;
PubSubClient client(espClient);

void MQTT_init()
{
    WiFi.begin(ssid, password);
    if (WiFi.status() != WL_CONNECTED)
    {
        APlink();
        while (WiFi.status() != WL_CONNECTED)
        {
            Preferences prefs;
            prefs.begin("mynamespace");
            Serial.printf(prefs.getString("ssid", "555").c_str());
            Serial.printf(prefs.getString("password", "555").c_str());
            WiFi.begin(prefs.getString("ssid", "555").c_str(), prefs.getString("password", "555").c_str());
            delay(5000);
        }
        WiFi.enableAP(false);
    }
    Serial.println("Connected to the WiFi network");
    client.setServer(mqttServer, mqttPort); //连接MQTT
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP8266Client", mqttUser, mqttPassword))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

// MQTT服务持续运行
void Sub_loop()
{
    client.loop();
}

//获取Mac值，发布订阅
void MQTT_send(char *data, int mac)
{
    const char *msg = data;
    client.publish(tochar(mac), msg);
}

void receiveCallback(char *topic, byte *payload, unsigned int length)
{
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    JsonObject obj = doc.as<JsonObject>();
    fanControl = obj["fan"];
    int isSmart = obj["fanAutoCtrl"];
    int switchStatus = obj["switchStatus"];
    int wantTemperature = obj["wantTemperature"];
    Serial.println(switchStatus);
    SwitchCtrl(switchStatus);
    smartFanSwitch(wantTemperature, isSmart, fanControl);
}

void Sub_init()
{
    char subID[100];
    int chipid = ESP.getEfuseMac();
    itoa(chipid, subID, 10);
    strcat(subID, "sub");
    client.subscribe(subID, 0); //接收订阅
    client.setCallback(receiveCallback);
}

int getFanStatus(void)
{
    return fanControl;
}
