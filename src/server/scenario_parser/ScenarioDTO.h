#ifndef PARSER_SCENARIODTO_H
#define PARSER_SCENARIODTO_H

#include <string>
#include <vector>
#include "WormDTO.h"
#include "BeamDTO.h"

using std::string;
using std::vector;

class ScenarioDTO {

private:
    string background;
    int height;
    int width;
    vector<WormDTO> worms;
    vector<BeamDTO> beams;

public:
    ScenarioDTO(string background, int height, int width, vector<WormDTO> worms, vector<BeamDTO> beams) ;
    string get_background();
    int get_height();
    int get_width();
    vector<WormDTO> get_worms();
    vector<BeamDTO> get_beams();

};


#endif //PARSER_SCENARIODTO_H
