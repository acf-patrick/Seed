#include "drawable.h"
#include "app.h"
#include <SDL2/SDL_image.h>

Drawable::~Drawable()
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);
    m_surface = NULL;
    m_texture = NULL;
}

void Drawable::draw(SDL_Renderer* renderer) const
{
	// overload
}

void Drawable::draw(SDL_Surface* target_surface) const
{
	// overload
}

SDL_Texture* loadTexture(const std::string& file_name)
{
    SDL_Texture* ret = IMG_LoadTexture(App::instance->getRenderer(), file_name.c_str());
    if (!ret)
        std::cerr << "Failed to load the texture : " << IMG_GetError() << std::endl;
    return ret;
}
