//
// Created by Ethan Orchard on 06/03/2023.
//
#include <iostream>

#include "object.h"

void object::move(int _xMovement, int _yMovement) {
    m_DestRect.x += _xMovement;
    m_DestRect.y += _yMovement;
}

void object::setSrcRect(int _x, int _y, int _w, int _h)
{
    m_SrcRect.x = _x;
    m_SrcRect.y = _y;
    m_SrcRect.w = _w;
    m_SrcRect.h = _h;
}

void object::setDestRect(int _x, int _y, int _w, int _h)
{
    m_DestRect.x = _x;
    m_DestRect.y = _y;
    m_DestRect.w = _w;
    m_DestRect.h = _h;
}
