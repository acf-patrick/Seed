#include "drawable.h"
#include "app.h"
#include <SDL2/SDL_image.h>

Drawable::~Drawable()
{
    SDL_DestroyTexture(m_texture);
    m_texture = NULL;
}

void Drawable::draw(SDL_Renderer* renderer)
{
	// overload
}

SDL_Texture* Drawable::loadTexture(const std::string& file_name)
{
    SDL_Texture* ret = IMG_LoadTexture(App::instance->getRenderer(), file_name.c_str());
    if (!ret)
        std::cerr << "Failed to load the texture : " << IMG_GetError() << std::endl;
    return ret;
}
