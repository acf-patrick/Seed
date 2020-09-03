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
	Sprite(int x = 0, int y = 0, std::string file_img = "");

	/* which part of the texture will be shown */
	void defineSourceRect(int, int, int, int);
	void defineSourceRect(const SDL_Rect&);

	void flip(SDL_RendererFlip);

	virtual void setTexture(SDL_Texture*);
	virtual void setTexture(const std::string&);

    void draw(SDL_Renderer*);

    SDL_Point getTextureSize();

    void zoom(float, float);
    void setScaleX(float);
    void setScaleY(float);

protected:
	// tells which part of the texture will be drawn
	// set to texture's size by default
    SDL_Rect m_source_rect;

    SDL_RendererFlip m_flip;

    float m_scaleX, m_scaleY;

};

#endif // SPRITE_H
