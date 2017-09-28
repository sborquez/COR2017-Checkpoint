from Inputs import InputHandler
try:
    import RPi.GPIO as GPIO

except RuntimeError:
    print("Gpio no disponible")
    class GPIO(InputHandler):
        def __init__(self):
            super().__init__()
            self.botones = {boton: int(pin) for boton, pin in self.config["GPIO"].items()}

        def is_down(self, boton):
            raise NotImplementedError

        def is_up(self, boton):
            raise NotImplementedError

        def on_press(self, boton):
            raise NotImplementedError

        def on_release(self, boton):
            raise NotImplementedError

        def update(self):
            raise NotImplementedError

else:
    class GPIO(InputHandler):
        def __init__(self):
            super().__init__()
            self.botones = {boton: int(pin) for boton, pin in self.config["GPIO"].items()}

        def is_down(self, boton):
            raise NotImplementedError

        def is_up(self, boton):
            raise NotImplementedError

        def on_press(self, boton):
            raise NotImplementedError

        def on_release(self, boton):
            raise NotImplementedError

        def update(self):
            raise NotImplementedError