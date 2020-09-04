#include "header/texture.h"
#include "header/app.h"
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
	TextureManager & self = *instance;
	if (ID.empty())
	{
        std::stringstream oss;
        oss << "Texture n° " << self.m_textures.size()+1;
        ID = oss.str();
	}
    SDL_Texture *texture = IMG_LoadTexture(App::instance->getRenderer(), file_name.c_str());
    if (texture)
		self.m_textures[ID] = texture;
	else if (!file_name.empty())
		std::cerr << "Failed to load " << file_name << " : " << IMG_GetError() << std::endl;
	return texture;
}

SDL_Texture* TextureManager::get(const std::string & ID)
{ return instance->m_textures[ID]; }

void TextureManager::destroy(const std::string& ID)
{
	TextureManager & self = *instance;
	SDL_DestroyTexture(self.m_textures[ID]);
	self.m_textures.erase(ID);
}

void TextureManager::destroy(SDL_Texture * texture)
{
	TextureManager & self = *instance;
	std::string ID;
	for (auto pair : self.m_textures)
		if (pair.second == texture)
		{
			ID = pair.first;
			SDL_DestroyTexture(pair.second);
		}
	self.m_textures.erase(ID);
}