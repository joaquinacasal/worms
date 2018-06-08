#include <string>
#include <vector>
#include <map>
#include "yaml-cpp/yaml.h"
#include "YamlParser.h"
#include "ScenarioDTO.h"
#include "WormDTO.h"
#include "BeamDTO.h"

map<string, string> YamlParser::load_config(string filename) {
    YAML::Node config_file = YAML::LoadFile(filename);
    map<string, string> config = config_file.as<map<string, string>>();
    return config;
}

ScenarioDTO YamlParser::load_scenario(string filename) {
    YAML::Node scenario_file = YAML::LoadFile(filename);

    map<string, string> scenario = scenario_file["scenario"].as<map<string, string>>();
    int heigth = std::stoi(scenario.at("heigth"));
    int width = std::stoi(scenario.at("width"));
    string background = scenario.at("background");

    vector<map<string, string>> worms = scenario_file["worms"].as<vector<map<string, string>>>();
    vector<WormDTO> wormsDTOs;
    for (map<string, string> worm : worms){
        int id = std::stoi(worm.at("id"));
        int x = std::stoi(worm.at("x"));
        int y = std::stoi(worm.at("y"));
        string image = worm.at("image");
        WormDTO wormDTO(id, image, x, y);
        wormsDTOs.push_back(wormDTO);
    }

    vector<map<string, string>> beams = scenario_file["beams"].as<vector<map<string, string>>>();
    vector<BeamDTO> beamsDTOs;
    for (map<string, string> beam : beams){
        int id = std::stoi(beam.at("id"));
        int x = std::stoi(beam.at("x"));
        int y = std::stoi(beam.at("y"));
        string image = beam.at("image");
        int length = std::stoi(beam.at("length"));
        int angle = std::stoi(beam.at("angle"));
        BeamDTO beamDTO(id, image, x, y, length, angle);
        beamsDTOs.push_back(beamDTO);
    }

    ScenarioDTO scenarioDTO(background, heigth, width, wormsDTOs, beamsDTOs);
    return scenarioDTO;
}

