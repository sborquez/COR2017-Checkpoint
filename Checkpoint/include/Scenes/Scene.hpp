#ifndef __Scene__
#define __Scene__

#include <string>
#include <iostream>
#include <vector>

class Scene;
class BaseScene;

#include "../Application.hpp"
//#include "GameObject.hpp"

class Scene
{
public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handleEvents() = 0;
    virtual bool onExit() = 0;
    virtual bool onEnter() = 0;

    virtual std::string getSceneID() const = 0;

    ~Scene() {};

protected:
    Scene(const std::string ID) { };
    std::string sceneID;
};

class BaseScene : public Scene
{
public:
    BaseScene(const std::string ID) : Scene(ID) { sceneID = ID; }
    /*BaseScene(std::string id, std::vector<GameObject*> a_pObjects)
        : sceneID(id),
            m_pObjects(a_pObjects)
    {
    }*/

    ~BaseScene();

    virtual void update();

    virtual void handleEvents();

    virtual void render();

    virtual bool onExit() {
        SDL_Log(" Chao, fui la escena %s", sceneID.c_str());
        return true;
    }

    virtual bool onEnter() {
        SDL_Log(" Hola, soy la escena %s", sceneID.c_str());
        return true;
    }

    inline std::string getSceneID() const { return sceneID; }

protected:
    //std::vector<GameObject*> m_pObjects;
    std::string sceneID;
};

#endif
