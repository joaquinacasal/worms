#include <string>
#include "WormDTO.h"

using std::string;

WormDTO::WormDTO(int id, string image, float x, float y): id(id), image(image), x(x), y(y) {}

int WormDTO::get_id() {
    return id;
}

string WormDTO::get_image() {
    return image;
}

float WormDTO::get_x() {
    return x;
}

float WormDTO::get_y() {
    return y;
}
