#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "YamlParser.h"
#include "ScenarioDTO.h"
#include "WormDTO.h"
#include "BeamDTO.h"

using std::string;
using std::vector;
using std::map;

int main() {
    YamlParser parser;

    map<string, string> config = parser.load_config("config.yaml");
    std::cout << "clave: " << config.at("clave") << std::endl;

    ScenarioDTO scenario = parser.load_scenario("scenario.yaml");
    std::cout << "width: " << scenario.get_width() << std::endl;

    vector<WormDTO> worms = scenario.get_worms();
    for (WormDTO worm : worms){
        std::cout << "Gusano " << worm.get_id() << std::endl;
        std::cout << "x: " << worm.get_x() << std::endl;
    }
    return 0;
}