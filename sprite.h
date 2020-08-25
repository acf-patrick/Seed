#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <SDL2/SDL.h>
#include "object.h"
#include "drawable.h"

class Sprite : public Object, public Drawable
{
public:
	Sprite(int, int, const std::string&);

	void defineSourceRect(int, int, int, int);
	void defineSourceRect(const SDL_Rect&);

	void setFlip(SDL_RendererFlip);
	void setTexture(SDL_Texture*);

    virtual void draw(SDL_Renderer*);

protected:
	// tells which part of the texture will be drawn
    SDL_Rect m_source_rect;
    SDL_RendererFlip m_flip;
};

#endif // SPRITE_H
