#include "../../include/Scenes/ChronoScene.hpp"
#include "../../include/Scenes/ResultScene.hpp"

void ResultScene::update() 
{
    BaseScene::update();
}

void ResultScene::handleEvents()
{
    BaseScene::handleEvents();
    m_keystate = SDL_GetKeyboardState(NULL);
    
    //Test
    if (m_keystate and m_keystate[SDL_SCANCODE_R]){
        TheApplication->getSceneStateMachine()->changeScene(new ChronoScene("Chrono"));
    }
}

void ResultScene::render()
{
    TheApplication->getTextureManager()->drawBackground("Velocidad-bases", 0, 0, 0, 0, true);
}

bool ResultScene::onEnter()
{
    TheApplication->getTextureManager()->load("../../data/assets/Velocidad-bases.jpg","Velocidad-bases");
    return BaseScene::onEnter();
}

bool ResultScene::onExit()
{
    TheApplication->getTextureManager()->unload("Velocidad-bases");
    return BaseScene::onExit();
}