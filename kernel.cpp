//
// Created by Mikhail on 25.09.2020.
//

#include "kernel.h"
#include "area_rect.h"

stbi_uc Kernel::applyOnPixel(image_data &img,
                             const point &p, const AreaRect &areaOfApplying, char channelIndex)
{
    try
    {
        if ((channelIndex < 0) || (channelIndex > 2))
            throw "Not valid colour channel name";

        double res = 0;

        point pCur = {p.x - (sizeW / 2), p.y - (sizeW / 2)};

        for (int i = 0; i < sizeW; i++) {
            for (int j = 0; j < sizeW; j++) {
                pCur.x += i;
                pCur.y += j;

                if (areaOfApplying.containsPoint(pCur)) {
                    rgb_errorFlag pixel_err = img.getPixel(pCur);

                    if (!pixel_err.second)
                        res += pixel_err.first[channelIndex] * W[j][i];

                }
            }
        }

        return stbi_uc(res);
    }
    catch (const char *str)
    {
        std::cout << "Error: " << str << std::endl;
    }
}