# include librarys for send menssage on MQTT
from typing import Callable
import paho.mqtt.client as paho
import json
import os


class MqttOcchi:
    def __init__(
        self, 
    ) -> None:
        self.client = paho.Client()

        with open(
            os.getcwd() + "/lib/config.json", "r"
        ) as config_file:  # Read archive .json of configuration
            data = config_file.read()

        self.config = json.loads(data)

    # connect mqtt
    def connect_mqtt(self, on_publish: Callable, on_message: Callable):
        # Create e configuration client mqtt
        self.client.username_pw_set(self.config["username"], self.config["password"])

        self.client.on_publish = on_publish
        self.client.on_message = on_message
        self.client.enable_bridge_mode()

        self.client.connect(
            self.config["host"], self.config["port"], self.config["keepalive"]
        )
        
        # Cliente mqtt
        self.sub_motor()
    
    def loop_forever(self):
        self.client.loop_forever()
        

    # Send menssage
    def pub_image(self):
        self.client.publish(
            self.config["topic_path_image"],
            str(os.getenv("OCCHI_PATH_IMAGE", "/tmp/image.png")),
            qos=self.config["qos"],
        )

    # Send menssage battery
    def pub_sensor_battery(self, value: float = 0.0):
        self.client.publish(
            self.config["topic_sensor_battery"], str(value), qos=self.config["qos"]
        )

    # Send menssage hscr
    def pub_sensor_hscr(self, value: bool = False):
        self.client.publish(
            self.config["topic_sensor_hcsr"], str(value), qos=self.config["qos"]
        )

    # Send menssage gyro
    def pub_sensor_gyro(self, value: bool = False):
        self.client.publish(
            self.config["topic_sensor_gyro"], str(value), qos=self.config["qos"]
        )

    # Send menssage piezo
    def pub_sensor_piezo(self, value: bool = False):
        self.client.publish(
            self.config["topic_sensor_piezo"], str(value), qos=self.config["qos"]
        )

    def sub_motor(self):
        self.client.subscribe(self.config["topic_motors"], qos=1)
