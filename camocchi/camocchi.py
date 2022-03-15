from time import sleep
from picamera import PiCamera
import os
import logging


class Camocchi:
    def __init__(
        self,
        name: str = os.getenv("OCCHI_PATH_IMAGE", "image.png"),
        time: int = 2,
        debug: bool = False,
        cont: bool = False,
        asy: bool = False,
    ) -> None:
        self.logger = logging.getLogger("Occhi Log |")
        self.name = name
        self.time = time
        self.debug = debug
        self.cont = cont
        self.asy = asy
        pass

    def run(self):

        self.cont and self.continuos_get_image()
        self.asy and self.take_photo()

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
