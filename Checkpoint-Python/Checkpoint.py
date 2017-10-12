from Scenes import *
from Data import *
import Inputs
from sys import argv

drive = False
verbose = False
database = None
FULLSCREEN = False
input1 = Inputs.KeyBoard()

for option in argv[1:]:
    if option == "--fullscreen":
        FULLSCREEN = True
    elif option == "--gpio":
        input1 = Inputs.Gpio()
    elif option == "--drive":
        database  = None
    elif option == "--barra":
        database = DataBase("Data/datafiles")
    elif option == "--verbose":
        verbose = True
        print("Verbose mode is ON")


app = SceneManager("Competencia Robotica 2017", width=1920, height=1080, fullscreen=FULLSCREEN,
                   input_handler=input1, database=database, verbose=verbose)

if verbose:
    print("Title Scene")
app.change_scene(scene_id="TitleScreen", Scene=TitleScreen(app, "TitleScreen"), remove=False)

app.run()
