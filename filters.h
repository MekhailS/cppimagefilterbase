//
// Created by Mikhail on 18.09.2020.
//

#ifndef FILTERS_FILTERS_H
#define FILTERS_FILTERS_H

#include "definitions.h"
#include "area_rect.h"
#include "png_toolkit.h"

class FilterAbstract
{
public:
    virtual void apply(image_data& img, AreaRect& area) = 0;
};


class FilterRed: public FilterAbstract
{
public:
    virtual void apply(image_data& img, AreaRect& area) override;
};


class FilterBlackWhite: public FilterAbstract
{
public:
    virtual void apply(image_data& img, AreaRect& area) override;
};


class FilterThreshold: public FilterAbstract
{
public:
    virtual void apply(image_data& img, AreaRect& area) override;
};

#endif //FILTERS_FILTERS_H
