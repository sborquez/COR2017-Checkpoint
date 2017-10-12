from pygame.gfxdraw import arc, filled_circle
from time import strftime, gmtime, time


class Chronometer:
    def __init__(self):
        self.init_time = 0.0000
        self.running = False
        self.mark_time = 0.0000

    def start(self):
        if not self.running:
            self.running = True
            self.init_time = time()

    def stop(self):
        if self.running:
            self.mark_time = time() - self.init_time
            self.running = False

    def reset(self):
        if self.running:
            self.init_time = time()
        else:
            self.mark_time = 0.0000

    def get_time(self):
        if self.running:
            return time() - self.init_time
        return self.mark_time

    def get_format_time(self):
        seconds = self.get_time()
        mili = str(seconds % 1)[2:5]
        mili = "000" if mili == "0" else mili
        return strftime("%M:%S:", gmtime(seconds)) + mili

    def draw(self, screen, x, y):
        arc(screen, x, y, 100, -90, int((360 * self.get_time()) % 360) - 90,(255, 255, 255))
