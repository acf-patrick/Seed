#include "header/sprite.h"
#include "header/texture.h"

Sprite::Sprite(int x, int y, std::string file_img) :
	m_flip(SDL_FLIP_NONE), m_scaleX(1),
	m_scaleY(1)
{
    setPosition(x, y);
    if (!file_img.empty())
		setTexture(TextureManager::load(file_img));
}

void Sprite::defineSourceRect(int x, int y, int w, int h)
{
    m_source_rect.x = (Sint16)x;
    m_source_rect.y = (Sint16)y;
    m_source_rect.w = (Uint16)w;
    m_source_rect.h = (Uint16)h;
}

void Sprite::defineSourceRect(const SDL_Rect & rect)
{
    m_source_rect.x = rect.x;
    m_source_rect.y = rect.y;
    m_source_rect.w = rect.w;
    m_source_rect.h = rect.h;
}

void Sprite::draw(SDL_Renderer * renderer, Camera * camera)
{
	SDL_Rect crect = { 0 };
	if (camera)
		crect = camera->getBox();
	SDL_Rect source(m_source_rect), dest;
	dest.x = (Sint16)(m_x - crect.x);
	dest.y = (Sint16)(m_y - crect.y);
	dest.w = m_w;
	dest.h = m_h;
	SDL_RenderCopyEx(renderer, m_texture, &source, &dest, m_angle, NULL, m_flip);
}

void Sprite::flip(SDL_RendererFlip p_flip)
{ m_flip = p_flip; }

void Sprite::setTexture(SDL_Texture* texture)
{ m_texture = texture; }

void Sprite::setTexture(const std::string & file_name)
{ m_texture = TextureManager::load(file_name); }

SDL_Point Sprite::getTextureSize()
{
	SDL_Point ret;
	SDL_QueryTexture(m_texture, NULL, NULL, &ret.x, &ret.y);
	return ret;
}

void Sprite::zoom(float scale_x, float scale_y)
{
	setScaleX(scale_x);
	setScaleY(scale_y);
}

void Sprite::setScaleX(float scale_x)
{
	m_scaleX = scale_x;
	m_w *= scale_x;
}

void Sprite::setScaleY(float scale_y)
{
	m_scaleY = scale_y;
	m_h *= scale_y;
}
