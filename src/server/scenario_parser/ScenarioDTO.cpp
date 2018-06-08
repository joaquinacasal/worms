#include <string>
#include <vector>
#include "WormDTO.h"
#include "BeamDTO.h"
#include "ScenarioDTO.h"

using std::string;
using std::vector;

ScenarioDTO::ScenarioDTO(string background, int heigth, int width, vector<WormDTO> worms, vector<BeamDTO> beams) :
                    background(background), height(heigth), width(width), worms(worms), beams(beams) {}

string ScenarioDTO::get_background() {
    return background;
}

int ScenarioDTO::get_height() {
    return height;
}

int ScenarioDTO::get_width() {
    return width;
}

vector<WormDTO> ScenarioDTO::get_worms() {
    return worms;
}

vector<BeamDTO> ScenarioDTO::get_beams() {
    return beams;
}
