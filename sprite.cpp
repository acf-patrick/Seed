#include "sprite.h"
#include "texture.h"

Sprite::Sprite(int x, int y, std::string file_img) : m_flip(SDL_FLIP_NONE)
{
    setPosition(x, y);
    if (!file_img.empty())
		setTexture(TextureManager::loadTexture(file_img));
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
	SDL_Rect source(m_source_rect), dest(m_rect);
	/* prevent for texture scaling */
	dest.w = m_source_rect.w;
	dest.h = m_source_rect.h;
	SDL_Point center(getCenter());
	SDL_RenderCopyEx(renderer, m_texture, &source, &dest, m_angle, &center, m_flip);
}

void Sprite::defineSourceRect(const SDL_Rect & rect)
{
    m_source_rect.x = rect.x;
    m_source_rect.y = rect.y;
    m_source_rect.w = rect.w;
    m_source_rect.h = rect.h;
}

void Sprite::flip(SDL_RendererFlip p_flip)
{ m_flip = p_flip; }

void Sprite::setTexture(SDL_Texture* texture)
{
	m_texture = texture;
	updateSize();
}

void Sprite::setTexture(const std::string & file_name)
{
    m_texture = TextureManager::loadTexture(file_name);
    updateSize();
}

void Sprite::updateSize()
{
	if (m_texture)
		SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
}
