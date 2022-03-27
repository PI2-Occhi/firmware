from time import sleep
from picamera import PiCamera
import os
import logging
import cv2
import numpy as np

# https://github.com/Itseez/opencv/blob/master/data/haarcascades/haarcascade_frontalface_default.xml
face_cascade = cv2.CascadeClassifier(
    "/home/pi/firmware/camocchi/haarcascade_frontalface_default.xml"
)
# https://github.com/Itseez/opencv/blob/master/data/haarcascades/haarcascade_eye.xml
eye_cascade = cv2.CascadeClassifier("/home/pi/firmware/camocchi/haarcascade_eye.xml")


class Camocchi:
    def __init__(
        self,
        name: str = os.getenv("OCCHI_PATH_IMAGE", "image.png"),
        time: int = 2,
        debug: bool = False,
        module: str = "continuos",
        cam: str = "web",
    ) -> None:
        self.logger = logging.getLogger("Occhi Log |")
        self.name = name
        self.time = time
        self.debug = debug
        self.module = module
        self.cam = cam

    def run(self):
        if self.cam == "web":
            if self.module == "continuos":
                self.continuos_get_image_web()
            if self.module == "one":
                self.take_photo_web()
            if self.module == "ht":
                self.equalizeHistogram()
            if self.module == "crop":
                self.crop_image()

        if self.cam == "rpi":
            if self.module == "continuos":
                self.continuos_get_image()
            if self.module == "one":
                self.take_photo()

    """
    Continuos function
    """

    def continuos_get_image(self) -> None:
        # Create object picamera
        camera = PiCamera()

        # Connected to an instance of PiPrevewRenderer
        camera.start_preview()

        # Wait for 2 minutes
        sleep(2)

        # Continuos captura
        for filename in camera.capture_continuous(self.name):
            # turn led
            if self.debug:
                self.logger.info("Captured %s" % filename)
            sleep(self.time)  # wait 5 minutes

    """
    Take a photo function
    """

    def take_photo(self) -> None:
        # Create object picamera
        camera = PiCamera()

        # Define resolution
        camera.resolution = (1024, 768)

        # Connected to an instance of PiPrevewRenderer
        camera.start_preview()

        # Wait for 2 seconds
        sleep(self.time)

        # Capture photo
        camera.capture(self.name)

    """
    Continuos function web 
    """

    def continuos_get_image_web(self) -> None:
        # Create object VideoCapture
        cam = cv2.VideoCapture(0)

    """
    Take a photo web function
    """

    def take_photo_web(self) -> None:
        # initialize the camera
        cam = cv2.VideoCapture(0)
        ret, image = cam.read()

        # Use the cvtColor() function to grayscale the image
        gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

        # Take image
        cv2.imwrite(self.name, gray_image)
        cam.release()

    """
    Get Equalize histogram
    """

    def equalizeHistogram(self):
        img_bgr = cv2.imread(self.name)
        img_hsv = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2HSV)
        img_hsv[:, :, 2] = cv2.equalizeHist(img_hsv[:, :, 2])
        saida = cv2.cvtColor(img_hsv, cv2.COLOR_HSV2BGR)
        # concat=cv2.hconcat((img_bgr,saida))
        cv2.imwrite(self.name, saida)

    """
    Get crop image
    """

    def crop_image(self):
        img = cv2.imread(self.name)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        faces = face_cascade.detectMultiScale(gray, 1.3, 5)

        for (x, y, w, h) in faces:
            cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 2)
            roi_gray = gray[y : y + h, x : x + w]
            roi_color = img[y : y + h, x : x + w]

            eyes = eye_cascade.detectMultiScale(roi_gray)
            for (ex, ey, ew, eh) in eyes:
                crop_img = img[ey : ey + eh, ex : ex + ew]
                cv2.imwrite(self.name, eyes)
                cv2.rectangle(roi_color, (ex, ey), (ex + ew, ey + eh), (0, 255, 0), 2)
