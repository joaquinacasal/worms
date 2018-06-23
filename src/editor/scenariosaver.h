#ifndef SCENARIO_H
#define SCENARIO_H

#include <string>
#include <vector>
#include <map>
#include "draglabel.h"
#include <QList>

using std::string;
using std::vector;
using std::map;

#define PIXEL_METER_CONVERSION 10

class ScenarioSaver
{
private:
    map<string, string> data;

    bool check_intersections(QList<DragLabel*>& worms_labels, QList<DragLabel*>& beams_labels);

public:
    ScenarioSaver() = default;
    int save_scenario(QList<DragLabel*>& worms_labels, QList<DragLabel*>& beams_labels, string filename);
    void load_scenario(string filename, int& height, int& width, string& background,
                                vector<map<string, string>>& worms, vector<map<string, string>>& beams);
    void set_size(int width, int height);
    void set_background(string filename);
    int get_width();
    int get_height();
    string get_background();
    float pixels_to_meters(float pixels);
    float meters_to_pixels(float meters);
    ~ScenarioSaver() = default;
};

#endif // BEAMLABEL_H


