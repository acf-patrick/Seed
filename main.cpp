#include "app.h"
#include "sprite.h"

class Test : public App
{
public:
	Sprite sprite;

	Test() : App("test", 600, 600), sprite(0, 0, "img.png")
	{ }

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
