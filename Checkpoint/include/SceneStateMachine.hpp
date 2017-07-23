#ifndef __SceneStateMachine__
#define __SceneStateMachine__

#include <vector>

class SceneStateMachine;

#include "Scenes/Scene.hpp"

class SceneStateMachine
{
public:
    SceneStateMachine() {} ;

    ~SceneStateMachine();
    
    void update();

    void render();
    
    void handleEvents();

    void firstScene();
    
    void pushScene(Scene* pScene);

    void changeScene(Scene* pScene);

    void popScene();

private:
    std::vector<Scene*> m_Scenes;
};

#endif