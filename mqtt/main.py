from mqtt.lib.mqtt_occhi import MqttOcchi
import serial

# Open port with baud rate and initialization MQTT
ser = serial.Serial("/dev/ttyS0", 115200)
mqttocchi = MqttOcchi()


def dataToByte(data):
    if data and type(data) is dict:
        if "forward" in data and data["forward"]:
            ser.write("0x01")
        if "backward" in data and data["backward"]:
            ser.write("0x02")
        if "left" in data and data["left"]:
            ser.write("0x03")
        if "right" in data and data["right"]:
            ser.write("0x04")
        if "stop" in data and data["stop"]:
            ser.write("0x05")
        if "turn" in data and data["turn"]:
            ser.write("0x06")


def parseSerialToMqtt(tag: str):
    value_read = ser.read()
    if len(str(value_read)) > 1:
        if tag == "hcsr" and "hcsr" in value_read:
            # "hcsr=value;"
            value = str(value_read.decode())
            return value.split("=")[1].replace(";", "")

        if tag == "battery" and "battery" in value_read:
            # "battery=value;"
            value = str(value_read.decode())
            return value.split("=")[1].replace(";", "")

        if tag == "gyro" and "gyro" in value_read:
            # "gyro=value;"
            value = str(value_read.decode())
            return value.split("=")[1].replace(";", "")

        if tag == "piezo" and "piezo" in value_read:
            # "piezo=value;"
            value = str(value_read.decode())
            return value.split("=")[1].replace(";", "")


# Define fuction for received mensage
def on_message(client, userdata, msg):
    data = msg.payload.decode()
    dataToByte(data)

    mqttocchi.pub_image()
    mqttocchi.pub_sensor_battery(parseSerialToMqtt("battery"))
    mqttocchi.pub_sensor_hscr(parseSerialToMqtt("hcsr"))
    mqttocchi.pub_sensor_gyro(parseSerialToMqtt("gyro"))
    mqttocchi.pub_sensor_piezo(parseSerialToMqtt("piezo"))

    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))


def on_publish(client, userdata, mid):
    print("mid: " + str(mid))


# Connect mqtt
mqttocchi.connect_mqtt(on_publish, on_message)

# Loop mqtt
mqttocchi.loop_forever()
