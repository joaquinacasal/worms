#ifndef PARSER_WORMDTO_H
#define PARSER_WORMDTO_H

#include <string>

using std::string;

class WormDTO {
private:
    int id;
    string image;
    float x;
    float y;

public:
    WormDTO(int id, string image, float x, float y);
    int get_id();
    string get_image();
    float get_x();
    float get_y();
};


#endif //PARSER_WORMDTO_H
