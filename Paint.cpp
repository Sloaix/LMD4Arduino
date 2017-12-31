#include "Paint.h"

void Paint::setColor(int color)
{
    this->color = color;
}

int Paint::getColor()
{
    return this->color;
}

void Paint::setStyle(Style style)
{
    this->style = style;
}

Style Paint::getStyle()
{
    return this->style;
}

void Paint::setThickness(int thickness)
{
    this->thickness = thickness;
}

int Paint::getThickness()
{
    return this->thickness;
}