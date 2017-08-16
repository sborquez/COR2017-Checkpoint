#ifndef __ChronoScene__
#define __ChronoScene__

#include "Scene.hpp"

class ChronoScene : public BaseScene
{
public:
    ChronoScene(const std::string ID) : BaseScene(ID) {};

    void update();

    void handleEvents();

    void render();

    bool onExit();

    bool onEnter();

private:
  //objeto chronometro
  // objeto text display(tiempo chronometer)
};

#endif
