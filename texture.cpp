#include "texture.h"
#include "app.h"
#include <sstream>
#include <SDL2/SDL_image.h>

TextureManager* TextureManager::instance(nullptr);

TextureManager::TextureManager()
{ instance = this; }

TextureManager::~TextureManager()
{
	for (auto pair : m_textures)
	{
		SDL_DestroyTexture(pair.second);
		m_textures[pair.first] = nullptr;
	}
}

SDL_Texture* TextureManager::load(const std::string & file_name, std::string ID)
{
	if (ID.empty())
	{
        std::stringstream oss;
        oss << "Texture n° " << instance->m_textures.size()+1;
        ID = oss.str();
	}
    SDL_Texture *texture = IMG_LoadTexture(App::instance->getRenderer(), file_name.c_str());
    if (texture)
		instance->m_textures[ID] = texture;
	else if (!file_name.empty())
		std::cerr << "Failed to load " << file_name << " : " << IMG_GetError() << std::endl;
	return texture;
}

SDL_Texture* TextureManager::get(const std::string & ID)
{ return instance->m_textures[ID]; }
