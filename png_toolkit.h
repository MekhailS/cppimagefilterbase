#ifndef PNG_TOOLKIT_H
#define PNG_TOOLKIT_H

#include <string>
#include <map>
//#include <memory>
#include "stb_image.h"

#include "definitions.h"

struct image_data
{
    stbi_uc *pixels;
    int w, h;
    int compPerPixel;

    bool setPixel(int x, int y, rgb& clrSet);
    rgb getPixel(int x, int y);

private:
    int indexByXY(int x, int y);
};

class png_toolkit
{
public:
    enum class Error {
        WrongSize,
        WrongFormat,
        Ok
    };

    png_toolkit();
    ~png_toolkit();
    bool load( std::string const &pictureName );
    bool save( std::string const &pictureName );
    image_data getPixelData( void ) const;

private:
    image_data imgData;
};

#endif // PNG_TOOLKIT_H
