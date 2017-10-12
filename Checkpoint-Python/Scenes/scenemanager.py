import pygame
from pygame.locals import *
import sys

class SceneManager:
    """
    Ventana principal.

    Mantiene en funcionamiento el juego, se
    encarga de actualizar, dibuja y propagar eventos.

    Además, manipula el cambio de escenas (Scene).

    """

    pygame.init()

    def __init__(self, title: str, width: int, height: int, input_handler: object,
                    database: object, fullscreen: bool = False, verbose: bool = False):
        # Crear una nueva ventana
        flags = pygame.RESIZABLE
        if fullscreen:
            flags |= pygame.FULLSCREEN

        self.screen = pygame.display.set_mode((width, height), flags)

        pygame.display.set_caption(title)

        # Almacenar escenas
        self.scenes = {}
        self.running_scene = "None"
        self.scene = None

        # Juego corriendo
        self.running = False

        # Clock de la app
        self.clock = pygame.time.Clock()

        # Elegir un medio de input
        self.input_handler = input_handler

        # Conectar con la Base de Datos
        self.DB = database
        if database is not None and verbose:
            self.DB.mostrar()

        # Variables globales entre escenas
        self.globals = {
             "width": width,
            "heigth": height,
             "title": title,
             "verbose": verbose
        }

    def run(self):
        """Pone en funcionamiento el bucle principal de la aplicacion."""

        if self.running_scene is not None:
            self.running = True

        while self.running:
            #time = self.clock.tick(60)

            # Eventos de Salida
            events = []
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.stop_running()
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        self.stop_running()
                    elif event.key == pygame.K_f:
                        pygame.display.toggle_fullscreen()

            # detecta eventos
            self.input_handler.update()
            self.scene.on_event(self.input_handler)

            # actualiza la escena
            self.scene.on_update()

            # dibuja la pantalla
            self.scene.on_draw(self.screen)

            # actualiza la superficie
            pygame.display.flip()

    def load_scene(self, Scene, scene_id):
        """Carga una escena al diccionario de escenas."""
        self.scenes[scene_id] = Scene

    def delete_scene(self, scene_id):
        """Elimina una escena"""
        if self.running_scene != scene_id:
            del self.scenes[scene_id]

    def change_scene(self, scene_id, Scene=None, remove=True):
        """ Cambia de escena """
        actual = self.running_scene

        # En caso de querer cargar una nueva escena
        if Scene is not None:
            self.load_scene(Scene, scene_id)
            self.running_scene = scene_id

        # En caso de querer cargar una escena previamente cargada
        elif scene_id in self.scenes.keys():
            self.running_scene = scene_id

        # Si se desea eliminar la escena anterior
        if remove:
            self.delete_scene(actual)

        # Cambiamos la escena corriendo
        self.scene = self.scenes[self.running_scene]

    def stop_running(self):
        self.running = False

    def quit(self):
        pygame.quit()

    def set_input(self, inputhandler):
        self.input_handler = inputhandler
