//
// Created by MikhailS on 17.09.2020.
//


#ifndef FILTERS_DEFINITIONS_H
#define FILTERS_DEFINITIONS_H

#include <array>
#include "stb_image.h"


typedef std::array<stbi_uc, 3> rgb;
typedef std::pair<rgb, bool> rgb_errorFlag;

struct point
{
    int x, y;
};

#endif //FILTERS_DEFINITIONS_H
