#ifndef PARSER_BEAMDTO_H
#define PARSER_BEAMDTO_H

#include <string>

using std::string;

class BeamDTO {
private:
    int id;
    string image;
    int x;
    int y;
    int length;
    int angle;

public:
    BeamDTO(int id, string image, int x, int y, int length, int angle);
    int get_id();
    string get_image();
    int get_x();
    int get_y();
    int get_length();
    int get_angle();
};


#endif //PARSER_BEAMDTO_H
