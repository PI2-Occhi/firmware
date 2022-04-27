# Code: send.py
# Author: Matheus Gois Vieira
# Project occhi

# include librarys for send menssage on MQTT
import paho.mqtt.client as paho
import json

# Read archive .json of configuration
with open("config.json", "r") as myfile:
    data = myfile.read()

config = json.loads(data)

# Define fuction for received mensage
def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_message(client, userdata, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))

# Create client mqtt
client = paho.Client()
client.username_pw_set(config["username"], config["password"])
client.on_subscribe = on_subscribe
client.on_message = on_message
client.connect(config["host"], config["port"], config["keepalive"])
client.subscribe(config["topic_motors"], qos=1)

# client.loop_forever()  # wait for message
