#ifndef __InputHandler__
#define __InputHandler__

#include <SDL2/SDL.h>
#include <map>

enum Botton
{
    B_UP = SDL_SCANCODE_UP,
    B_DOWN = SDL_SCANCODE_DOWN,
    B_LEFT = SDL_SCANCODE_LEFT,
    B_RIGHT = SDL_SCANCODE_RIGHT,
    B_A = SDL_SCANCODE_Z,
    B_B = SDL_SCANCODE_X,
    B_C = SDL_SCANCODE_C,
    B_D  = SDL_SCANCODE_S,
    B_LTRIGER = SDL_SCANCODE_A,
    B_RTRIGER = SDL_SCANCODE_D,
    B_START = SDL_SCANCODE_EXECUTE,
    B_SELECT = SDL_SCANCODE_BACKSPACE,
    B_RESET = SDL_SCANCODE_R,
    B_QUIT = SDL_SCANCODE_ESCAPE
};


class InputHandler
{
public:
    InputHandler();
    
    ~InputHandler();

    // Actualize inputs
    void update();

    // Check if key is pressed
    bool isKeyDown(SDL_Scancode key);
    bool isKeyDown(Botton botton);

    // Check if key is not pressed
    bool isKeyUp(SDL_Scancode key);
    bool isKeyUp(Botton botton);

    // Check if key was pressed once
    bool onPress(SDL_Scancode key);
    bool onPress(Botton botton);

private:
    // Keys pressed once in actual state
    std::map<Uint8, bool> m_pressKey;

    // Keys pressed in actual state
    const Uint8* m_Keystate;
};
#endif