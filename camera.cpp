#include "camera.h"
#include "app.h"

Camera* Camera::instance(nullptr);

Camera::Camera(Mode mode, Object* focus) :
	m_focus(focus), m_container(nullptr),
	m_limit(nullptr), m_mode(mode)
{ instance = this; }

Camera::~Camera()
{
	instance = nullptr;
	delete m_container;
	delete m_limit;
	m_container = m_limit = nullptr;
}

void Camera::setContainer(int x, int y, int w, int h)
{
    m_container = new SDL_Rect;
    m_container->x = (Sint16)x;
    m_container->y = (Sint16)y;
	m_container->w = (Uint16)w;
	m_container->h = (Uint16)h;
}

void Camera::setLimit(int x, int y, int w, int h)
{
	SDL_Rect *tmp(m_container);
	setContainer(x, y, w, h);
	m_limit = m_container;
	m_container = tmp;
}

void Camera::update()
{
	if (!m_focus)
		return;
	SDL_Point object_center(m_focus->getCenter());
    if (m_mode == center_following)
	{
		m_rect.x = Sint16(object_center.x - m_rect.w/2.);
		m_rect.y = Sint16(object_center.y - m_rect.w/2.);
	}
	else if (m_container)
	{
        int x_min(m_rect.x + m_container->x),
			y_min(m_rect.y + m_container->y);
        int x_max(x_min + m_container->w),
			y_max(y_min + m_container->h);
        if (object_center.x < x_min)
			m_rect.x -= Sint16(x_min - object_center.x);
        if (object_center.y < y_min)
			m_rect.y -= Sint16(y_min - object_center.y);
        if (object_center.x > x_max)
			m_rect.x -= Sint16(x_max - object_center.x);
        if (object_center.y > y_max)
			m_rect.y -= Sint16(y_max - object_center.y);
	}
    if (m_limit)
	{
        if (m_rect.x < m_limit->x) m_rect.x = m_limit->x;
        if (m_rect.y < m_limit->y) m_rect.y = m_limit->y;
        if (m_rect.x+m_rect.x >= m_limit->x+m_limit->w)
			m_rect.x = Sint16(m_limit->x+m_limit->w - m_rect.x);
        if (m_rect.y+m_rect.h >= m_limit->y+m_limit->h)
			m_rect.y = Sint16(m_limit->y+m_limit->h - m_rect.h);
	}
}

void Camera::draw(Sprite* sprite)
{
	if (!sprite)
		return;
	SDL_Point prev(sprite->getPosition());
    sprite->setPosition(prev.x - m_rect.x, prev.y - m_rect.y);
    sprite->draw(App::instance->getRenderer());
    sprite->setPosition(prev.x, prev.y);
}
