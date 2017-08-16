#include "../../include/Scenes/ChronoScene.hpp"
#include "../../include/Scenes/ResultScene.hpp"

void ResultScene::update()
{
    BaseScene::update();
}

void ResultScene::handleEvents()
{
    if (TheInputHandler->onPress("B_RESET"))
        TheSceneManager->changeScene(new ChronoScene("Chronometer"));
        //TODO
        //TheSceneManager->popScene();
    if (TheInputHandler->get_gpio()) {
      if (TheInputHandler->onRising("B_RESET"))
          //TODO
          //TheSceneManager->popScene();
          TheSceneManager->changeScene(new ChronoScene("Chronometer"));
      if (TheInputHandler->isPinOn("B_QUIT"))
          std::cout << "quit gpio " << std::endl;
    }
}

void ResultScene::render()
{
    TheTextureManager->drawBackground("Velocidad-bases", 0, 0, 0, 0, true);
    //rederizar tiempo result
}

bool ResultScene::onEnter()
{
    TheTextureManager->load("assets/Velocidad-bases.jpg","Velocidad-bases");
    return BaseScene::onEnter();
}

bool ResultScene::onExit()
{
    TheTextureManager->unload("Velocidad-bases");
    return BaseScene::onExit();
}
