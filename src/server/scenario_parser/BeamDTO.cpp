#include <string>
#include "BeamDTO.h"

using std::string;

BeamDTO::BeamDTO(int id, string image, float x, float y, int length, int angle) : id(id), image(image), x(x), y(y), length(length), angle(angle) {}

int BeamDTO::get_id() {
    return id;
}

string BeamDTO::get_image() {
    return image;
}

float BeamDTO::get_x() {
    return x;
}

float BeamDTO::get_y() {
    return y;
}

int BeamDTO::get_length() {
    return length;
}

int BeamDTO::get_angle() {
    return angle;
}
