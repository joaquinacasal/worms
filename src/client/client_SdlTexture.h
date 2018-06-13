#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__

#include <string>
#include <SDL2/SDL_image.h>

using std::string;

class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

class SdlTexture {
public:
    SdlTexture(const string& filename, const SdlWindow& window, int x, int y, int width, int heigth);
    int render() const;
    void set_position(int x, int y);
    ~SdlTexture();
private:
    SDL_Texture* loadTexture(const std::string& filename);
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect position;
};

#endif
