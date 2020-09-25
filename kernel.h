//
// Created by Mikhail on 25.09.2020.
//

#ifndef STUDENT_TOOLKIT_KERNEL_H
#define STUDENT_TOOLKIT_KERNEL_H

#include "definitions.h"
#include "png_toolkit.h"

class AreaRect;

class Kernel {
protected:

    int sizeW;
    std::vector<std::vector<double>> W;

public:

    stbi_uc applyOnPixel(image_data& img,
                         const point& p, const AreaRect& areaOfApplying, char channelIndex);
};


#endif //STUDENT_TOOLKIT_KERNEL_H
