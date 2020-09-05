#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <iostream>
#include <vector>
#include "timer.h"
#include "sprite.h"
#include "camera.h"
#include "drawable.h"

class AnimatedSprite : public Sprite
{
public:
    enum Mode { using_spritesheet, separated_sprites };

    AnimatedSprite(int, int, int, Mode);
    ~AnimatedSprite();

    void setResources(const std::string&, const std::vector<SDL_Rect>&);
    void setResources(SDL_Texture*, const std::vector<SDL_Rect>&);
    void setResources(const std::string&, int);
    void setResources(SDL_Texture*, int);
    void setResources(const std::vector<std::string>&);
    void setResources(const std::vector<SDL_Texture*>&);

    void setTexture(SDL_Texture*);
    void setTexture(const std::string&);

    void update();

    void draw(SDL_Renderer*, Camera*);

protected:
    Chrono m_timer;

    int m_frame_index;
    Mode m_mode;

    std::vector<SDL_Rect> m_srcrects;
    std::vector<SDL_Texture*> m_image_textures;

};
#endif // ANIMATED_SPRITE_H
