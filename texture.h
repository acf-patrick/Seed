#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <map>

class TextureManager
{
public:
	TextureManager() {}
    ~TextureManager()
    {
        for (auto pair : m_textures)
		{
            SDL_DestroyTexture(pair.second);
            m_textures[pair.first] = nullptr;
		}
    }
    static SDL_Texture* loadTexture(const std::string & file_name)
    {

    }

private:
	std::map<std::string, SDL_Texture*> m_textures;

	TextureManager* instance;
};
#endif // TEXTURE_H

