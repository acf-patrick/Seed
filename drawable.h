#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SDL2/SDL.h>
#include <iostream>

// virtual class for drawable objects
class Drawable
{
public:
	virtual ~Drawable();
	virtual void draw(SDL_Renderer*);

protected:
    SDL_Texture* m_texture;
};

#endif // DRAWABLE_H

