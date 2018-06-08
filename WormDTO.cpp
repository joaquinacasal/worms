#include <string>
#include "WormDTO.h"

using std::string;

WormDTO::WormDTO(int id, string image, int x, int y): id(id), image(image), x(x), y(y) {}

int WormDTO::get_id() {
    return id;
}

string WormDTO::get_image() {
    return image;
}

int WormDTO::get_x() {
    return x;
}

int WormDTO::get_y() {
    return y;
}
