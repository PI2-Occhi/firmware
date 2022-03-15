from time import sleep
from picamera import PiCamera
import sys


# Create object picamera
camera = PiCamera()

# Define resolution
camera.resolution = (1024, 768)

# Connected to an instance of PiPrevewRenderer
camera.start_preview()

# Wait for 2 seconds
sleep(2)

# Capture photo
camera.capture("example.png")
