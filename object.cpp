#include "object.h"

Object::Object()
{
    setPosition(0, 0);
    m_rect.w = m_rect.h = angle = 0;
}

Object::~Object()
{}

void Object::setPosition(int x, int y)
{
    m_x = rect.x = x;
    m_y = rect.y = y;
}

void Object::getPosition(int & x, int & y)
{
	x = (int)m_x;
	y = (int)m_y;
}

void Object::update()
{}
