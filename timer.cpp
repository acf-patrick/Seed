#include "timer.h"
#include <SDL2/SDL.h>

Uint32 getTicks()
{
    Uint32 ret(SDL_GetTicks());
    if (!ret)
        return 1;
    return ret;
}

Timer::Timer() { restart(); }

int Timer::getElapsedMilliseconds(){ return (SDL_GetTicks() - start_time + 1); }
float Timer::getElapsedSeconds(){ return getElapsedMilliseconds()/1000.; }

void Timer::restart() { start_time = SDL_GetTicks(); }

Chrono::Chrono(int remaining_time):
    remaining(remaining_time)
{}
void Chrono::restart(int r_time)
{
    if (r_time > 0)
        remaining = r_time;
    Timer::restart();
}
bool Chrono::out() { return (getElapsedMilliseconds() >= remaining); }
