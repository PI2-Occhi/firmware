import click
from camocchi import Camocchi
import os


@click.command()
@click.option("-m", "--module", default="continuos", help="Modulo executado")
@click.option("-c", "--cam", default="web", help="Selecionar camera")
@click.option("-t", "--time", default=2, help="Definir um tempo.")
@click.option("-d", "--dohistogram", default=True, help="Permitir histograma.")
@click.option(
    "-n",
    "--name",
    default=os.getenv("OCCHI_PATH_IMAGE", "image.png"),
    help="Definir nome de saída da imagem.",
)
@click.option("-d", "--debug", default=False, help="Ativar modo debug.")
@click.version_option()
def main(name: str, time: int, debug: bool, module: str, cam: str, dohistogram: bool):
    camocchi = Camocchi(name, time, debug, module, cam, dohistogram)
    camocchi.run()
