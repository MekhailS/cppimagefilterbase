//
// Created by Mikhail on 18.09.2020.
//

#ifndef FILTERS_AREA_RECT_H
#define FILTERS_AREA_RECT_H

#include <functional>
#include "definitions.h"
#include "png_toolkit.h"

class AreaRect {
private:
    point upLeft, downRight;

public:
    AreaRect();
    AreaRect(const point &p, int radius);

    bool containsPoint(const point& p) const;

    AreaRect partInsideOf(const AreaRect& B);

    void fitToImageByFraction(image_data& img,
                              const point& frUpLeft={0,0},
                              const point& frDownRight={1,1});

    void forEachImagePixel(image_data& img,
                           const std::function<void(image_data&, const point&)> func);

    stbi_uc getMedianChannelVal(image_data& img, int channelIndex);
};


#endif //FILTERS_AREA_RECT_H
