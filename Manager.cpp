//
// Created by Mikhail on 19.09.2020.
//

#include "Manager.h"
#include <fstream>
#include <sstream>


filterName_AreaAsArr Manager::parseLine(std::string &line)
{
    std::string filterName;
    std::array<int, 4> boundaries;

    std::stringstream s(line);

    s >> filterName;

    for (auto& el : boundaries)
        s >> el;

    return filterName_AreaAsArr (filterName, boundaries);
}

void Manager::launch(char *fileConfigName, char *fileInputName, char *fileOutputName)
{
    png_toolkit pic;
    pic.load(fileInputName);

    image_data img = pic.getPixelData();

    std::ifstream cfgFile(fileConfigName);

    std::string line;
    while(std::getline(cfgFile, line)){
        filterName_AreaAsArr filterName_boundaries = parseLine(line);

        auto filterName = filterName_boundaries.first;
        auto boundaries = filterName_boundaries.second;

        FilterAbstract *filter = filters.getFilter(filterName);
        if (filter != nullptr){
            AreaRect area;
            area.fitToImageByFraction(img, {boundaries[0], boundaries[1]},
                                      {boundaries[2], boundaries[3]});
            filter->apply(img, area);
        }
    }

    pic.save(fileOutputName);
    return;
}