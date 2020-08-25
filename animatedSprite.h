#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <iostream>
#include "sprite.h"


class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(int, int, const std::string&);
};

#endif // ANIMATED_SPRITE_H
