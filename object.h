#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>

class Object
{
public:
	Object();
	virtual ~Object();

	// mettre à jour l'objet à chaque frame
	virtual void update();

	void setPosition(int, int);
	void getPosition(int&, int&);

private:
	// positions
	float m_x, m_y;
	// bounding box
	SDL_Rect m_rect;
	// in degrees
	float m_angle;
};

#endif // OBJECT_H
