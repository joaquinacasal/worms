#ifndef PARSER_BEAMDTO_H
#define PARSER_BEAMDTO_H

#include <string>

using std::string;

class BeamDTO {
private:
    int id;
    string image;
    float x;
    float y;
    int length;
    int angle;

public:
    BeamDTO(int id, string image, float x, float y, int length, int angle);
    int get_id();
    string get_image();
    float get_x();
    float get_y();
    int get_length();
    int get_angle();
};


#endif //PARSER_BEAMDTO_H
