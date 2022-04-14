from time import sleep
from picamera import PiCamera
import os
import logging
import cv2
import numpy as np

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
        
        while True:
          # initialize the camera and get photo
        	ret, image = cam.read()
         
          # Use the cvtColor() function to grayscale the image
          gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
          
          # Equalize image
          saida = self.equalizeHistogram(gray_image)      
          
          # Store image    
          cv2.imwrite(self.name, saida)
          cam.release()
          
          # Time between take photo
        	sleep(self.time)

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

    def equalizeHistogram(self, img_hsv):
        img_hsv[:, :, 2] = cv2.equalizeHist(img_hsv[:, :, 2])
        saida = cv2.cvtColor(img_hsv, cv2.COLOR_HSV2BGR)
        
        return saida
