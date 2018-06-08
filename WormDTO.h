#ifndef PARSER_WORMDTO_H
#define PARSER_WORMDTO_H

#include <string>

using std::string;

class WormDTO {
private:
    int id;
    string image;
    int x;
    int y;

public:
    WormDTO(int id, string image, int x, int y);
    int get_id();
    string get_image();
    int get_x();
    int get_y();
};


#endif //PARSER_WORMDTO_H
