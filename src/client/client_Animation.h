#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <string>
#include <SDL2/SDL_image.h>
#include "client_Area.h"

using std::string;

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;

class Animation {
public:
    Animation(SDL_Texture* texture, const SdlWindow& window, \
              Area position, int frames);
    void render(int angle = 0, SDL_RendererFlip flip_flags = SDL_FLIP_NONE);
    void set_position(int x, int y);
    void set_texture(SDL_Texture* texture, int frames);
    ~Animation() = default;
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    Area position;
    Area current_frame;
    int frame_counter;
    int frame_counter_counter;
    int frames;
    float frame_height;
};

#endif
