#include "animatedSprite.h"
#include "texture.h"

AnimatedSprite::AnimatedSprite(int x, int y, int frames_per_second, Mode mode) :
	Sprite(x, y), m_timer(1000/frames_per_second),
	m_frame_index(0), m_mode(mode)
{ }

AnimatedSprite::~AnimatedSprite()
{ m_image_textures.clear(); }

void AnimatedSprite::setResources(const std::string& img_name, std::vector<SDL_Rect> rects)
{
	setTexture(img_name);
	m_srcrects = rects;
}

void AnimatedSprite::setResources(const std::vector<std::string> & files)
{
	for (auto name : files)
        m_image_textures.push_back(TextureManager::load(name));
}

void AnimatedSprite::update()
{
	if (m_timer.out())
	{
		int len(0);
		if (m_mode == using_spritesheet)
		{
			defineSourceRect(m_srcrects[m_frame_index]);
			len = m_srcrects.size();
		}
		else if (m_mode == separated_sprites)
		{
			Sprite::setTexture(m_image_textures[m_frame_index]);
			len = m_image_textures.size();
		}
		if (len)
			m_frame_index = (m_frame_index+1)%len;
		m_timer.restart();
	}
}

void AnimatedSprite::setResources(const std::string& img_name, int frames_count)
{
	setTexture(img_name);
	SDL_Point size(getTextureSize());
	int w(size.x), h(size.y);
	w /= frames_count;
	for (int i=0; i < frames_count; ++i)
	{
        SDL_Rect r = { Sint16(i*w), 0, Uint16(w), Uint16(h) };
        m_srcrects.push_back(r);
	}
}

void AnimatedSprite::setTexture(SDL_Texture* texture)
{
    if (m_mode == using_spritesheet)
		Sprite::setTexture(texture);
}

void AnimatedSprite::setTexture(const std::string & file_name)
{
	if (m_mode == using_spritesheet)
		Sprite::setTexture(file_name);
}

void AnimatedSprite::draw(SDL_Renderer* renderer)
{
	SDL_Point centered;
    if (m_mode == using_spritesheet)
	{
        centered.x = 0.5*(m_w - m_source_rect.w);
        centered.y = 0.5*(m_h - m_source_rect.h);
	}
	else
	{
		SDL_Point t_size(getTextureSize());
        centered.x = 0.5*(m_w - t_size.x);
        centered.y = 0.5*(m_h - t_size.y);
	}
    move (centered.x, centered.y);
	Sprite::draw(renderer);
    move (-centered.x, -centered.y);
}

