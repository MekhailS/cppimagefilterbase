//
// Created by Mikhail on 18.09.2020.//

#include "area_rect.h"

void AreaRect::fitToImageByFraction(image_data &img, const point &frUpLeft, const point &frDownRight) {
    upLeft.x = (frUpLeft.x != 0) ? (img.w) / frUpLeft.x - 1: 0;
    upLeft.y = (frUpLeft.y != 0) ? (img.h) / frUpLeft.y - 1 : 0;

    downRight.x = (frDownRight.x != 0) ? (img.w-1) / frDownRight.x : 0;
    downRight.y = (frDownRight.y != 0) ? (img.h-1) / frDownRight.y : 0;
}

AreaRect::AreaRect(const point &p, int radius)
{
    if (radius < 1)
        return;

    radius -= 1;
    upLeft = {p.x - radius, p.y - radius};
    downRight = {p.x + radius, p.y + radius};
}

AreaRect::AreaRect()
{
    upLeft = {0, 0};
    downRight = {0, 0};
}

void AreaRect::forEachImagePixel(image_data& img, const std::function<void(image_data&, const point&)> func)
{
    for (int x = upLeft.x; x<=downRight.x; x++){
        for (int y = upLeft.y; y<=downRight.y; y++){
             func(img, {x, y});
        }
    }
}

stbi_uc AreaRect::getMedianChannelVal(image_data &img, char channel)
{
    try {
        int indexOfChannel = -1;

        if (channel == 'R')
            indexOfChannel = 0;
        else if (channel == 'G')
            indexOfChannel = 1;
        else if (channel == 'B')
            indexOfChannel = 2;
        else
            throw "Not valid colour channel name";

        std::vector<stbi_uc> colorsInArea;

        auto makeVectorColors_lambda = [&colorsInArea, indexOfChannel]
                (image_data &img, const point &p) mutable
        {
            rgb_errorFlag pixel_error = img.getPixel(p);

            if (!pixel_error.second)
                colorsInArea.push_back(pixel_error.first[indexOfChannel]);
        };

        forEachImagePixel(img, makeVectorColors_lambda);

        std::sort(colorsInArea.begin(), colorsInArea.end());
        return colorsInArea[colorsInArea.size() / 2];
    }
    catch (const char *str)
    {
        std::cout << "Error: " << str << std::endl;
    }
}