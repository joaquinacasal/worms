#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__

#include <string>
#include <SDL2/SDL_image.h>
#include "client_Area.h"

using std::string;

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

class SdlTexture {
public:
    SdlTexture(SDL_Texture* texture, const SdlWindow& window, Area position);
    int render() const;
    int render(int angle) const;
    void set_position(int x, int y);
    ~SdlTexture() = default;
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    Area position;
};

#endif
