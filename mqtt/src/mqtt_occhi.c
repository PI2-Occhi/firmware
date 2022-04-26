#include "mqtt_occhi.h"

void initMQTT(client_mqtt_occhi *client){
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    client->pubmsg = MQTTClient_message_initializer;
    int rc;
    int ch;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
  
    // MQTT Connection parameters
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
}

int publishMessage(char* payload, client_mqtt_occhi *client) {
    // Publish message
    client->pubmsg.payload = payload;
    client->pubmsg.payloadlen = strlen(payload);
    client->pubmsg.qos = QOS;
    client->pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &client->pubmsg, &client->token);
    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, client->token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", client->token);
  
    // Disconnect
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}

void subscriberMessage(client_mqtt_occhi *client) {
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC, QOS);
    do
    {
        ch = getchar();
    } while(ch!='Q' && ch != 'q');
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}