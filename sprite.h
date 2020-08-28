#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <SDL2/SDL.h>
#include "object.h"
#include "drawable.h"

/* note : m_rect contains the texture's size not object's size */

class Sprite : public Object, public Drawable
{
public:
	Sprite(int, int, std::string file_img = "");

	/* which part of the texture will be shown */
	void defineSourceRect(int, int, int, int);
	void defineSourceRect(const SDL_Rect&);

	virtual void flip(SDL_RendererFlip);

	virtual void setTexture(SDL_Texture*);
	virtual void setTexture(const std::string&);

    void draw(SDL_Renderer*);

protected:
	// tells which part of the texture will be drawn
    SDL_Rect m_source_rect;

    SDL_RendererFlip m_flip;

private:
    void updateSize();

};

#endif // SPRITE_H
