# ESP OCCHI

> Controller low level for get data sensors and control actuators of project Occhi.

## Sensors

* HCSR
* MPU6530
* Piezo
* Level batery

## Actuators

* Buzzer 
* Brushless Motor
* Led

## Protocols

* SPI
* I2C

## Comandos ESP-IDF

1. Set enviroments of espressif idf
```sh
cd $HOME
. $HOME/esp/esp-idf/export.sh
```

2. Define home folder of project and initialization with example
```sh
cd ~/$HOME_PROJECT
cp -r $IDF_PATH/examples/get-started/hello_world .
```

3. Set develop board and settings configurations
```sh
idf.py set-target esp32
idf.py menuconfig
```

4. Build of project
```sh
idf.py build
```

5. Upload project in develop board
```sh
idf.py -p PORT [-b BAUD] flash
idf.py -p PORT flash monitor
```

6. See screen monitor
```sh
screen /dev/ttyUSB0 115200
```

## Run project

1. Install depencys
```sh
screen /dev/ttyUSB0 115200
```

2. Build projects
```sh
screen /dev/ttyUSB0 115200
```

3. Run projects
```sh
screen /dev/ttyUSB0 115200
```
