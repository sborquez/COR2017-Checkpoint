#include "../include/Application.hpp"

// Singleton instance pointer
Application* Application::s_pInstance = NULL;

bool Application::init(const char* title, int xpos, int ypos, int width,
                       int height, bool fullscreen, bool gpio)
{   
    // Habilitar pantalla completa
    int flags = 0;
    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    // No mostrar cursor
    SDL_ShowCursor(SDL_DISABLE);

    // Intento de iniciar SDL
    SDL_Log("Iniciando SDL ... ");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("SDL inicio fallido - %s ", SDL_GetError());
        return false;
    }

    // Intento de iniciar nueva ventana
    SDL_Log("\tIniciando Ventana ... ");    
    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (m_pWindow == NULL) {
        SDL_Log("\tError al crear ventana - %s", SDL_GetError());
        return false;
    }
    SDL_Log("\tVentana iniciada");

    // Intento de iniciar Renderer
    SDL_Log("\tIniciando Renderer ... ");    
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if (m_pRenderer == NULL) {
        SDL_Log("\tError al crear ventana - %s", SDL_GetError());
        return false;
    }
    SDL_Log("\tRenderer iniciado");
    
    // Inicio exitoso   
    SDL_Log("SDL inicio exitoso");    
    
    // Iniciando variables
    // comenzar bucle principal, la aplicacion esta corriendo
    m_bRunning = true;

    // TextureManager
    m_pTextureManager = new TextureManager;

    // Input Handler
    /*
    if (gpio)
        m_pInputHandler = new InputHandlerGpio;
    else
        m_pInputHandler = new InputHandlerKeyBoard;
    */
    m_pInputHandler = new InputHandler;

    // SceneStateMachine, iniciar nueva 
    m_pSceneStateMachine = new SceneStateMachine;
    // Cargar la primera escena
    m_pSceneStateMachine->firstScene();

    return true;
}

// Dibujar en pantalla
void Application::render() 
{
    // Limpiar pantalla
    SDL_RenderClear(m_pRenderer);

    // Dibujar escena actual
    m_pSceneStateMachine->render();

    // Mostrar en pantalla
    SDL_RenderPresent(m_pRenderer);
}

void Application::update()
{
    // Actualizar escena actual
    m_pSceneStateMachine->update();
}

void Application::handleEvents()
{
    // Manipular eventos
    //m_pInputHandler->update();

    //TEST
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) { 
        case SDL_QUIT:
            quit();
            break;
        default:
            break;    
        }
    }

    m_pSceneStateMachine->handleEvents();
}

// Liberar memoria
void Application::clean()
{
    delete s_pInstance;
    s_pInstance = NULL;
}

// Destructor
Application::~Application()
{
    SDL_Log("Eliminando Aplicacion ... ");
    if (m_pWindow != NULL) {
        SDL_Log("\tEliminando Ventana");
        SDL_DestroyWindow(m_pWindow);
    }   
    if (m_pRenderer != NULL) {
        SDL_Log("\tEliminando Renderer");
        SDL_DestroyRenderer(m_pRenderer);
    }
    if (m_pSceneStateMachine != NULL) {
        delete m_pSceneStateMachine;
        m_pSceneStateMachine = NULL;
    }
    if (m_pInputHandler != NULL) {
        delete m_pInputHandler;
        m_pInputHandler = NULL;
    }
    if (m_pTextureManager != NULL) {
        SDL_Log("\tBorrando texturas");
        delete m_pTextureManager;
        m_pTextureManager = NULL;
    }
    SDL_Log("\tFinalizando SDL");
    SDL_Quit();
}
