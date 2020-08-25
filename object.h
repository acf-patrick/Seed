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
	SDL_Point getPosition();

	void setCenter(int, int);
	SDL_Point getCenter();

	void setSize(int, int);
	SDL_Point getSize();

	void setBox(int, int, int, int);
	SDL_Rect getBox();

protected:
	// positions
	float m_x, m_y;
	// bounding box
	SDL_Rect m_rect;
	// in degrees
	float m_angle;
};

#endif // OBJECT_H
