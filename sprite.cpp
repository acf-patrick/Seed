#include "sprite.h"

Sprite::Sprite(int x, int y, const std::string& image_file) : m_flip(SDL_FLIP_NONE)
{
    setPosition(x, y);
    setTexture(loadTexture(image_file));
	defineSourceRect(0, 0, m_rect.w, m_rect.h);
}

void Sprite::defineSourceRect(int x, int y, int w, int h)
{
    m_source_rect.x = (Sint16)x;
    m_source_rect.y = (Sint16)y;
    m_source_rect.w = (Uint16)w;
    m_source_rect.h = (Uint16)h;
}

void Sprite::draw(SDL_Renderer* renderer)
{
	SDL_Rect copy(m_source_rect);
	SDL_Point center(getCenter());
	SDL_RenderCopyEx(renderer, m_texture, &copy, &m_rect, m_angle, &center, m_flip);
}

void Sprite::defineSourceRect(const SDL_Rect & rect)
{
    m_source_rect.x = rect.x;
    m_source_rect.y = rect.y;
    m_rect.w = m_source_rect.w = rect.w;
    m_rect.h = m_source_rect.h = rect.h;
}

void Sprite::setFlip(SDL_RendererFlip flip)
{ m_flip = flip; }

void Sprite::setTexture(SDL_Texture* texture)
{
    if (!texture)
		return;
	m_texture = texture;
    if (m_texture)
		SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
}
