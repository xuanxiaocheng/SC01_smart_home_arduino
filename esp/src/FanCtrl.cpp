#include <Arduino.h>
#include "DHTCtrl.h"
#include "MQTTCtrl.h"

int freq = 2000;    // 频率
int channel = 0;    // 通道
int resolution = 8; // 分辨率
const int led = 26; // 串口

//串口与PWM通道初始化
void FanInit()
{
    ledcSetup(channel, freq, resolution); // 设置通道
    ledcAttachPin(led, channel);          // 将通道与对应的引脚连接
}

//串口PWM调节
void setGrade(int num)
{
    ledcWrite(channel, num);
}

//风扇智能调节
void smartFanSwitch(int wantTemperature, int isSmart, int fanControl)
{
    if (isSmart == 1)
    {
        if (getTemperature() < wantTemperature)
        {
            ledcWrite(channel, 255); // 输出PWM
        }
    }
    else
    {
        setGrade(fanControl);
    }
}
