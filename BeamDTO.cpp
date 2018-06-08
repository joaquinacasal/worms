#include <string>
#include "BeamDTO.h"

using std::string;

BeamDTO::BeamDTO(int id, string image, int x, int y, int length, int angle) : id(id), image(image), x(x), y(y), length(length), angle(angle) {}

int BeamDTO::get_id() {
    return id;
}

string BeamDTO::get_image() {
    return image;
}

int BeamDTO::get_x() {
    return x;
}

int BeamDTO::get_y() {
    return y;
}

int BeamDTO::get_length() {
    return length;
}

int BeamDTO::get_angle() {
    return angle;
}
