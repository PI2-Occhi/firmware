# Code: pub.py
# Author: Matheus Gois Vieira
# Project Occhi

# include librarys for send menssage on MQTT
import paho.mqtt.client as paho
import time
import json
import os

# Read archive .json of configuration
with open("config.json", "r") as myfile:
    data = myfile.read()

# Parse to dict
config = json.loads(data)

# Define function for publish
def on_publish(client, userdata, mid):
    print("mid: " + str(mid))


# Create e configuration client mqtt
client = paho.Client()
# client.username_pw_set(config['username'], config['password'])
client.on_publish = on_publish
client.connect(config["host"], config["port"], config["keepalive"])
client.loop_start()

# Send menssage
def push_image():
    client.publish(
        config["topic_path_image"],
        str(os.getenv("OCCHI_PATH_IMAGE")),
        qos=config["qos"],
    )


# Send menssage battery
def push_sensor_battery(value: float = 0.0):
    client.publish(config["topic_sensor_battery"], str(value), qos=config["qos"])


# Send menssage hscr
def push_sensor_hscr(value: bool = False):
    client.publish(config["topic_sensor_hcsr"], str(value), qos=config["qos"])


# Send menssage gyro
def push_sensor_gyro(value: bool = False):
    client.publish(config["topic_sensor_gyro"], str(value), qos=config["qos"])


# Send menssage piezo
def push_sensor_piezo(value: bool = False):
    client.publish(config["topic_sensor_piezo"], str(value), qos=config["qos"])
