#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SDL2/SDL.h>

// virtual class for drawable objects
class Drawable
{
public:
	virtual ~Drawable();
	virtual void draw(SDL_Renderer*) = 0;

protected:
    SDL_Texture* m_texture;
    SDL_Surface* m_surface;
};

#endif // DRAWABLE_H

