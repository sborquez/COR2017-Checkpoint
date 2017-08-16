#include "../../include/Scenes/StartScene.hpp"
#include "../../include/Scenes/ChronoScene.hpp"

#include <iostream>

void StartScene::update()
{
    BaseScene::update();
}

void StartScene::handleEvents()
{
    if (TheInputHandler->onPress("B_RESET"))
        TheSceneManager->changeScene(new ChronoScene("Chronometer"));

    if (TheInputHandler->get_gpio()) {
      if (TheInputHandler->onRising("B_RESET"))
          TheSceneManager->changeScene(new ChronoScene("Chronometer"));
    }
}

void StartScene::render()
{
    TheTextureManager->drawBackground("banner", 0, 0, 0, 0, true);
}

bool StartScene::onEnter()
{
    TheTextureManager->load("assets/banner2.png","banner");
    return BaseScene::onEnter();
}

bool StartScene::onExit()
{
    TheTextureManager->unload("banner");
    return BaseScene::onExit();
}
