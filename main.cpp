#include "app.h"
#include "drawable.h"
#include "animatedSprite.h"
#include <Box2D/Box2D.h>
#include <vector>
#include <SDL2/SDL2_gfxPrimitives.h>

const int w(800), h(600);
const float scale(30);

b2World *world;

class Ground : public Sprite
{
	b2Body * body;

public:
    Ground() : Sprite(40, h-70)
    {
    	setSize(w-80, 5);
        b2BodyDef body_def;
        SDL_Point center(getCenter());
        body_def.position.Set(center.x/scale, center.y/scale);
        body = world->CreateBody(&body_def);
        b2PolygonShape body_s;
        body_s.SetAsBox(0.5*m_w/scale, 0.5*m_h/scale);
        body->CreateFixture(&body_s, 0.f);
    }
    void draw(SDL_Renderer* renderer)
    {
    	SDL_SetRenderDrawColor(renderer, 150, 241, 60, 255);
    	SDL_Rect && r = getBox();
    	SDL_RenderDrawRect(renderer, &r);
	}
};

class Box : public AnimatedSprite
{
	b2Body * body;

public:
	Box(int x, int y) : AnimatedSprite(x, y, 20, AnimatedSprite::using_spritesheet)
	{
		setResources("img.png", 11);
		setSize(32, 32);
		zoom(2, 1);
		b2BodyDef body_def;
		body_def.type = b2_dynamicBody;
        SDL_Point center(getCenter());
        body_def.position.Set(center.x/scale, center.y/scale);
        body = world->CreateBody(&body_def);
        b2PolygonShape body_s;
        body_s.SetAsBox(0.5*m_w/scale, 0.5*m_h/scale);
        b2FixtureDef body_fix_def;
        body_fix_def.shape = &body_s;
        body_fix_def.density =  0.5;
        body_fix_def.friction = 0.3;
        body_fix_def.restitution = 0.5;
        body->CreateFixture(&body_fix_def);
	}
	~Box()
	{ world->DestroyBody(body); }
	void update()
	{
		AnimatedSprite::update();
		b2Vec2 cur_pos(body->GetPosition());
        setCenter(scale*cur_pos.x, scale*cur_pos.y);
		// std::cout << "body position : " << cur_pos.x << ", " << cur_pos.y << std::endl;
		// std::cout << "sprite position : " << getCenter().x << ", " << getCenter().y << std::endl;
        setAngle(body->GetAngle()*180/b2_pi);
	}
};

class Test : public App
{
	std::vector<Sprite*> sprites;
public:
	Test() :
		App("test", w, h)
	{
		world = new b2World(b2Vec2(0, 10.f));
		m_camera = new Camera(Camera::center_following);
		m_camera->setBox(0, 0, w, h);
		sprites.push_back(new Ground);
	}
	~Test()
	{
		for (auto sprite : sprites)
			delete sprite;
		delete world;
	}
	void manage_events()
	{
        App::manage_events();
        if (m_event.type == SDL_MOUSEBUTTONUP)
			sprites.push_back(new Box(m_event.button.x, m_event.button.y));
		if (m_event.type == SDL_KEYDOWN and m_event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			pause();
	}
	void update()
	{
		world->Step(1/120.f, 3, 2);
		std::vector<Sprite*> lSprite(sprites);
		for (int i=0; i<(int)lSprite.size(); ++i)
		{
			Sprite* sprite(lSprite[i]);
            SDL_Rect box(sprite->getBox()), win = { 0, 0, w, h };
			if (SDL_HasIntersection(&box, &win))
				sprite->update();
			else
			{
				delete sprite;
				sprites.erase(sprites.begin()+i);
			}
		}
	}
	void render()
	{
		cleanTarget();
		for (auto sprite : sprites)
			draw(sprite);
	}
};

int main(int argc, char* argv[])
{
	Test().run();
	return 0;
}
