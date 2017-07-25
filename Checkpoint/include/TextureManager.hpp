#ifndef __TextureManager__
#define __TextureManager__

#include <map>
#include <string>

class TextureManager;

#include "Application.hpp"

/* Almacenamiento de texturas

TextureManager toma a "data/" como raiz para buscar las texturas, así las
texturas deben almacenarse en la carpeta "data/", pasando la ruta (fileName)
respecto a "data/".

Ej:

data/
    background/
            special/
                img1.png
        img2.png
    img3.png

Deben ingresarse el argumento fileName como:
    img1.png -> "background/special/img1.png"
    img2.png -> "background/img2.png"
    img3.png -> "img3png"

*/


class TextureManager
{
public:
    TextureManager();
    ~TextureManager() 
    { 
      freeTextureMap(); 
    }

    // Cargar nueva textura
    bool load(std::string fileName, std::string id);    
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);    

    // Descargar textura
    bool unload(std::string id);

    // Dibujar textura
    void draw(std::string id, int srcX, int srcY, int destX, int destY, int width, int height,
              SDL_RendererFlip flip = SDL_FLIP_NONE);
    void draw(std::string id, int srcX, int srcY, int destX, int destY, int width, int height,
              SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Dibujar textura fondo
    void drawBackground(std::string id, int srcX, int srcY, int width, int height,
                        bool all = false, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawBackground(std::string id, int srcX, int srcY, int width, int height, 
                        SDL_Renderer* pRenderer, bool all = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Dibujar frame textura
    void drawFrame(std::string id, int x, int y, int width, 
                   int height, int currentRow, int currentFrame,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string id, int x, int y, int width, 
                   int height, int currentRow, int currentFrame,
                   SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    std::string getDataFolder() const { return dataFolder; } 

    void freeTextureMap();

private:
    std::map<std::string, SDL_Texture*> m_textureMap;
    std::string dataFolder;
};
#endif