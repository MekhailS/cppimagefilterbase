#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <array>
#include <iostream>
#include "stb_image_write.h"
#include "png_toolkit.h"

int image_data::indexByXY(int x, int y)
{
    int i = compPerPixel * (x + y * w);
    return (i <= h * w - compPerPixel) ? i : -1;
}

bool image_data::setPixel(int x, int y, rgb &clrSet)
{
    try
    {
        int i = indexByXY(x, y);

        if (i < 0)
            throw "Point (x,y) is outside of image area";

        pixels[i] = clrSet[0];
        pixels[i+1] = clrSet[1];
        pixels[i+2] = clrSet[2];
    }
    catch (const char *str)
    {
        std::cout << "Error: " << str << std::endl;
    }
}

rgb image_data::getPixel(int x, int y)
{
    try
    {
        int i = indexByXY(x, y);

        if (i < 0)
            throw "Point (x,y) is outside of image area";

        return {pixels[i], pixels[i+1], pixels[i+2]};
    }
    catch (const char *str)
    {
        std::cout << "Error: " << str << std::endl;
    }
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
