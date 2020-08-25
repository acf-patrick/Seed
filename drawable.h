#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SDL2/SDL.h>
#include <iostream>

// virtual class for drawable objects
class Drawable
{
public:
	virtual ~Drawable();
	virtual void draw(SDL_Renderer*) const;
	virtual void draw(SDL_Surface*) const;

protected:
    SDL_Texture* m_texture;
    SDL_Surface* m_surface;
};

SDL_Texture* loadTexture(const std::string&);

#endif // DRAWABLE_H

