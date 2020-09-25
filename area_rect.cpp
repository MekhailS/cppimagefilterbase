//
// Created by Mikhail on 18.09.2020.//

#include "area_rect.h"


bool AreaRect::containsPoint(const point& p) const
{
    return (((upLeft.x <= p.x) && (p.x < downRight.x)) &&
            ((upLeft.y <= p.y) && (p.y < downRight.y)));
}

AreaRect AreaRect::partInsideOf(const AreaRect& B)
{
    AreaRect partInside;
    partInside.upLeft.x = std::max(upLeft.x, B.upLeft.x);
    partInside.upLeft.y = std::max(upLeft.y, B.upLeft.y);

    partInside.downRight.x = std::min(downRight.x, B.downRight.x);
    partInside.downRight.y = std::min(downRight.y, B.downRight.y);

    return partInside;
}

void AreaRect::fitToImageByFraction(image_data &img, const point &frUpLeft, const point &frDownRight) {
    upLeft.x = (frUpLeft.x != 0) ? (img.w) / frUpLeft.x: 0;
    upLeft.y = (frUpLeft.y != 0) ? (img.h) / frUpLeft.y: 0;

    downRight.x = (frDownRight.x != 0) ? (img.w) / frDownRight.x : 0;
    downRight.y = (frDownRight.y != 0) ? (img.h) / frDownRight.y : 0;
}

AreaRect::AreaRect(const point &p, int radius)
{
    if (radius < 1)
        return;

    radius -= 1;
    upLeft = {p.x - radius, p.y - radius};
    downRight = {p.x + radius + 1, p.y + radius + 1};
}

AreaRect::AreaRect()
{
    upLeft = {0, 0};
    downRight = {0, 0};
}

void AreaRect::forEachImagePixel(image_data& img, const std::function<void(image_data&, const point&)> func)
{
    for (int x = upLeft.x; x < downRight.x; x++) {
        for (int y = upLeft.y; y < downRight.y; y++) {
             func(img, {x, y});
        }
    }
}

stbi_uc AreaRect::getMedianChannelVal(image_data &img, int channelIndex)
{
    try
    {
        if ((channelIndex < 0) || (channelIndex > 2))
            throw "Not valid colour channel name";

        std::vector<stbi_uc> colorsInArea;

        auto makeVectorColors_lambda = [&colorsInArea, channelIndex]
                (image_data &img, const point &p) mutable
        {
            rgb_errorFlag pixel_error = img.getPixel(p);

            if (!pixel_error.second)
                colorsInArea.push_back(pixel_error.first[channelIndex]);
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