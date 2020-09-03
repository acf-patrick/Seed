#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>

class Object
{
public:
	Object();
	virtual ~Object();

	virtual void update();

	void move(int, int);

	void setPosition(int, int);
	SDL_Point getPosition();

	void setCenter(int, int);
	SDL_Point getCenter();

	void setSize(int, int);
	SDL_Point getSize();

	void setBox(int, int, int, int);
	SDL_Rect getBox();

	void setAngle(float);
	float getAngle();

protected:
	// positions
	float m_x, m_y;
	// real size
	int m_w, m_h;
	// in degrees
	float m_angle;
};

#endif // OBJECT_H
