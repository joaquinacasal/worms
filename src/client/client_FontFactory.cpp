#include "client_FontFactory.h"
#include "client_SdlException.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include <string>
#include "config.h"
#include <iostream>

using std::string;

FontFactory::FontFactory(){
    if(TTF_Init() < 0)
        throw SdlException("No se pudo inicializar la librería TTF", TTF_GetError());
    string font = string(ASSETS_FOLDER) + string(FONT_ASSET);
    this->big_font = TTF_OpenFont(font.c_str(), 24);
    this->small_font = TTF_OpenFont(font.c_str(), 18);
}

TTF_Font* FontFactory::get_big_font(){
    return big_font;
}

TTF_Font* FontFactory::get_small_font(){
    return small_font;
}

SDL_Texture* FontFactory::get_texture_big_font(const char* text, SDL_Color color, SDL_Renderer* renderer){
    SDL_Surface* surface = TTF_RenderText_Solid(big_font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* FontFactory::get_texture_small_font(const char* text, SDL_Color color, SDL_Renderer* renderer){
    SDL_Surface* surface = TTF_RenderText_Solid(small_font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

FontFactory::~FontFactory(){
    TTF_CloseFont(big_font);
    TTF_CloseFont(small_font);
}
