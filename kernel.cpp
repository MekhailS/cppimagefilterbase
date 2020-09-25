//
// Created by Mikhail on 25.09.2020.
//

#include "kernel.h"
#include "area_rect.h"

Kernel::Kernel(std::vector<std::vector<double>> W_s)
{
    int sizeW = W_s.size();
    for (auto W_line : W_s) {
        if (W_line.size() != sizeW)
            return;
    }
    W = W_s;
    sumWeights = 0;
    for (auto W_line: W){
        for (auto W_elem: W_line){
            sumWeights += W_elem;
        }
    }
}

stbi_uc Kernel::applyOnPixel(image_data &img,
                             const point &p, const AreaRect &areaOfApplying, char channelIndex) const
{
    try
    {
        int sizeW = W.size();

        if ((channelIndex < 0) || (channelIndex > 2))
            throw "Not valid colour channel name";

        double res = 0;

        point pCur;

        pCur.x = p.x - (sizeW / 2);
        for (int i = 0; i < sizeW; i++, pCur.x += 1) {
            pCur.y = p.y - (sizeW / 2);
            for (int j = 0; j < sizeW; j++, pCur.y += 1) {
                //pCur.x += i;
                //pCur.y += j;

                if (areaOfApplying.containsPoint(pCur)) {
                    rgb_errorFlag pixel_err = img.getPixel(pCur);

                    if (!pixel_err.second)
                        res += pixel_err.first[channelIndex] * W[j][i];

                }
            }
        }

        res /= sumWeights;

        if (res > 255)
            res = 255;
        else if (res < 0)
            res = 0;

        return stbi_uc(res);
    }
    catch (const char *str)
    {
        std::cout << "Error: " << str << std::endl;
    }
}