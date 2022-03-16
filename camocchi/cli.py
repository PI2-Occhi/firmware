import click
from camocchi import Camocchi
import os

@click.command()
@click.option("-t", "--time", default=2, help="Definir um tempo.")
@click.option(
    "-n", "--name", default=os.getenv("OCCHI_PATH_IMAGE", "image.png"), help="Definir nome de saída da imagem."
)
@click.option("-d", "--debug", default=False, help="Atividade modo debug.")
@click.version_option()
def main(name: str, time: int, debug: bool):
    camocchi = Camocchi(name, time, debug)
    camocchi.run()
