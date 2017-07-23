#ifndef __ResultScene__
#define __ResultScene__ 

#include "Scene.hpp"

class ResultScene : public BaseScene
{
public:
    ResultScene(const std::string ID) : BaseScene(ID) {};

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