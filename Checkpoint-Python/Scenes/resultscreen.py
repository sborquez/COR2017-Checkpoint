from Scenes import load_image, Scene
import AppObjects


#TODO agregar lista, quizas
class ResultScreen(Scene):
    """
    Pantalla de resultado
    """

    def __init__(self, manager, scene_id):
        super().__init__(manager, scene_id)
        #TODO Cambiar imagen de fondo
        self.background = load_image("resources/images/background1.jpg")

        #TODO cambiar fuente
        self.time_text = AppObjects.Text(size=80)

    def on_update(self):
        "Actualizacion logica que se llama automaticamente desde el manager."
        self.time_text.set_text(self.manager.globals["time_mark"][1])

    def on_event(self, inputs_handler):
        "Se llama cuando llega un evento especifico al bucle."
        if inputs_handler.on_press("reset"):
            self.manager.change_scene(scene_id="Chrono", remove=False)

    def on_draw(self, screen):
        "Se llama cuando se quiere dibujar la pantalla."

        # Fondo.
        screen.blit(self.background, (0, 0))

        # Tiempo
        # TODO posicionar correctamente
        self.time_text.render(screen, self.manager.globals["width"]/3, self.manager.globals["heigth"]/2)
