#ifndef APP_H
#define APP_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

/// Template
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
    void getWindowSize(int*, int*);

    static bool keyPressed(SDL_Scancode);
    /* param : 1=left, 2=middle, 3=right */
    static bool buttonPressed(int);
    static void mousePosition(int*, int*);

protected:
    virtual void manage_events();
    virtual void update();
    virtual void draw();
    void cleanTarget();

    // current app state
    bool m_paused, m_running;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Event m_event;

};

#endif
