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

void Object::getPosition(int & x, int & y)
{
	x = (int)m_x;
	y = (int)m_y;
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
