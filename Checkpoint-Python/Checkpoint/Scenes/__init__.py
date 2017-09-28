import pygame

pygame.init()
pygame.mouse.set_visible(False)

def load_image(filename, transparent=False):
    try:
        image = pygame.image.load(filename)
    except pygame.error as message:
        raise SystemExit(message)
    image = image.convert()
    if transparent:
        color = image.get_at((0, 0))
        image.set_colorkey(color, pygame.RLEACCEL)
    return image


from Scenes.scene import Scene
from Scenes.scenemanager import SceneManager
from Scenes.resultscreen import ResultScreen
from Scenes.chronometer import Chronometer
from Scenes.titlescreen import TitleScreen

