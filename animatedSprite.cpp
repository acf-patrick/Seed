#include "animatedSprite.h"

AnimatedSprite::AnimatedSprite(int x, int y, int frames_per_second) :
	Sprite(x, y), m_component(NULL), m_timer(1000/frames_per_second)
{}

AnimatedSprite::~AnimatedSprite()
{
	delete m_component;
	m_component = NULL;
}

void AnimatedSprite::setResources(const std::string& img_name, std::vector<SDL_Rect> rects)
{
    UsingSpritesheet *component = new UsingSpritesheet((int)m_x, (int)m_y, img_name);

	component->defineSrcRects(rects);
	m_component = static_cast<Sprite*>(component);
}

void AnimatedSprite::setResources(std::vector<SDL_Texture*> textures)
{
    SeparatedSprites *component = new SeparatedSprites((int)m_x, (int)m_y);
    component->setTextures(textures);
	m_component = static_cast<Sprite*>(component);
}

void AnimatedSprite::update()
{
	if (m_component)
		if (m_timer.out())
		{
			m_component->setPosition(m_x, m_y);
			m_component->update();
			m_timer.restart();
		}
}

void AnimatedSprite::draw(SDL_Renderer* renderer)
{
	if (m_component)
		m_component->draw(renderer);
}

void AnimatedSprite::setResources(const std::string& img_name, int frames_count)
{
    UsingSpritesheet *component = new UsingSpritesheet((int)m_x, (int)m_y, img_name);

	int w (component->getSize().x), h(component->getSize().y);
	w /= frames_count;
	std::vector<SDL_Rect> rects;
	for (int i=0; i < frames_count; ++i)
	{
        SDL_Rect r = { Sint16(i*w), 0, Uint16(w), Uint16(h) };
        rects.push_back(r);
	}

	component->defineSrcRects(rects);
	// component->setSize(w, h);
	m_component = static_cast<Sprite*>(component);
}

void AnimatedSprite::flip(SDL_RendererFlip p_flip)
{
	Sprite::flip(p_flip);
    if (m_component)
		m_component->flip(p_flip);
}

void AnimatedSprite::setTexture(SDL_Texture* texture)
{
	Sprite::setTexture(texture);
	UsingSpritesheet* sprite = dynamic_cast<UsingSpritesheet*> (m_component);
	if (sprite)
		sprite->setTexture(texture);
}
