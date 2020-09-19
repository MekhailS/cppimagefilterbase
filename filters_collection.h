//
// Created by Mikhail on 19.09.2020.
//

#ifndef FILTERS_FILTERS_COLLECTION_H
#define FILTERS_FILTERS_COLLECTION_H

#include "definitions.h"
#include "filters.h"

class FiltersCollection {

    std::unordered_map<std::string, FilterAbstract*> filtersMap =
            {
            { "Red" , new FilterRed()},
            {"BlackWhite", new FilterBlackWhite()},
            {"Threshold", new FilterThreshold()}
                                                        };

public:
    //FiltersCollection();
    FilterAbstract* getFilter(std::string);
    ~FiltersCollection();
};


#endif //FILTERS_FILTERS_COLLECTION_H
