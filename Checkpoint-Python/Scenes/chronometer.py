from Scenes import load_image, Scene
import AppObjects


class Chronometer(Scene):
    """
    Pantalla del cronometro
    """

    def __init__(self, manager, scene_id):
        super().__init__(manager, scene_id)

        self.background = load_image("resources/images/background2.png")
        self.time_text = AppObjects.Text(size=280, font="resources/fonts/TitilliumWeb-Regular.ttf", color=(230,230,230))
        self.runner_text = AppObjects.Text(size=120, font="resources/fonts/data-latin.ttf", color=(245,245,245))

        """
        Estados:
         - 'Aux'     : Nula. Sirve para renderizar un frame
         - 'Reading' : Esperando a ingresar ID
         - 'StandBy' : chronometro detenido en 0
         - 'Running' : chronometro contando
         - 'Finish'  : chronometro detenido en tiempo de vuelta
        """
        self.state = "Aux"
        self.chronometer = AppObjects.Chronometer()
        self.manager.globals["equipo_actual"] = None
        manager.globals["time_mark"] = (0.0, "")

    def on_update(self):
        "Actualizacion logica que se llama automaticamente desde el director."
        format_time = self.chronometer.get_format_time()
        self.time_text.set_text(format_time, color=(230,230,230))


    def validator(self, text):
        equipo_actual, err = self.manager.DB.get_tiempo_by_member(text)
        if err is None:
            self.manager.globals["equipo_actual"] = equipo_actual
            equipo_nombre = equipo_actual["nombre"]
            return equipo_nombre, True
        else:
            self.manager.globals["equipo_actual"] = None
            return "", False

    def on_event(self, inputs_handler):
        "Se llama cuando llega un evento especifico al bucle."
        if self.state == "Aux":
            self.state = "Reading"
            if self.manager.globals["verbose"]:
                print("\tReading state")
            if self.manager.DB is not None:
                self.runner_text.set_text("Equipo", color=(245,245,245))
            else:
                self.runner_text.set_text("")

        elif self.state == "Reading":
            if self.manager.DB is not None:
                print("\tEsperando input",end=" ")
                text, valid = inputs_handler.text_input(show="", validate=self.validator)
                print(text)
            else:
                text, valid = "", True

            if valid:
                self.runner_text.set_text(text, color=(245,245,245))
                print("\tValid input %s" % text)
                self.state = "StandBy"
            else:
                print("\tInvalid input")
                self.runner_text.set_text("No encontrado: " + text, color=(245,245,245))
                self.state = "Aux"

        elif self.state == "StandBy":
            self.chronometer.reset()
            if inputs_handler.on_press("start"):
                self.chronometer.start()
                self.state = "Running"

            elif inputs_handler.on_press("reset"):
                self.state = "Aux"

        elif self.state == "Running":
            if inputs_handler.on_press("reset"):
                self.state = "StandBy"
                self.chronometer.stop()
                self.chronometer.reset()

            elif inputs_handler.is_up("start"):
                self.state = "Finish"
                self.chronometer.stop()

        else: #state finish
            self.manager.change_scene(scene_id="Results", remove=False)
            self.manager.globals["time_mark"] = (self.chronometer.get_time(), self.chronometer.get_format_time())
            self.state = "StandBy"

    def on_draw(self, screen):
        "Se llama cuando se quiere dibujar la pantalla."

        # Fondo.
        screen.blit(self.background, (0, 0))

        #TODO Agregar dibujo del cronometro
        #self.chronometer.draw(screen, 200, 300)
        self.runner_text.render(screen, y=380, centerx=(True, 1920))

        # Tiempo
        #TODO ajustar a nuevo fondo
        self.time_text.render(screen, y=500, centerx=(True, 1920))
