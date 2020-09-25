//
// Created by Mikhail on 18.09.2020.
//

#ifndef FILTERS_FILTERS_H
#define FILTERS_FILTERS_H

#include "definitions.h"
#include "area_rect.h"
#include "kernel.h"
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


class FilterConvolution: public FilterAbstract
{
protected:
    const Kernel kernel;

public:
    FilterConvolution(std::vector<std::vector<double>> W): kernel(W) {};

    virtual void apply(image_data& img, AreaRect& area) override;
};


class FilterEdge: public FilterConvolution
{
public:
    FilterEdge():
        FilterConvolution({{-1, -1, -1},
                           {-1,  9, -1},
                           {-1, -1, -1}}) {};
};


class FilterBlur: public FilterConvolution
{
public:
    FilterBlur():
            FilterConvolution({{1, 1, 1},
                               {1, 1, 1},
                               {1, 1, 1}}) {};
};

#endif //FILTERS_FILTERS_H
