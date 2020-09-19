//
// Created by MikhailS on 17.09.2020.
//


#ifndef FILTERS_DEFINITIONS_H
#define FILTERS_DEFINITIONS_H

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "stb_image.h"

typedef std::array<stbi_uc, 3> rgb;
typedef std::pair<rgb, bool> rgb_errorFlag;
typedef std::pair<std::string, std::array<int, 4>> filterName_AreaAsArr;

struct point
{
    int x, y;
};

#endif //FILTERS_DEFINITIONS_H
