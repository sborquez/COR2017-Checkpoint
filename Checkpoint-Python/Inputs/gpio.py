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
            self.mode = GPIO.BCM if int(self.config["GPIO"]["mode"]) == 0 else GPIO.BOARD
            self.botones = {boton: int(pin) for boton, pin in self.config["GPIO"].items() if
                            boton != "mode" and int(pin) != 0}

            # Setup
            print("Using GPIO mode")
            print("\tSetting mode %s" % "BCM" if self.mode == GPIO.BCM else "BOARD")
            GPIO.setmode(self.mode)

            print("\tSetting OUTPUTS pins:")
            for k,v in self.botones.items():
                print("\t\t%s:%d" % (k, v))

            GPIO.setup(list(self.botones.values()), GPIO.IN)

            # Estados previos
            self.previos = {}
            self.actual = {boton: GPIO.input(pin) for boton, pin in self.botones.items()}

        def is_down(self, boton):
            return self.actual[boton] == GPIO.HIGH

        def is_up(self, boton):
            return self.actual[boton] == GPIO.LOW

        def on_press(self, boton):
            return self.actual[boton] == GPIO.HIGH and self.previos[boton] == GPIO.LOW

        def on_release(self, boton):
            return self.actual[boton] == GPIO.LOW and self.previos[boton] == GPIO.HIGH

        def update(self):
            self.previos = dict(self.actual)
            self.actual = {boton: GPIO.input(pin) for boton, pin in self.botones.items()}
