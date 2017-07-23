#ifndef NULL
#define NULL 0
#endif

#ifndef __Application__
#define __Application__


#include <SDL2/SDL.h>

#include "TextureManager.hpp"
#include "SceneStateMachine.hpp"
#include "InputHandler.hpp"

#define TheApplication Application::Instance()

class Application {
public:
    ~Application();

    // Iniciar SDL y ventana de la aplicacion
    bool init (const char* title, int xpos, int ypos, int width, 
               int height, bool fullscreen, bool gpio);
    
    // Dibujar en pantalla
    void render();

    // Actualizar estados de la escena actual
    void update();

    // Manipular eventos en la escena actual
    void handleEvents();

    // Liberar memoria
    void clean();

    inline void quit() { m_bRunning = false; }

    // Esta corriendo?
    inline bool running() { return m_bRunning; }

    // Renderer
    inline SDL_Renderer* getRenderer() const { return m_pRenderer; }

    // StateMachine
    inline SceneStateMachine* getSceneStateMachine() const { return m_pSceneStateMachine; }

    // TextureManager
    inline TextureManager* getTextureManager() const { return m_pTextureManager; }

    // Input Handler
    inline InputHandler* getInputHandler() const { return m_pInputHandler; }

    // Singleton instance getter
    static Application* Instance()
    {
        if (!s_pInstance){
            s_pInstance = new Application();
        } 
        return s_pInstance;
    }
private:    

    // Singleton constructor
    Application() : 
                    m_pWindow(NULL), 
                    m_pRenderer(NULL), 
                    m_pInputHandler(NULL),
                    m_pTextureManager(NULL), 
                    m_pSceneStateMachine(NULL), 
                    m_bRunning(false)
    {

    }

    // Singleton instance pointer
    static Application* s_pInstance;

    // Ventana
    SDL_Window* m_pWindow;
    
    // Renderer
    SDL_Renderer* m_pRenderer; 

    // SceneStateMachine - controla las escenas
    SceneStateMachine* m_pSceneStateMachine;

    // TextureManager - contiene las images y texturas
    TextureManager* m_pTextureManager;

    // Input Handler - manipula las entradas de usuario
    InputHandler* m_pInputHandler;

    // Esta corriendo - flag de bucle principal
    bool m_bRunning;
};

#endif