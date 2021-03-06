#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "drawable.h"
#include "texture.h"
#include "camera.h"
#include "signal.h"

/// template for the main class
class App
{
public:
    // singleton class
    static App* instance;

    App(std::string app_title = "App", int w = 480, int h = 360);
    virtual ~App();

    void run();
    void pause();
    void end();

    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();

    void draw(Drawable*);

    static bool getKeyPressed(SDL_Scancode);
    /* param : 1=left, 2=middle, 3=right */
    static bool getButtonPressed(int);
    static void getMousePosition(int*, int*);
    static void getWindowSize(int*, int*);
	static std::pair<SDL_Renderer*, Camera*> getRenderingComponent();

protected:
    virtual void manage_events();
    virtual void keyPressed(SDL_Scancode);
    virtual void keyReleased(SDL_Scancode);
    virtual void buttonPressed(Uint8);
    virtual void buttonReleased(Uint8);
    virtual void update();
    virtual void render();
    void cleanTarget();

    // current app state
    bool m_paused, m_running;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Event m_event;

    Camera* m_camera;
    SignalManager* m_signals;
    TextureManager* m_texture_manager;
};

#endif
