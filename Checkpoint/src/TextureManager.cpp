#include <SDL2/SDL_image.h>

#include "../include/TextureManager.hpp"

// Cargar nueva textura
bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

    if (!pTempSurface){
        SDL_Log("No se pudo cargar %s", fileName.c_str());
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

    SDL_FreeSurface(pTempSurface);

    if (pTexture) {
        SDL_Log("Cargado: %s => %s", id.c_str(), fileName.c_str());
        m_textureMap[id] = pTexture;
        return true;
    }
    return false;
}

bool TextureManager::load(std::string fileName, std::string id)
{
    return load(fileName, id, TheApplication->getRenderer());
}

// Descargar textura
bool TextureManager::unload(std::string id)
{
    if (m_textureMap.find(id) == m_textureMap.end()) {
        SDL_Log("No existe id: %s", id.c_str());
        return false;
    }
    SDL_DestroyTexture(m_textureMap[id]);
    m_textureMap.erase(id);
    SDL_Log("Eliminada textura %s", id.c_str());
    return true;
}

// Dibujar textura

void TextureManager::draw(std::string id, int srcX, int srcY, int destX, int destY,
                          int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = srcX;
    srcRect.y = srcY;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;

    destRect.x = destX;
    destRect.y = destY;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0 ,0, flip);
}
void TextureManager::draw(std::string id, int srcX, int srcY, int destX, int destY, 
                          int width, int height, SDL_RendererFlip flip)
{
    draw(id, srcX, srcY, destX, destY, width, height, TheApplication->getRenderer(), flip);
}

// Dibujar textura fondo
void TextureManager::drawBackground(std::string id, int srcX, int srcY, int width, int height,
                                    SDL_Renderer* pRenderer, bool all, SDL_RendererFlip flip)
{
    if (all) {
        SDL_RenderCopyEx(pRenderer, m_textureMap[id], NULL, NULL, 0 ,0, flip);
    } else {
        SDL_Rect srcRect;

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.w = width;
        srcRect.h = height;
        SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, NULL, 0 ,0, flip);
    }

}

void TextureManager::drawBackground(std::string id, int srcX, int srcY, int width, int height,
                                    bool all, SDL_RendererFlip flip)
{
    drawBackground(id, srcX, srcY, width, height, TheApplication->getRenderer(), all, flip);
}


// Dibujar frame textura
void TextureManager::drawFrame(std::string id, int x, int y, int width, 
                               int height, int currentRow, int currentFrame,
                               SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;

    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0 ,0, flip);
}
void TextureManager::drawFrame(std::string id, int x, int y, int width, 
                               int height, int currentRow, int currentFrame,
                               SDL_RendererFlip flip)
{
    drawFrame(id, x, y, width, height, currentRow, currentFrame, TheApplication->getRenderer(), flip);  
}

void TextureManager::freeTextureMap()
{
    for (auto it = m_textureMap.begin(); it != m_textureMap.end(); ++it){
        SDL_DestroyTexture(it->second);
        m_textureMap.erase(it);
    }
}