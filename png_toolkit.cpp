#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <array>
#include <iostream>
#include "stb_image_write.h"
#include "png_toolkit.h"

#include "area_rect.h"
#include "filters.h"

image_data image_data::deepcopy()
{
    image_data imgNew;
    imgNew.h = h;
    imgNew.w = w;
    imgNew.compPerPixel = compPerPixel;

    int imgSize = h*w*compPerPixel;
    imgNew.pixels = new stbi_uc[imgSize];
    memcpy(imgNew.pixels, pixels, imgSize);

    return imgNew;
}

bool image_data::setPixel(const point& p, const rgb &clrSet)
{
    try
    {
        int i = indexByPoint(p);

        if (i < 0)
            throw "Set point (x,y) is outside of image area";

        pixels[i] = clrSet[0];
        pixels[i+1] = clrSet[1];
        pixels[i+2] = clrSet[2];

        return 1;
    }
    catch (const char *str)
    {
        std::cout << "Error: " << str << std::endl;
    }
    return 0;
}

rgb_errorFlag image_data::getPixel(const point& p)
{
    int i = indexByPoint(p);

    if (i < 0)
        return rgb_errorFlag (rgb{0, 0, 0}, 1);

    return rgb_errorFlag (rgb{pixels[i], pixels[i+1], pixels[i+2]}, 0);
}

int image_data::indexByPoint(const point& p)
{

    if (( (0 <= p.x) && (p.x < w)) && ((0 <= p.y) && (p.y < h)))
        return compPerPixel * (p.x + p.y * w);

    return -1;
}

void image_data::freePixels()
{
    stbi_image_free(pixels);
}


png_toolkit::png_toolkit()
{
}

png_toolkit::~png_toolkit()
{
    stbi_image_free(imgData.pixels);
}

bool png_toolkit::load( const std::string &pictureName )
{
    imgData.pixels = stbi_load(pictureName.c_str(), &imgData.w, &imgData.h, &imgData.compPerPixel, 0);
    return imgData.pixels != nullptr;
}

bool png_toolkit::save( const std::string &pictureName )
{
    return stbi_write_png(pictureName.c_str(),
                   imgData.w, imgData.h,
                   imgData.compPerPixel,
                          imgData.pixels, 0) != 0;
}

image_data png_toolkit::getPixelData( void ) const
{
    return imgData;
}

