#include "app.h"
#include "drawable.h"
#include "animatedSprite.h"

class Test : public App
{
public:
	AnimatedSprite sprite;

	Test() : App("test", 600, 600), sprite(0, 0, 20)
	{
		sprite.setResources("img.png", 11);
	}

	void update()
	{
		sprite.update();
	}
	void render()
	{
		cleanTarget();
		draw(sprite);
	}
};

int main(int argc, char* argv[])
{
	Test().run();
	return 0;
}
