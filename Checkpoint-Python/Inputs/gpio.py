from Inputs import InputHandler

try:
    import RPi.GPIO as GPIO


except RuntimeError:
    from Inputs import KeyBoard
    print("Gpio no disponible")


    class Gpio(KeyBoard):
        def __init__(self):
            super().__init__()

else:
    class Gpio(InputHandler):
        def __init__(self):
            super().__init__()

            # Cargar configuracion
            self.mode = GPIO.BCM if self.config["GPIO"]["mode"] == 0 else GPIO.BOARD
            self.botones = {boton: int(pin) for boton, pin in self.config["GPIO"].items() if
                            boton != "mode" and int(pin) != 0}

            # Setup
            GPIO.setmode(self.mode)
            GPIO.setup(self.botones.values(), GPIO.IN)

            # Estados previos
            self.previos = {}
            self.actual = {boton: GPIO.input(pin) for boton, pin in self.botones.items()}

        def is_down(self, boton):
            return GPIO.input(self.botones[boton]) == GPIO.LOW

        def is_up(self, boton):
            return GPIO.input(self.botones[boton]) == GPIO.HIGH

        def on_press(self, boton):
            return GPIO.input(self.botones[boton]) == GPIO.HIGH and self.previos[boton] == GPIO.LOW

        def on_release(self, boton):
            return GPIO.input(self.botones[boton]) == GPIO.LOW and self.previos[boton] == GPIO.HIGH

        def update(self):
            self.previos = dict(self.actual)
            self.actual = {boton: GPIO.input(pin) for boton, pin in self.botones.items()}
