import click
from frame import continuos_get_image, take_photo

@click.command()
@click.option('--time', default=2, help='Number of greetings.')
@click.option('--name', prompt='camocchi',
            help='The person to greet.')