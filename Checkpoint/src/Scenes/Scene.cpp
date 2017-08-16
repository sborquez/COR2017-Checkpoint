#include "../../include/Scenes/Scene.hpp"

void BaseScene::update()
{
    //for (auto it = m_pObjects.begin(); it != m_pObjects.end(); ++it)
    //     it->update();
}

void BaseScene::handleEvents()
{
}

void BaseScene::render()
{
    //for (auto it = m_pObjects.begin(); it != m_pObjects.end(); ++it)
    //     it->render();
}

BaseScene::~BaseScene()
{
    SDL_Log("\tEliminando objetos de escena");
    //for (auto it = m_pObjects.begin(); it != m_pObjects.end(); ++it)
    //     delete *it;
}
