#include "Paint.h"

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