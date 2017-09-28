import pygame
from configparser import ConfigParser
from Inputs.inputbox import ask


pygame.init()


class InputHandler:
    def __init__(self):
        self.config = ConfigParser()
        self.config.read("Inputs/inputs.ini")

    def is_down(self, boton):
        raise NotImplementedError

    def is_up(self, boton):
        raise NotImplementedError

    def on_press(self, boton):
        raise NotImplementedError

    def on_release(self, boton):
        raise NotImplementedError

    def update(self):
        raise NotImplementedError

    def text_input(self, validate=lambda s: (s, True), show=""):
        """Espera a una entrada de texto, retorna el input y si es valido. """
        text = ask(show)
        return tuple(validate(text))
