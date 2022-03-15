from time import sleep
from picamera import PiCamera
import os
import logging

# Define logging
logger = logging.getLogger("Occhi Log |")

"""
Continuos function
"""


def continuos_get_image(
    name: str = os.getenv("OCCHI_PATH_IMAGE", "image.png"),
    time: int = 2,
    debug: bool = False,
) -> None:
    # Create object picamera
    camera = PiCamera()

    # Connected to an instance of PiPrevewRenderer
    camera.start_preview()

    # Wait for 2 minutes
    sleep(2)

    # Continuos captura
    for filename in camera.capture_continuous(name):
        # turn led
        if debug:
            logger.info("Captured %s" % filename)
        sleep(time)  # wait 5 minutes


"""
Take a photo function
"""


def take_photo(name: str = os.getenv("OCCHI_PATH_IMAGE", "image.png")) -> None:
    # Create object picamera
    camera = PiCamera()

    # Define resolution
    camera.resolution = (1024, 768)

    # Connected to an instance of PiPrevewRenderer
    camera.start_preview()

    # Wait for 2 seconds
    sleep(2)

    # Capture photo
    camera.capture(name)
