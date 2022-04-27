import serial
from pub import push_image, push_sensor_battery, push_sensor_hscr, push_sensor_gyro, push_sensor_piezo
from sub import 

## Open port with baud rate
ser = serial.Serial ("/dev/ttyS0", 115200)

# Exemplo {"forward": true, "backward": false, "left": false, "right": false, "stop": false, "turn": false}
def dataToByte(data: dict = {}):
  if data['forward']:
    ser.write("0x01")  
  if data['backward']:
    ser.write("0x02")  
  if data['left']:
    ser.write("0x03")  
  if data['right']:
    ser.write("0x04")  
  if data['stop']:
    ser.write("0x05")  
  if data['turn']:
    ser.write("0x06")  
    
# dataToByte(msg.payload)