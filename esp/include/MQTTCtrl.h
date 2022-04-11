#ifndef __MQTTCtrl_H__
#define __MQTTCtrl_H__

void MQTT_init(void);
void Sub_loop(void);
void MQTT_send(char *, int);
void Sub_init();
int getFanStatus(void);
#endif
