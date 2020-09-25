//
// Created by Mikhail on 25.09.2020.
//

#ifndef STUDENT_TOOLKIT_KERNEL_H
#define STUDENT_TOOLKIT_KERNEL_H

#include "definitions.h"
#include "png_toolkit.h"

class AreaRect;

class Kernel {
private:

    int sumWeights;

    std::vector<std::vector<double>> W;

public:

    Kernel(std::vector<std::vector<double>> W_s);

    stbi_uc applyOnPixel(image_data& img,
                         const point& p, const AreaRect& areaOfApplying, char channelIndex) const;
};


#endif //STUDENT_TOOLKIT_KERNEL_H
