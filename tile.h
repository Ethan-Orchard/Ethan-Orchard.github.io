//
// Created by Ethan Orchard on 28/02/2023.
//
#pragma once

#ifndef FEC_TILE_H
#define FEC_TILE_H

#include <string>
#include <SDL2/SDL.h>

#include "object.h"

class tile : public object
{
public:

    tile();

    void setValues(int _avoid, int _heal, std::string _srcImage, bool _moveable);

    int m_avoid;
    int m_heal;
    std::string m_srcImage;
    bool m_moveable;
    SDL_Texture* m_texture;

    bool m_draw;

    int m_width;
    int m_height;

};

#endif //FEC_TILE_H
