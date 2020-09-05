#include "header/object.h"

Object::Object()
{
    setBox(0, 0, 0, 0);
    m_angle = 0;
}

Object::~Object()
{}

void Object::setPosition(int x, int y)
{
    m_x = (float)x;
    m_y = (float)y;
}

SDL_Point Object::getPosition()
{
    SDL_Point ret = { int(m_x), int(m_y) };
    return ret;
}

void Object::update()
{
    // overload
}

void Object::setBox(int x, int y, int w, int h)
{
    setPosition(x, y);
    setSize(w, h);
}

void Object::setCenter(int x, int y)
{
    setPosition(x-0.5*m_w, y-0.5*m_h);
}

SDL_Point Object::getCenter()
{
    SDL_Point ret = { int(m_x+0.5*m_w), int(m_y+0.5*m_h) };
    return ret;
}

void Object::setSize(int w, int h)
{
    m_w = w;
    m_h = h;
}

SDL_Point Object::getSize()
{
    SDL_Point ret = { m_w, m_h };
    return ret;
}

SDL_Rect Object::getBox()
{
    SDL_Rect ret;
    ret.x = (Sint16)m_x;
    ret.y = (Sint16)m_y;
    ret.w = (Uint16)m_w;
    ret.h = (Uint16)m_h;
    return ret;
}

void Object::move(int x_offset, int y_offset)
{
    setPosition(m_x + x_offset, m_y + y_offset);
}

float Object::getAngle()
{
    return m_angle;
}

void Object::setAngle(float angle)
{
    m_angle = angle;
}
