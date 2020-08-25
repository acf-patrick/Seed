#include "drawable.h"

Drawable::~Drawable()
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);
    m_surface = m_texture = NULL;
}
