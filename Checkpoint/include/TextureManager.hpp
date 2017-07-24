#ifndef __TextureManager__
#define __TextureManager__

#include <map>
#include <string>

class TextureManager;

#include "Application.hpp"

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