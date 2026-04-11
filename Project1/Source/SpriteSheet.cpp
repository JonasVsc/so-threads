#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* surface = SDL_LoadPNG(path);
    if (!surface)
    {
        SDL_Log("Error: SDL_LoadPNG(): %s\n", SDL_GetError());
        return;
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!m_texture)
    {
        SDL_Log("Error: SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return;
    }
}

SpriteSheet::~SpriteSheet()
{
    if(m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
}
