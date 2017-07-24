#include "../include/Application.hpp"

#define HEIGHT 480
#define WIDTH 640

int main(int argc, char const *argv[])
{
    // Habilitar modo pantalla completa
    bool fullscreen = false;

    // Habilitar entradas por gpio
    bool gpio = false;

    // Separar argumentos
    if (argc >= 2) {
        for (int i = 1; i < argc; ++i) {
            switch (*argv[i]) {
            case 'F':
            case 'f': 
                fullscreen = true;
                break;
            case 'G':
            case 'g':
                gpio = true;
                break;
            default:
                SDL_Log("Argumentos incorrectos");
                SDL_Log("Saliendo");
                return 1;
            }
        }
    }
    if (gpio)
        SDL_Log("Modo GPIO");   
    
    if (fullscreen)
        SDL_Log("Modo Pantalla Completa");
    
    // Establecer directorio de trabajo
    TheApplication->setDir(std::string(argv[0]));

    // Iniciar applicacion
    if (TheApplication->init("Checkpoint", 0, 0, WIDTH, HEIGHT, fullscreen, gpio)) {
        SDL_Log("Aplicacion iniciada");
    } else {
        SDL_Log("No se pudo iniciar la aplicacion - %s", SDL_GetError());
        SDL_Log("Saliendo");   
        return 1;
    }

    // Bucle principal
    while (TheApplication->running()) {
        TheApplication->handleEvents();
        TheApplication->update();
        TheApplication->render();
    } 

    // Vaciar memoria
    TheApplication->clean();
    SDL_Log("Saliendo");
    return 0;
}