#ifndef __FONTFACTORY__
#define __FONTFACTORY__

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#define FONT_ASSET "BebasNeueRegular.ttf"

class FontFactory {
public:
    FontFactory();
    TTF_Font* get_big_font();
    TTF_Font* get_small_font();
    SDL_Texture* get_texture_big_font(const char* text, SDL_Color, \
                                      SDL_Renderer* renderer);
    SDL_Texture* get_texture_small_font(const char* text, SDL_Color, \
                                        SDL_Renderer* renderer);
    ~FontFactory();

private:
    TTF_Font* big_font;
    TTF_Font* small_font;
};

#endif
