#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <map>

class TextureManager
{
public:
	TextureManager();
    ~TextureManager();
    static SDL_Texture* loadTexture(const std::string &, std::string ID = "");
    static SDL_Texture* getTexture(const std::string &);

private:
	std::map<std::string, SDL_Texture*> m_textures;

	static TextureManager* instance;
};

#endif // TEXTURE_H
