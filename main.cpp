#include "app.h"
#include "drawable.h"
#include "animatedSprite.h"

const int w(480), h(360);

class Test : public App
{
public:
	AnimatedSprite sprite;

	Test() : App("test", w, h), sprite(0, 0, 20, AnimatedSprite::using_spritesheet)
	{
		sprite.setSize(32, 32);
		sprite.setResources("img.png", 11);
		m_camera = new Camera(Camera::center_following);
		m_camera->setBox(0, 0, w, h);
	}

	void update()
	{ sprite.update(); }
	void render()
	{
		cleanTarget();
		draw(&sprite);
	}
};

int main(int argc, char* argv[])
{
	Test().run();
	return 0;
}
