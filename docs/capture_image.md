# Capture Image

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

## Install opencv in Rpi
```sh
sudo apt update
sudo apt install python3-opencv
```

## Run code otimization
```sh
python3 camocchi/continuos_simples.py
```

#### Install camocchi application:

Initialization venv:
```sh
python3 -m pip3 install virtualenv
source venv/bin/activate
```

Install application:
```sh
python3 -m pip3 install -e .
sudo apt-get install libatlas-base-dev
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