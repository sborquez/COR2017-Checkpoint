from Scenes import *
import Inputs
from sys import argv

drive = False
FULLSCREEN = False
input1 = Inputs.KeyBoard()

for option in argv[1:]:
    if option == "--fullscreen":
        FULLSCREEN = True
    elif option == "--gpio":
        input1 = Inputs.GPIO()
    elif option == "--drive":
        drive = True

app = SceneManager("Competencia Robotica 2017", width=1280, height=720, fullscreen=FULLSCREEN, input_handler=input1)

app.change_scene(scene_id="TitleScreen", Scene=TitleScreen(app, "TitleScreen"), remove=False)

app.run()

app.quit()
