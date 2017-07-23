#include "../../include/Scenes/ChronoScene.hpp"
#include "../../include/Scenes/ResultScene.hpp"

void ChronoScene::update() 
{
    BaseScene::update();
}

void ChronoScene::handleEvents()
{
    BaseScene::handleEvents();
    
    //Test
    m_keystate = SDL_GetKeyboardState(NULL);
    if (m_keystate and m_keystate[SDL_SCANCODE_R])
        TheApplication->getSceneStateMachine()->changeScene(new ResultScene("Resultado"));
}

void ChronoScene::render()
{
    TheApplication->getTextureManager()->drawBackground("logo", 0, 0, 0, 0, true);
}

bool ChronoScene::onEnter()
{
    TheApplication->getTextureManager()->load("../../data/assets/logo.png","logo");
    return BaseScene::onEnter();
}

bool ChronoScene::onExit()
{
    TheApplication->getTextureManager()->unload("logo");
    return BaseScene::onExit();
}