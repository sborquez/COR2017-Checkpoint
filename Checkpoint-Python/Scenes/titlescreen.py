from Scenes import load_image, Scene, ResultScreen, Chronometer


# TODO agregar algo y cambiar fondo
class TitleScreen(Scene):
    """
    Pantalla inicial
    """

    def __init__(self, manager, scene_id):
        super().__init__(manager, scene_id)
        self.background = load_image("resources/images/background1.jpg")

        manager.load_scene(Scene=Chronometer(manager, "Chrono"), scene_id="Chrono")
        manager.load_scene(Scene=ResultScreen(manager, "Results"), scene_id="Results")

    def on_update(self):
        "Actualizacion logica que se llama automaticamente desde el director."
        pass

    def on_event(self, inputs_handler):
        "Se llama cuando llega un evento especifico al bucle."
        if inputs_handler.on_press("reset"):
            self.manager.change_scene(scene_id="Chrono", remove=True)

    def on_draw(self, screen):
        "Se llama cuando se quiere dibujar la pantalla."

        # Fondo.
        screen.blit(self.background, (0, 0))
