//
// Created by Ethan Orchard on 06/03/2023.
//

#pragma once

#ifndef FEC_OBJECT_H
#define FEC_OBJECT_H

#include <SDL2/SDL.h>

class core;

class object {
public:
    SDL_Rect m_SrcRect;
    SDL_Rect m_DestRect;

    core* core;

    void move(int _xMovement, int _yMovement);
    void setSrcRect(int _x, int _y, int _w, int _h);
    void setDestRect(int _x, int _y, int _w, int _h);
};


#endif //FEC_OBJECT_H
