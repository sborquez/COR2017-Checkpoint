#include "../include/SceneStateMachine.hpp"    
#include "../include/Scenes/StartScene.hpp"

#include <SDL2/SDL.h>

// Carga la primera escena. Esta siempre se llamara StartScene y debe ser definida.
void SceneStateMachine::firstScene() {
    pushScene(new StartScene("Inicial"));
}

// Cambia a una nueva escena sin desechar la anterior
void SceneStateMachine::pushScene(Scene *pScene)
{
    SDL_Log("Cambiando a escena: %s", pScene->getSceneID().c_str());
    m_Scenes.push_back(pScene);
    pScene->onEnter();
}

// Elimina la escena actual
void SceneStateMachine::popScene()
{
    if (!m_Scenes.empty() && m_Scenes.back()->onExit()) {
        SDL_Log("Eliminando escena: %s", m_Scenes.back()->getSceneID().c_str());
        delete m_Scenes.back();
        m_Scenes.pop_back();
    }
}

// Cambia la escena actual por una nueva, la anterior se elimina
void SceneStateMachine::changeScene(Scene *pScene)
{
    // Si hay escena actual debe eliminarse
    if (!m_Scenes.empty()) {

        // Si es la misma escena, no hacemos nada
        if(m_Scenes.back()->getSceneID() == pScene->getSceneID()) {
            return;
        }

        // Si hay escena, finalizarla y eliminarla
        if (m_Scenes.back()->onExit()) {
            SDL_Log("Eliminando escena: %s", m_Scenes.back()->getSceneID().c_str());
            delete m_Scenes.back();
            m_Scenes.pop_back();
        // no se pudo eliminar la escena           
        } else {
            SDL_Log("No se pudo eliminar escena: %s", m_Scenes.back()->getSceneID().c_str());
            return;
        }
    }
    // Agregamos la nueva escena
    pushScene(pScene);
}

// Actualizar la escena actual
void SceneStateMachine::update()
{
    if (!m_Scenes.empty())
        m_Scenes.back()->update();
}

// Renderiza la escena actual
void SceneStateMachine::render()
{
    if (!m_Scenes.empty())
        m_Scenes.back()->render();
}

// Manupular eventos
void SceneStateMachine::handleEvents()
{
    if (!m_Scenes.empty())
        m_Scenes.back()->handleEvents();
}


// Vaciar memoria de las escenas
SceneStateMachine::~SceneStateMachine()
{
    while (!m_Scenes.empty()) {
        delete m_Scenes.back();
        m_Scenes.pop_back();
    }
}