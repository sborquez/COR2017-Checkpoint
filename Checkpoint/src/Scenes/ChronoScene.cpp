#include "../../include/Scenes/ChronoScene.hpp"
#include "../../include/Scenes/ResultScene.hpp"

void ChronoScene::update()
{
    BaseScene::update();
    /*if (chronometer.isrunning)
      chronometer.update() set time actual, calculate dif*/
}

void ChronoScene::handleEvents()
{
    if (TheInputHandler->onPress("B_RESET"))
        TheSceneManager->changeScene(new ResultScene("Result"));
    if (TheInputHandler->get_gpio()) {
      if (TheInputHandler->onRising("B_RESET"))
         TheSceneManager->changeScene(new ResultScene("Result"));
      if (TheInputHandler->isPinOn("B_START"))
         std::cout << "start gpio " << std::endl;
    }

    /*TODO
    if (chronometer.isrunning){
       if (isPinOff("running"))
          time = chronometer.stop() set time Result, isrunning=false
                                    and return Result
          chronometer.reset() set times to 0
          ResultScene* resultscene= new ResultScene("Result")
          resultscene->time = time
          TheSceneManager->pushScene(resultscene);

    } else {
        if (onRising("running"))
          chronometer.start() //set time inicio y running=true
    }
    */

}

void ChronoScene::render()
{
    TheTextureManager->drawBackground("logo", 0, 0, 0, 0, true);
}

bool ChronoScene::onEnter()
{
    TheTextureManager->load("assets/logo.png","logo");
    return BaseScene::onEnter();
}

bool ChronoScene::onExit()
{
    TheTextureManager->unload("logo");
    return BaseScene::onExit();
}
