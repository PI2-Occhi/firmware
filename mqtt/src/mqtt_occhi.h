// Author: Matheus Gois Vieira
// Project: Occhi

#ifndef FIRMWARE_MQTT_CLIENT_H
#define FIRMWARE_MQTT_CLIENT_H

#include <MQTTClient.h>

#define ADDRESS             "tcp://10.0.0.100:1883"
#define CLIENTID            "occhi"
#define TOPIC_CAM           "matheus"
#define TOPIC_SENSORS       "matheus"
#define TOPIC_SENSORS       "matheus"
#define PAYLOAD             "123"
#define QOS                 0
#define TIMEOUT             10000L

typedef struct 
{
  MQTTClient client;
  MQTTClient_message pubmsg;
  MQTTClient_deliveryToken token;
} client_mqtt_occhi;




void initMQTT(client_mqtt_occhi *client);
void publishMessage(char* payload, client_mqtt_occhi *client);
void subscriberMessage(client_mqtt_occhi *client);

#endif //FIRMWARE_MQTT_CLIENT_H
