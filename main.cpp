#include "header/app.h"
#include "header/drawable.h"
#include "header/animatedSprite.h"
#include <Box2D/Box2D.h>
#include <vector>
#include <map>
#include <cmath>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "header/const.h"

const int w(800), h(600);
const float scale(30);

b2World *world;

class Ground : public Sprite
{
    b2Body * body;

public:
    Ground() : Sprite(40, h-70)
    {
        setSize(w-80, 1);
        b2BodyDef body_def;
        SDL_Point center(getCenter());
        body_def.position.Set(center.x/scale, center.y/scale);
        body = world->CreateBody(&body_def);
        b2EdgeShape body_s;
        body_s.Set(b2Vec2(-0.5*m_w/scale, 0), b2Vec2((0.5*m_w)/scale, 0));
        body->CreateFixture(&body_s, 0.f);
    }
    void draw(SDL_Renderer* renderer, Camera * camera)
    {
        SDL_SetRenderDrawColor(renderer, 150, 241, 60, 255);
        SDL_Rect && c = camera->getBox();
        SDL_Rect && r = getBox();
        r.x -= c.x;
        r.y -= c.y;
        SDL_RenderDrawRect(renderer, &r);
    }
};

class Circle : public Sprite
{
    b2Body * body;

public:
    Circle(int x, int y)
    {
        setTexture("image/circle.png");
        setSize(40, 40);
        defineSourceRect(0, 0, m_w, m_h);
        setCenter(x, y);
        b2BodyDef body_def;
        body_def.position.Set(x/scale, y/scale);
        body_def.type = b2_dynamicBody;
        body = world->CreateBody(&body_def);
        b2FixtureDef fix_def;
        b2CircleShape shape;
        shape.m_radius = 0.5*m_w/scale;
        fix_def.density = 0.2;
        fix_def.restitution = 0.25;
        fix_def.friction = 0.1;
        fix_def.shape = &shape;
        body->CreateFixture(&fix_def);
    }
    void update()
    {
        b2Vec2 pos(body->GetPosition());
        setCenter(scale*pos.x, scale*pos.y);
        setAngle(180*body->GetAngle()/b2_pi);
    }
};

class Box : public Sprite
{
public:
    b2Body * body;
    Box(int x, int y) : Sprite(x, y)
    {
        int w, h;
        w = h = 32;
        SDL_Surface* box = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
                                                0x00ff0000, 0x0000ff00,
                                                0x000000ff, 0xff000000);
        SDL_FillRect(box, NULL, 0xffffffff);
        SDL_Rect inner = { 2, 2, w-4, w-4 };
        SDL_FillRect(box, &inner, 0x0);
        setTexture(SDL_CreateTextureFromSurface(App::instance->getRenderer(), box));
        setSize(w, h);
        defineSourceRect(0, 0, m_w, m_h);
        SDL_FreeSurface(box);
        SDL_Point center(getCenter());
        b2BodyDef body_def;
        body_def.position.Set(center.x/scale, center.y/scale);
        body_def.type = b2_dynamicBody;
        body = world->CreateBody(&body_def);
        b2PolygonShape body_s;
        body_s.SetAsBox(0.5*m_w/scale, 0.5*m_h/scale);
        b2FixtureDef body_fix_def;
        body_fix_def.shape = &body_s;
        body_fix_def.density = 0.25;
        body_fix_def.friction = 0.25;
        body_fix_def.restitution = 0.3;
        body->CreateFixture(&body_fix_def);
    }
    void update()
    {
        b2Vec2 cur_pos(body->GetPosition());
        setCenter(scale*cur_pos.x, scale*cur_pos.y);
        setAngle(body->GetAngle()*180/b2_pi);
    }
};

class MaskDude : public AnimatedSprite
{
    b2Body * body;
    Box box;

public:
    MaskDude(int x, int y) : AnimatedSprite(x, y, 20, AnimatedSprite::using_spritesheet), box(x, y)
    {
        setResources("image/img.png", 11);
        setSize(32, 32);
        body = box.body;
    }
    ~MaskDude()
    {
        world->DestroyBody(body);
    }
    void update()
    {
        box.update();
        AnimatedSprite::update();
        b2Vec2 cur_pos(body->GetPosition());
        setCenter(scale*cur_pos.x, scale*cur_pos.y);
        setAngle(body->GetAngle()*180/b2_pi);
    }
    void draw(SDL_Renderer* renderer, Camera * camera)
    {
        AnimatedSprite::draw(renderer, camera);
        box.draw(renderer, camera);
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
    void buttonReleased(Uint8 button)
    {
        int x, y;
        getMousePosition(&x, &y);
        if (button == SDL_BUTTON_LEFT)
            sprites.push_back(new MaskDude(x, y));
        else if (button == SDL_BUTTON_RIGHT)
            sprites.push_back(new Circle(x, y));
    }
    void update()
    {
        App::update();
        std::map<SDL_Scancode, SDL_Point> bind =
        {
            { SDL_SCANCODE_UP, {  0,  1 } },
            { SDL_SCANCODE_DOWN, {  0, -1 } },
            { SDL_SCANCODE_LEFT, {  1,  0 } },
            { SDL_SCANCODE_RIGHT, { -1,  0 } }
        };
        for (auto pair : bind)
            if (getKeyPressed(pair.first))
                m_camera->move(pair.second.x, pair.second.y);
        world->Step(1/120.f, 3, 2);
        std::vector<Sprite*> lSprite(sprites);
        for (int i=0; i<(int)lSprite.size(); ++i)
        {
            Sprite* sprite(lSprite[i]);
            SDL_Rect &&box = sprite->getBox(), win = { 0, 0, w, h };
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
