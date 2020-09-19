//
// Created by Mikhail on 19.09.2020.
//

#ifndef FILTERS_MANAGER_H
#define FILTERS_MANAGER_H

#include "definitions.h"
#include "filters_collection.h"

class Manager {
    FiltersCollection filters;

    filterName_AreaAsArr parseLine(std::string &line);

public:
    void launch(char* fileConfigName, char* fileInputName, char* fileOutputName);
};


#endif //FILTERS_MANAGER_H
