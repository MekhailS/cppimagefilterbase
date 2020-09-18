#ifndef PNG_TOOLKIT_H
#define PNG_TOOLKIT_H

#include <string>
#include <map>
//#include <memory>
#include "definitions.h"

class FilterAbstract;
class AreaRect;

struct image_data
{
    stbi_uc *pixels;
    int w, h;
    int compPerPixel;

    image_data deepcopy();
    bool setPixel(const point& p, const rgb& clrSet);
    rgb_errorFlag getPixel(const point& p);

private:
    int indexByPoint(const point& p);
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

    void applyFilter(FilterAbstract* filter, AreaRect& area);

private:
    image_data imgData;
};

#endif // PNG_TOOLKIT_H
