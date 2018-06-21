#ifndef __COLORSFACTORY__
#define __COLORSFACTORY__

#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

using std::string;
using std::vector;
using std::map;

class ColorsFactory {
public:
    ColorsFactory();
    SDL_Color get_color_by_id(int id);
    SDL_Color get_color_by_name(string color);
    ~ColorsFactory() = default;

private:
    map<string, SDL_Color> colors;
    map<int, string> id_mapper;
};

#endif
