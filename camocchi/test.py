from time import sleep
from picamera import PiCamera
import cv2

# Create object picamera
camera = PiCamera()

# Define resolution
camera.resolution = (1024, 768)

# Connected to an instance of PiPrevewRenderer
camera.start_preview()

# Wait for 2 seconds
sleep(2)

# Capture photo
camera.capture("example_rpi.png")


cam = cv2.VideoCapture(0)
ret, image = cam.read()

# Use the cvtColor() function to grayscale the image
gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
cv2.imwrite("example_web.png", gray_image)
cam.release()
