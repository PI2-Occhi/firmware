import cv2

# Create object VideoCapture
cam = cv2.VideoCapture(0)

while True:
    # initialize the camera and get photo
    ret, image = cam.read()

    # Use the cvtColor() function to grayscale the image
    img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    # Equalize image
    # equ = cv2.equalizeHist(img)

    # Store image
    cv2.imwrite("image.png", img)
