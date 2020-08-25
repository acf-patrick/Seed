#include "app.h"
#include <SDL2/SDL2_gfxPrimitives.h>

class Test : public App
{
public:
	Test() : App("test", 600, 600)
	{}

	void draw()
	{
		cleanTarget();
		int w, h;
		getWindowSize(&w, &h);
		filledCircleColor(renderer, w/2, h/2, h/3, 0xffffffff);
	}
};

int main(int argc, char* argv[])
{
	Test().run();
	return 0;
}
