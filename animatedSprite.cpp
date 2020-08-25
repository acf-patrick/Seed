#include "animatedSprite.h"

AnimatedSprite::AnimatedSprite(int x, int y) : m_component(NULL)
{ setPosition(x, y); }

AnimatedSprite::~AnimatedSprite()
{ delete m_component; }

void AnimatedSprite::setResources(SDL_Texture* spritesheet, std::vector<SDL_Rect> rects)
{
    UsingSpritesheet *component = new UsingSpritesheet((int)m_x, (int)m_y, "");
    component->setTexture(spritesheet);
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

}

void AnimatedSprite::draw(SDL_Renderer* renderer)
{ m_component->draw(renderer); }
