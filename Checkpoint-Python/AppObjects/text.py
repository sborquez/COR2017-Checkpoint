import pygame

pygame.font.init()


class Text:
    def __init__(self, font="resources/fonts/PressStart2P.ttf", size=10, color=(255, 255, 255)):
        self.text = ""
        self.size = size
        self._font = font
        self.color = color
        self.font = pygame.font.Font(font, self.size)

    def set_text(self, text, size=-1, color=(255, 255, 255), bold=False, italic=False, underline=False):
        """ Determinar cual sera el texto a mostrar y su formato """

        if size > 0:
            self.font = pygame.font.Font(self._font, size)
            self.size = size

        self.color = color
        self.font.set_bold(bold)
        self.font.set_italic(italic)
        self.font.set_underline(underline)

        self.text = text

    def render(self, screen, x=0, y=0, centerx=(False,0), centery=(False,0)):
        size = self.font.size(self.text)
        if centerx[0]:
            x = centerx[1]//2 - size[0]//2
        if centery[0]:
            y  = centery[1]//2 - size[1]//2
        text = self.font.render(self.text, 1, self.color)
        screen.blit(text, (x, y))
