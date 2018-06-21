#ifndef __TEXTUREFACTORY__
#define __TEXTUREFACTORY__

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using std::string;
using std::map;

#define WORM_R_ASSET "worm_r.png"
#define WORM_L_ASSET "worm_l.png"
#define BEAM_ASSET "grdl0.png"
#define DYNAMITE_ASSET "dynamite.png"
#define RADIOCONTROLLED_ASSET "radiocontrolled.png"
#define START_TURN_ASSET "startTurn.png"
#define FINISH_TURN_ASSET "finishTurn.png"
#define GRAVE_ASSET "grave.png"

class TextureFactory {
public:
    TextureFactory() = default;
    void init(SDL_Renderer* renderer);
    SDL_Texture* get_texture_by_name(string name);
    SDL_Texture* load_texture(const string& filename, SDL_Renderer* renderer);
    ~TextureFactory();

private:
    map<string, SDL_Texture*> textures;
};

#endif
