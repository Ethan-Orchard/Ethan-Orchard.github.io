//
// Created by Ethan Orchard on 28/02/2023.
//
#include "tile.h"

tile::tile()
{
    m_width = 70;
    m_height = 70;
}


void tile::setValues(int _avoid, int _heal, std::string _srcImage, bool _moveable)
{
    m_avoid = _avoid;
    m_heal = _heal;
    m_srcImage = _srcImage;
    m_moveable = _moveable;
}
