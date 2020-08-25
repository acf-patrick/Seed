#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <iostream>
#include <vector>
#include "sprite.h"
#include "drawable.h"

class AnimatedSprite : public Object, public Drawable
{
private:
	class UsingSpritesheet : public Sprite
	{
	public:
		UsingSpritesheet(int x, int y, const std::string & spritesheet) :
			Sprite(x, y, spritesheet), m_frame_index(0)
		{}
		void defineSrcRects(std::vector<SDL_Rect> rects)
		{ m_srcrects = rects; }

		void update()
		{
			int len(m_srcrects.size());
			if (!len)
				return;
			m_frame_index = (m_frame_index+1)%len;
			defineSourceRect(m_srcrects[m_frame_index]);
		}

	private:
		int m_frame_index;
		std::vector<SDL_Rect> m_srcrects;
	};
	class SeparatedSprites : public Sprite
	{
	public:
		SeparatedSprites(int x, int y) : Sprite(x, y, ""), m_frame_index(0)
		{}
		~SeparatedSprites()
		{
			for (auto texture : m_image_textures)
				SDL_DestroyTexture(texture);
		}

		void setTextures(std::vector<SDL_Texture*> textures)
		{ m_image_textures = textures; }

		void update()
		{
			int len(m_image_textures.size());
			if (!len)
				return;
			m_frame_index = (m_frame_index+1)%len;
			setTexture(m_image_textures[m_frame_index]);
		}

	private:
		int m_frame_index;
		std::vector<SDL_Texture*> m_image_textures;
	};

protected:
    Sprite* m_component;

public:
	AnimatedSprite(int, int);
	~AnimatedSprite();

	void setResources(SDL_Texture*, std::vector<SDL_Rect>);
	void setResources(std::vector<SDL_Texture*>);

	void update();
	void draw(SDL_Renderer*);
};
#endif // ANIMATED_SPRITE_H
