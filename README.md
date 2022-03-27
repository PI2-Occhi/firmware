# Firmware Occhi Project

> The firmware from Occhi Project can perform the below features:

* Get photo of user
* Process collected image
* Get data sensors
* Send data sensors to MQTT Broker

### Capture Image

Requirements:

* Raspberry Pi 3+
* Python version >=3.7 in Rpi
* Module Cam Rpi
* Web Cam Logi 900

### Bash

Web Cam
```
fswebcam -r 1280x720 --no-banner image.jpg
```

Cam Pi
```
raspistill -o image.jpg
```

#### Install camocchi application:

```sh
python3 -m pip3 install -e .
```

#### Run application:

Command to get one photo:
```sh
camocchi -m one
```

Command to get continuos photo:
```sh
camocchi -m continuos
```
