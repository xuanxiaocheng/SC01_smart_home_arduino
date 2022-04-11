#include "DHTCtrl.h"
#include "MQTTCtrl.h"
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "cJSON.h"

int chipid = ESP.getEfuseMac();                                   //获取ESP本机Mac地址

void Pub_loop()
{
    float *p = DHT_GetData();                                     //获取DHT传感器数据
    char temperature[100];                                        //定义温度变量
    float temperatureFloat = *(p + 0);                            //获取温度实时数据
    sprintf(temperature, "%2.1f", temperatureFloat);              //小数点处理
    char humidity[100];                                           //定义湿度变量
    float humidityFloat = *(p + 1);                               //获取湿度实时数据
    sprintf(humidity, "%2.0f", humidityFloat);                    //小数点处理
    char fanstatus[100];                                          //定义风扇PWM变量
    int fanIOStatus = getFanStatus();                             //获取风扇PWM变量
    sprintf(fanstatus, "%d", fanIOStatus);                        //小数点处理
    cJSON *pRoot = cJSON_CreateObject();                          // 创建JSON根部结构体
    cJSON *pValue = cJSON_CreateObject();                         // 创建JSON子叶结构体
    cJSON_AddStringToObject(pRoot, "temperature", temperature);   // 添加字符串类型数据到根部结构体
    cJSON_AddStringToObject(pRoot, "humidity", humidity);         // 添加字符串类型数据到根部结构体
    cJSON_AddStringToObject(pRoot, "fanStatus", fanstatus);       // 添加字符串类型数据到根部结构体
    /*   cJSON_AddItemToObject(pRoot, "value", pValue); 添加字符串类型数据到子叶结构体 */
    char *out = cJSON_Print(pRoot);                               //转换除JSON格式
    Serial.println(out);
    MQTT_send(out, chipid);                                       //MQTT发布订阅
}