#include <iostream>
#include <vector>
#include <map>
#include <gdspy.h>


std::map<std::pair<int, int>, std::vector<gdspy::Polygon*>> GdsReader(const std::string& filename) {
    gdspy::GdsLibrary lib(filename);
    gdspy::Cell* main_cell = lib.top_level()[0];
    std::map<std::pair<int, int>, std::vector<gdspy::Polygon*>> pol_dict = main_cell->get_polygons(true);
    std::vector<gdspy::Polygon*> polygons = pol_dict[std::make_pair(layer, datatype)];
    return polygons;
}


