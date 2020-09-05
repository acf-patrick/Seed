#ifndef MAP_H
#define MAP_H

#include <tmx/tmx.h>
#include <SDL2/SDL.h>
#include "drawable.h"
#include "texture.h"
#include "camera.h"

class Tilemap : public Drawable
{
public:
    Tilemap(const std::string&);
    ~Tilemap();
	
	void draw(SDL_Renderer*, Camera*);

protected:
    tmx_map * m_map;
	
	void drawLayers(tmx_layer*);
	virtual void drawObjects(tmx_object_group*);
	
private:
	void drawImage(tmx_layer*);
	void drawTiles(uint32_t*);
	
	void* _load(const char* file_name)
	{ 
		return (void*)TextureManager::load(std::string(file_name)); 
	}
	void _free(void* texture)
	{ 
		TextureManager::destroy((SDL_Texture*)texture); 
	}
};

#endif // MAP_H

