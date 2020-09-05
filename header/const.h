#ifndef CONST_H
#define CONST_H

#include <SDL2/SDL.h>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define RMASK 0xff000000
#define GMASK 0x00ff0000
#define BMASK 0x0000ff00
#define AMASK 0x000000ff
#else
#define AMASK 0xff000000
#define BMASK 0x00ff0000
#define GMASK 0x0000ff00
#define RMASK 0x000000ff
#endif

#endif // CONST_H
