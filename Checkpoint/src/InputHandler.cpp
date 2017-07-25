#include "../include/InputHandler.hpp"
#include "../include/Application.hpp"

InputHandler::InputHandler()
{
    m_Keystate = SDL_GetKeyboardState(NULL);
}

InputHandler::~InputHandler() 
{
    m_pressKey.clear();
}

// Actualize inputs
void InputHandler::update()
{
    // event structure
    SDL_Event event;
    
    // Clear previous state
    m_pressKey.clear();
 
    while(SDL_PollEvent(&event)) {
        switch (event.type) { 

        // Evento de cierre de la aplicacion
        case SDL_QUIT:
            TheApplication->quit();
            break;

        // Evento de presion de tecla
        case SDL_KEYDOWN:
            // Se guarda si la tecla fue presionada solo una vez o se mantuvo pulsada
            if (not event.key.repeat)
                m_pressKey[event.key.keysym.scancode] = true;
            break;
        default:
            break;    
        }
    }
}

// Check if key is pressed
bool InputHandler::isKeyDown(SDL_Scancode key)
{
    return m_Keystate[key];
}
bool InputHandler::isKeyDown(Botton botton)
{
    return m_Keystate[botton];
}

// Check if key is not pressed
bool InputHandler::isKeyUp(SDL_Scancode key)
{
    return not m_Keystate[key];
}
bool InputHandler::isKeyUp(Botton botton)
{
    return not m_Keystate[botton];
}

// Check if key was pressed once
bool InputHandler::onPress(SDL_Scancode key)
{
    return m_pressKey[key];
}
bool InputHandler::onPress(Botton botton)
{
    return m_pressKey[botton];
}
