//
// Created by Mikhail on 19.09.2020.
//

#include "filters_collection.h"


/*FiltersCollection::FiltersCollection()
{
    filtersMap["Red"] = new FilterRed();
    filtersMap["BlackWhite"] = new FilterBlackWhite();
    filtersMap["Threshold"] = new FilterThreshold();
}*/

FilterAbstract* FiltersCollection::getFilter(std::string filterName)
{
    if (filtersMap.find(filterName) != filtersMap.end()) {
        return filtersMap.find(filterName)->second;
    }
    return nullptr;
}

FiltersCollection::~FiltersCollection()
{
    for (auto& x : filtersMap)
        delete x.second;
}