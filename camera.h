#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "object.h"
#include "sprite.h"

class Camera : public Object
{
public:
	enum Mode { center_following, rect_container };
	Camera(Mode, Object* focus = nullptr);
	~Camera();

	void setContainer(int, int, int, int);
	void setLimit(int, int, int, int);

	void update();
	void draw(Sprite*);

	static Camera* instance;

protected:
	Object* m_focus;
	SDL_Rect *m_container, *m_limit;
	Mode m_mode;
};

#endif // CAMERA_H

