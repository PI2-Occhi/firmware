import cv2
import sys
import os

# Create object VideoCapture
cam = cv2.VideoCapture(0)

while True:
    # initialize the camera and get photo
    ret, image = cam.read()

    file_name_image = os.getenv("OCCHI_PATH_IMAGE", "image.png")

    # Use the cvtColor() function to grayscale the image
    img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Equalize image
    if (len(sys.argv) > 1 and sys.argv[1]):
        img = cv2.equalizeHist(img)

    # Store image
    cv2.imwrite(file_name_image, img)
