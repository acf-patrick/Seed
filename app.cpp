#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "app.h"

App* App::instance(NULL);

App::App(std::string app_title, int w, int h):
    m_paused(false), m_running(true),
    m_camera(nullptr)
{
    instance = this;

    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to load SDL library : " << SDL_GetError() << std::endl;
        exit(1);
    }

    m_window = SDL_CreateWindow(app_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if (!m_window)
    {
        std::cerr << "Failed to open main m_window : " << SDL_GetError() << std::endl;
        exit(1);
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_window)
    {
        std::cerr << "Failed to create render context : " << SDL_GetError() << std::endl;
        exit(1);
    }

    m_signals = new SignalManager;
    m_texture_manager = new TextureManager;
}

App::~App()
{
    delete m_signals;
    delete m_texture_manager;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    TTF_Quit();
    SDL_Quit();
}

void App::run()
{
    while (m_running)
    {
        while (SDL_PollEvent(&m_event))
            manage_events();
        if (!m_paused)
            update();
        render();
        SDL_RenderPresent(m_renderer);
    }
}

void App::update()
{
    if (m_camera)
        m_camera->update();
}

void App::render()
{
    // overload
}

void App::manage_events()
{
    switch (m_event.type)
    {
    case SDL_QUIT:
        end();
        break;
    case SDL_KEYDOWN:
        keyPressed(m_event.key.keysym.scancode);
        break;
    case SDL_KEYUP:
        keyReleased(m_event.key.keysym.scancode);
        break;
    case SDL_MOUSEBUTTONDOWN:
        buttonPressed(m_event.button.button);
        break;
    case SDL_MOUSEBUTTONUP:
        buttonReleased(m_event.button.button);
        break;
    default: ;
    }
}

void App::pause() { m_paused = !m_paused; }
void App::end()
{
    // if (confirm("Quitter?"))
        m_running = false;
}

void App::getWindowSize(int* w, int* h)
{ SDL_GetWindowSize(instance->m_window, w, h); }

SDL_Window* App::getWindow()
{ return m_window; }

SDL_Renderer* App::getRenderer()
{ return m_renderer; }

bool App::getKeyPressed(SDL_Scancode key)
{ return SDL_GetKeyboardState(NULL)[key]; }

bool App::getButtonPressed(int index)
{ return SDL_GetMouseState(0, 0) & SDL_BUTTON(index); }

void App::getMousePosition(int* x, int* y)
{ SDL_GetMouseState(x, y); }

void App::cleanTarget()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void App::draw(Drawable * drawable)
{
    if (m_camera)
        m_camera->draw(dynamic_cast<Sprite*> (drawable));
    else
        drawable->draw(m_renderer);
}

void App::keyPressed(SDL_Scancode key)
{
    // overload
}

void App::keyReleased(SDL_Scancode key)
{
    // overload
}

void App::buttonReleased(Uint8 button)
{
    // overload
}

void App::buttonPressed(Uint8 button)
{
    // overload
}
