//
// Created by Mikhail on 18.09.2020.
//

#include "area_rect.h"

void AreaRect::fitToImageByFraction(image_data &img, const point &frUpLeft, const point &frDownRight) {
    upLeft.x = (frUpLeft.x != 0) ? img.w / frUpLeft.x : 0;
    upLeft.y = (frUpLeft.y != 0) ? img.h / frUpLeft.y : 0;

    downRight.x = (frDownRight.x != 0) ? img.w / frDownRight.x : 0;
    downRight.y = (frDownRight.y != 0) ? img.h / frDownRight.x : 0;
}


void AreaRect::forEachImagePixel(image_data& img, const std::function<void(image_data&, const point&)> func)
{
    for (int x = upLeft.x; x<=downRight.x; x++){
        for (int y = upLeft.y; y<=downRight.y; y++){
             func(img, {x, y});
        }
    }
}