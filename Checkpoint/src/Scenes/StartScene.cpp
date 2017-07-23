#include "../../include/Scenes/StartScene.hpp"
#include "../../include/Scenes/ChronoScene.hpp"

void StartScene::update() 
{
    BaseScene::update();
}

void StartScene::handleEvents()
{
    BaseScene::handleEvents();
    m_keystate = SDL_GetKeyboardState(NULL);
    
    if (m_keystate and m_keystate[SDL_SCANCODE_R]){
        TheApplication->getSceneStateMachine()->changeScene(new ChronoScene("Chrono"));
    }
}

void StartScene::render()
{
    TheApplication->getTextureManager()->drawBackground("banner", 0, 0, 0, 0, true);
}

bool StartScene::onEnter()
{
    TheApplication->getTextureManager()->load("../data/assets/banner2.png","banner");
    return BaseScene::onEnter();
}

bool StartScene::onExit()
{
    TheApplication->getTextureManager()->unload("banner");
    return BaseScene::onExit();
}
