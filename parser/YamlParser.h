#ifndef PARSER_YAMLPARSER_H
#define PARSER_YAMLPARSER_H

#include "ScenarioDTO.h"
#include "WormDTO.h"
#include "BeamDTO.h"
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class YamlParser {
public:
    YamlParser() = default;
    ScenarioDTO load_scenario(string filename);
    map<string, string> load_config(string filename);
};


#endif //PARSER_YAMLPARSER_H
