#include "app.h"
#include "object.h"
#include "drawable.h"

class Sprite : public Object, public Drawable
{
public:
	Sprite() : Object()
	{
		m_texture = loadTexture("img.png");
		SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
	}
	void draw(SDL_Renderer* renderer) const
	{
        SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
	}
};

class Test : public App
{
public:
	Sprite sprite;

	Test() : App("test", 600, 600)
	{}

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
