#include "client_ColorsFactory.h"
#include <string>
#include <map>
#include <SDL2/SDL.h>

using std::string;
using std::map;

ColorsFactory::ColorsFactory(){
    colors["red"] = {255, 0, 0, 0};
    colors["blue"] = {0, 0, 255, 0};
    colors["green"] = {0, 255, 0, 0};
    colors["yellow"] = {255, 255, 0, 0};
    colors["purple"] = {255, 0, 255, 0};
    colors["light_blue"] = {0, 255, 255, 0};
    colors["brown"] = {102, 51, 0, 0};
    colors["orange"] = {255, 102, 0, 0};
    colors["pink"] = {255, 153, 255, 0};
    colors["black"] = {0, 0, 0, 0};
    colors["white"] = {255, 255, 255, 0};

    int counter = 0;
    for (auto it = colors.begin(); it != colors.end(); ++it, counter++){
        id_mapper[counter] = it->first;
    }
}

SDL_Color ColorsFactory::get_color_by_id(int id){
    string color = id_mapper[id % id_mapper.size()];
    return get_color_by_name(color);
}

SDL_Color ColorsFactory::get_color_by_name(string color){
    return colors[color];
}
