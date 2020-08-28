#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <iostream>
#include <vector>
#include "timer.h"
#include "sprite.h"
#include "drawable.h"

class AnimatedSprite : public Sprite
{
public:
	enum Mode { using_spritesheet, separated_sprites };

	AnimatedSprite(int, int, int, Mode);
	~AnimatedSprite();

	void setResources(const std::string&, std::vector<SDL_Rect>);
	void setResources(const std::string&, int);
	void setResources(std::vector<SDL_Texture*>);

	void setTexture(SDL_Texture*);
	void setTexture(const std::string&);

	void update();

protected:
    Chrono m_timer;

    int m_frame_index;
    Mode m_mode;

	std::vector<SDL_Rect> m_srcrects;
	std::vector<SDL_Texture*> m_image_textures;

private:
	void defineSrcRects(std::vector<SDL_Rect> rects)
	{ m_srcrects = rects; }
	void setTextures(std::vector<SDL_Texture*> textures)
	{ m_image_textures = textures; }
};
#endif // ANIMATED_SPRITE_H
