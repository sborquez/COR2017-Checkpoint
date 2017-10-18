from Scenes import load_image, Scene
import AppObjects
from time import strftime as date
from time import gmtime


#TODO agregar lista, quizas
class ResultScreen(Scene):
    """
    Pantalla de resultado
    """

    def __init__(self, manager, scene_id):
        super().__init__(manager, scene_id)
        #TODO Cambiar imagen de fondo
        self.background = load_image("resources/images/background3.png")

        self.state = "exit"
        self.logfile = "Data/Log/%s.log" % date("%m-%d_%H:%M")
        with open(self.logfile, "a") as log:
            log.write("[log]%s;%s;%s\n" % ("nombre", "formateado", "real"))

        #TODO cambiar fuente
        self.time_text = AppObjects.Text(size=200, font="resources/fonts/TitilliumWeb-Regular.ttf", color=(230,230,230))
        self.time_1 =  AppObjects.Text(size=110, font="resources/fonts/TitilliumWeb-Regular.ttf", color=(230,230,230))
        self.time_2 = AppObjects.Text(size=110, font="resources/fonts/TitilliumWeb-Regular.ttf", color=(230,230,230))
        self.time_3 = AppObjects.Text(size=110, font="resources/fonts/TitilliumWeb-Regular.ttf", color=(230,230,230))

        self.runner_text = AppObjects.Text(size=120, font="resources/fonts/data-latin.ttf", color=(245,245,245))

    def on_update(self):
        "Actualizacion logica que se llama automaticamente desde el manager."
        #self.time_text.set_text(self.manager.globals["time_mark"][1], color=(230,230,230))
        if self.state == "exit":
            self.tiempo_seg = self.manager.globals["time_mark"][0]
            self.tiempo_form = self.manager.globals["time_mark"][1]

            # Se esta usando la base de datos
            if self.manager.globals["db"]:
                self.equipo = self.manager.globals["equipo_actual"]
                self.runner_text.set_text(self.equipo["nombre"], color=(245,245,245))

                if self.equipo["i1"] == "":
                    self.equipo["i1"] = (self.tiempo_seg, self.tiempo_form)
                elif self.equipo["i2"] == "":
                    self.equipo["i2"] = (self.tiempo_seg, self.tiempo_form)
                elif self.equipo["i3"] == "":
                    self.equipo["i3"] = (self.tiempo_seg, self.tiempo_form)

                if self.equipo["final"] is None:
                    self.equipo["final"] = [0.0,""]
                self.equipo["final"][0] +=  self.tiempo_seg
                seconds = self.equipo["final"][0]
                mili = str(seconds % 1)[2:5]
                mili = "000" if mili == "0" else mili
                self.equipo["final"][1] =  date("%M:%S:", gmtime(seconds)) + mili

                with open(self.logfile, "a") as log:
                    log.write("[%s]%s;%s;%f\n" % (date("%H:%M:%S  %z"),self.equipo["nombre"], self.tiempo_form, self.tiempo_seg))
                print(self.equipo, self.tiempo_form, self.tiempo_seg)

            else:
                print(self.tiempo_seg, self.tiempo_form)

            self.state = "entry"

        elif self.state == "entry":
            if self.equipo["final"][0] >= 180:
                self.time_text.set_text(self.equipo["final"][1], color=(230,30,30))
            else:
                self.time_text.set_text(self.equipo["final"][1], color=(230,230,230))
            self.time_1.set_text(self.equipo["i1"][1] if type(self.equipo["i1"]) == tuple else "---", color=(230,230,230))
            self.time_2.set_text(self.equipo["i2"][1] if type(self.equipo["i2"]) == tuple else "---", color=(230,230,230))
            self.time_3.set_text(self.equipo["i3"][1] if type(self.equipo["i3"]) == tuple else "---", color=(230,230,230))


    def on_event(self, inputs_handler):
        "Se llama cuando llega un evento especifico al bucle."
        if inputs_handler.on_press("reset") and self.state=="entry":
            self.manager.change_scene(scene_id="Chrono", remove=False)
            self.state = "exit"
        #if inputs_handler.on_press("exit"):
            #self.manager.stop_running()

    def on_draw(self, screen):
        "Se llama cuando se quiere dibujar la pantalla."

        # Fondo.
        screen.blit(self.background, (0, 0))

        # Tiempo
        # TODO posicionar correctamente
        #TODO Agregar dibujo del cronometro
        #self.chronometer.draw(screen, 200, 300)
        self.runner_text.render(screen, y=380, centerx=(True, 1920))

        # Tiempo
        #TODO ajustar a nuevo fondo
        self.time_text.render(screen, x=900, y=550)
        self.time_1.render(screen, centerx=(True, 1920//3), y=520)
        self.time_2.render(screen, centerx=(True, 1920//3), y=620)
        self.time_3.render(screen, centerx=(True, 1920//3), y=720)
