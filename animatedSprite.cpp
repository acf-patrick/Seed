#include "animatedSprite.h"

AnimatedSprite::AnimatedSprite(int x, int y, int frames_per_second, Mode mode) :
	Sprite(x, y), m_timer(1000/frames_per_second),
	m_frame_index(0), m_mode(mode)
{ }

AnimatedSprite::~AnimatedSprite()
{ m_image_textures.clear(); }

void AnimatedSprite::setResources(const std::string& img_name, std::vector<SDL_Rect> rects)
{
	setTexture(img_name);
	defineSrcRects(rects);
}

void AnimatedSprite::setResources(std::vector<SDL_Texture*> textures)
{ setTextures(textures); }

void AnimatedSprite::update()
{
	if (m_timer.out())
	{
		int len(m_srcrects.size());
		if (!len)
			return;
		m_frame_index = (m_frame_index+1)%len;
		if (m_mode == using_spritesheet)
			defineSourceRect(m_srcrects[m_frame_index]);
		else if (m_mode == separated_sprites)
			Sprite::setTexture(m_image_textures[m_frame_index]);
		m_timer.restart();
	}
}

void AnimatedSprite::setResources(const std::string& img_name, int frames_count)
{
	setTexture(img_name);

	int w(m_rect.w), h(m_rect.h);
	w /= frames_count;
	std::vector<SDL_Rect> rects;
	for (int i=0; i < frames_count; ++i)
	{
        SDL_Rect r = { Sint16(i*w), 0, Uint16(w), Uint16(h) };
        rects.push_back(r);
	}

	defineSrcRects(rects);
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
        centered.x = 0.5*(m_srcrects[m_frame_index].w - m_w);
        centered.y = 0.5*(m_srcrects[m_frame_index].h - m_h);
	}
    move (centered.x, centered.y);
    getPosition();
	Sprite::draw(renderer);
    move (-centered.x, -centered.y);
}

void AnimatedSprite::defineSrcRects(std::vector<SDL_Rect> rects)
{ m_srcrects = rects; }

void AnimatedSprite::setTextures(std::vector<SDL_Texture*> textures)
{ m_image_textures = textures; }

