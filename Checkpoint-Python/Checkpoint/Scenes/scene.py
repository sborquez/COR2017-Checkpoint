class Scene:
    """
    Representa un escena abstracta del videojuego.

    Una escena es una parte visible del juego, como una pantalla
    de presentacion o menu de opciones. Tiene que crear un objeto
    derivado de esta clase para crear una escena utilizable.
    """

    def __init__(self, manager, scene_id):
        self.manager = manager
        self.id = scene_id

    def on_update(self):
        "Actualizacion logica que se llama automaticamente desde el director."
        raise NotImplementedError

    def on_event(self, inputs_handler):
        "Se llama cuando llega un evento especifico al bucle."
        raise NotImplementedError

    def on_draw(self, screen):
        "Se llama cuando se quiere dibujar la pantalla."
        raise NotImplementedError