#include "object.h"

Object::Object()
{
    setPosition(0, 0);
    m_rect.w = m_rect.h = 0;
    m_angle = 0;
}

Object::~Object()
{}

void Object::setPosition(int x, int y)
{
    m_x = x;
    m_rect.x = (Sint16)x;
    m_y = y;
    m_rect.y = (Sint16)y;
}

SDL_Point Object::getPosition()
{
    SDL_Point ret = { (int)m_x, (int)m_y };
    return ret;
}

void Object::update()
{
	// overload
}

void Object::setBox(int x, int y, int w, int h)
{
	setPosition(x, y);
	m_rect.w = (Uint16)w;
	m_rect.h = (Uint16)h;
}

void Object::setCenter(int x, int y)
{ setPosition(x-0.5*m_rect.w, y-0.5*m_rect.h); }

SDL_Point Object::getCenter()
{
	SDL_Point ret = { int(m_x+0.5*m_rect.w), int(m_y+0.5*m_rect.h) };
	return ret;
}

void Object::setSize(int w, int h)
{ setBox(m_x, m_y, w, h); }

SDL_Point Object::getSize()
{
	SDL_Point ret = { m_rect.w, m_rect.h };
	return ret;
}

SDL_Rect Object::getBox()
{ return m_rect; }
