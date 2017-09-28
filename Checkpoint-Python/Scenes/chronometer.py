from Scenes import load_image, Scene
import AppObjects


class Chronometer(Scene):
    """
    Pantalla del cronometro
    """

    def __init__(self, manager, scene_id):
        super().__init__(manager, scene_id)

        #TODO cambiar fondo
        self.background = load_image("resources/images/background2.jpg")
        self.time_text = AppObjects.Text(size=100)

        """
        Estados:
         - 'StandBy' : chronometro detenido en 0
         - 'Running' : chronometro contando
         - 'Finish'  : chronometro detenido en tiempo de vuelta
        """
        self.state = "StandBy"
        self.chronometer = AppObjects.Chronometer()

        manager.globals["time_mark"] = 0.0

    def on_update(self):
        "Actualizacion logica que se llama automaticamente desde el director."
        format_time = self.chronometer.get_format_time()
        self.time_text.set_text(format_time)

    def on_event(self, inputs_handler):
        "Se llama cuando llega un evento especifico al bucle."
        if self.state == "StandBy":
            self.chronometer.reset()
            if inputs_handler.on_press("start"):
                self.chronometer.start()
                self.state = "Running"

        elif self.state == "Running":
            if inputs_handler.on_press("reset"):
                print("invalid")
                self.state = "StandBy"
                self.chronometer.stop()
                self.chronometer.reset()

            elif inputs_handler.is_up("start"):
                print("finish")
                self.state = "Finish"
                self.chronometer.stop()

        else:
            self.manager.change_scene(scene_id="Results", remove=False)
            self.manager.globals["time_mark"] = (self.chronometer.get_time(), self.chronometer.get_format_time())
            self.state = "StandBy"

    def on_draw(self, screen):
        "Se llama cuando se quiere dibujar la pantalla."

        # Fondo.
        screen.blit(self.background, (0, 0))

        #TODO Agregar dibujo del cronometro
        #self.chronometer.draw(screen, 200, 300)

        # Tiempo
        #TODO ajustar a nuevo fondo
        self.time_text.render(screen)

