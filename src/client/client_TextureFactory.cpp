#include "client_TextureFactory.h"
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "client_SdlException.h"
#include "config.h"

using std::string;
using std::map;

void TextureFactory::init(SDL_Renderer* renderer){
    textures["worm_resting"] = load_texture(string(ASSETS_FOLDER) + string(WORM_RESTING_ASSET), renderer);
    textures["worm_walking"] = load_texture(string(ASSETS_FOLDER) + string(WORM_WALKING_ASSET), renderer);
    textures["worm_jumping"] = load_texture(string(ASSETS_FOLDER) + string(WORM_JUMPING_ASSET), renderer);
    textures["beam"] = load_texture(string(ASSETS_FOLDER) + string(BEAM_ASSET), renderer);
    textures["start_turn"] = load_texture(string(ASSETS_FOLDER) + string(START_TURN_ASSET), renderer);
    textures["end_turn"] = load_texture(string(ASSETS_FOLDER) + string(FINISH_TURN_ASSET), renderer);
    textures["dynamite"] = load_texture(string(ASSETS_FOLDER) + string(DYNAMITE_ASSET), renderer);
    textures["radioControlled"] = load_texture(string(ASSETS_FOLDER) + string(RADIOCONTROLLED_ASSET), renderer);
    textures["grave"] = load_texture(string(ASSETS_FOLDER) + string(GRAVE_ASSET), renderer);
    textures["you_win"] = load_texture(string(ASSETS_FOLDER) + string(YOU_WIN_ASSET), renderer);
    textures["water"] = load_texture(string(ASSETS_FOLDER) + string(WATER_ASSET), renderer);
}

SDL_Texture* TextureFactory::get_texture_by_name(string name){
    return textures[name];
}

SDL_Texture* TextureFactory::load_texture(const string& filename, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename.c_str());
    if (!texture) {
        throw SdlException("Error al cargar la textura", SDL_GetError());
    }
    return texture;
}

TextureFactory::~TextureFactory(){
    for (auto it = textures.begin(); it != textures.end(); ++it){
        SDL_DestroyTexture(it->second);
    }
}
