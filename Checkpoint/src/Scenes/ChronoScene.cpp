#include "../../include/Scenes/ChronoScene.hpp"
#include "../../include/Scenes/ResultScene.hpp"

void ChronoScene::update() 
{
    BaseScene::update();
}

void ChronoScene::handleEvents()
{
    if (TheInputHandler->onPress(B_RESET))
        TheSceneManager->changeScene(new ResultScene("Result"));
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