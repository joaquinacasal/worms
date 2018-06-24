#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__

#include <string>
#include <SDL2/SDL_image.h>
#include "client_Area.h"
#include "client_Camera.h"

using std::string;

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;

class SdlTexture {
public:
    SdlTexture(SDL_Texture* texture, const SdlWindow& window, Area position);
    int render(Camera& camera, int angle = 0) const;
    int render(int angle = 0) const;
    void set_position(int x, int y);
    ~SdlTexture() = default;
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    Area position;

    int render(SDL_Rect position_rec, int angle = 0) const;
};

#endif
