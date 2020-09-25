//
// Created by Mikhail on 18.09.2020.
//

#include "filters.h"


void FilterRed::apply(image_data &img, AreaRect &area)
{
    auto setRed_lambda = [](image_data& img, const point& p){
        img.setPixel(p, {255, 0, 0});
    };

    area.forEachImagePixel(img, setRed_lambda);
}


void FilterBlackWhite::apply(image_data &img, AreaRect &area)
{
    auto setBW_lambda = [](image_data& img, const point& p){
        rgb clr = img.getPixel(p).first;
        auto intensity = stbi_uc(int((3*clr[0] + 6*clr[1] + 1*clr[2])/10));

        img.setPixel(p, {intensity, intensity, intensity});
    };

    area.forEachImagePixel(img, setBW_lambda);
}


void FilterThreshold::apply(image_data &img, AreaRect &area)
{
    FilterBlackWhite filterBW;
    filterBW.apply(img, area);

    image_data imgCopy = img.deepcopy();

    auto setThreshold_lambda = [&area, &imgCopy](image_data& img, const point& p) mutable {
        AreaRect square(p, 3);
        AreaRect areaForMedian = square.partInsideOf(area);

        // since BlackWhite filter was applied, there is no difference in channels,
        // so, we may pick any of R,G,B ('R' has been chosen below)
        stbi_uc medianValR = areaForMedian.getMedianChannelVal(imgCopy, 0);

        rgb_errorFlag pixel_error = img.getPixel(p);

        if ((!pixel_error.second) && (pixel_error.first[0] < medianValR))
            img.setPixel(p, {0, 0, 0});

    };

    area.forEachImagePixel(img, setThreshold_lambda);

    imgCopy.freePixels();
}


void FilterEdge::apply(image_data &img, AreaRect &area)
{
    FilterBlackWhite filterBW;
    filterBW.apply(img, area);

    image_data imgCopy = img.deepcopy();

    auto applyKernel_lambda = [this, &area, &imgCopy](image_data& img, const point& p) mutable {
        stbi_uc resKernelR = this->kernel.applyOnPixel(imgCopy, p, area, 0);

        rgb_errorFlag pixel_error = img.getPixel(p);

        if (!pixel_error.second)
            img.setPixel(p, {resKernelR, resKernelR, resKernelR});

    };

    area.forEachImagePixel(img, applyKernel_lambda);

    imgCopy.freePixels();
}


void FilterBlur::apply(image_data &img, AreaRect &area)
{

    image_data imgCopy = img.deepcopy();

    auto applyKernel_lambda = [this, &area, &imgCopy](image_data& img, const point& p) mutable {
        stbi_uc resKernelR = this->kernel.applyOnPixel(imgCopy, p, area, 0);
        stbi_uc resKernelG = this->kernel.applyOnPixel(imgCopy, p, area, 1);
        stbi_uc resKernelB = this->kernel.applyOnPixel(imgCopy, p, area, 2);

        rgb_errorFlag pixel_error = img.getPixel(p);

        if (!pixel_error.second)
            img.setPixel(p, {resKernelR, resKernelG, resKernelB});

    };

    area.forEachImagePixel(img, applyKernel_lambda);

    imgCopy.freePixels();
}