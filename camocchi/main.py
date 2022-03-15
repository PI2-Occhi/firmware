import click
from camocchi import Camocchi


@click.command()
@click.option("-a", "--asy", default=False, help="Definir um tempo.")
@click.option("-c", "--cont", default=False, help="Definir um tempo.")
@click.option("-t", "--time", default=2, help="Definir um tempo.")
@click.option(
    "-n", "--name", default="exmaple.png", help="Definir nome de saída da imagem."
)
@click.option("-d", "--debug", default=False, help="Atividade modo debug.")
@click.version_option()
def main(name: str, time: int, debug: bool, asy: bool, cont: bool):
    cam = Camocchi(name, time, debug, asy, cont)
    cam.run()
