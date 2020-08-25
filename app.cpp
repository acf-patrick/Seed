#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "app.h"

App* App::instance(NULL);

App::App(std::string app_title, int w, int h):
    paused(false), running(true)
{
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to load SDL library : " << SDL_GetError();
        exit(1);
    }

    window = SDL_CreateWindow(app_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Failed to open main window : " << SDL_GetError();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!window)
    {
        std::cerr << "Failed to create render context : " << SDL_GetError();
        exit(1);
    }
}

App::~App()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void App::run()
{
    while (running)
    {
        while (SDL_PollEvent(&event))
            manage_events();
        if (!paused)
            update();
        draw();
        SDL_RenderPresent(renderer);
    }
}

void App::update()
{
    //override
}

void App::draw()
{
    //override
}

void App::manage_events()
{
    if (event.type == SDL_QUIT)
        end();
}

void App::pause() { paused = !paused; }
void App::end()
{
    // if (confirm("Quitter?"))
        running = false;
}

void App::getWindowSize(int* w, int* h)
{ SDL_GetWindowSize(window, w, h); }

SDL_Window* App::getWindow()
{ return window; }

SDL_Renderer* App::getRenderer()
{ return renderer; }

bool App::keyPressed(SDL_Scancode key)
{ return SDL_GetKeyboardState(NULL)[key]; }

bool App::buttonPressed(int index)
{ return SDL_GetMouseState(0, 0) & SDL_BUTTON(index); }

void App::mousePosition(int* x, int* y)
{ SDL_GetMouseState(x, y); }

void App::cleanTarget()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}
