#ifndef __StartScene__
#define __StartScene__ 

#include "Scene.hpp"

class StartScene : public BaseScene
{
public:
    StartScene(const std::string ID) : BaseScene(ID) {};

    void update();

    void handleEvents();

    void render();
    
    bool onExit();
    
    bool onEnter();

private:
    //TEST
    const Uint8* m_keystate;

};

#endif