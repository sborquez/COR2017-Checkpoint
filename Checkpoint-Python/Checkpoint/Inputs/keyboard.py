from Inputs import *
import pygame


class KeyBoard(InputHandler):
    def __init__(self):
        super().__init__()
        self.botones = {boton: int(key) for boton, key in self.config["KEYBOARD"].items()}

        pressed = pygame.key.get_pressed()
        self.actual = {boton: pressed[index] for boton, index in self.botones.items()}

    def is_down(self, boton):
        return self.actual.get(boton, False)

    def is_up(self, boton):
        return not self.actual.get(boton, False)

    def on_press(self, boton):
        return self.actual.get(boton, False) and not self.previous.get(boton, False)

    def on_release(self, boton):
        return not self.actual.get(boton, False) and self.previous.get(boton, False)

    def update(self):
        # Guardar estado previo
        self.previous = dict(self.actual)

        # Cargar un nuevo estado
        pressed = pygame.key.get_pressed()
        self.actual = {boton: bool(pressed[index]) for boton, index in self.botones.items()}
