//
// Created by Ethan Orchard on 02/05/2023.
//

#pragma once

#ifndef FEC_WEAPON_H
#define FEC_WEAPON_H

#include "item.h"
#include <SDL2/SDL.h>
#include <string>

class weapon : public item {

public:

    int m_might;
    int m_hit;
    int m_crit;
    int m_durability;

    std::string m_srcString;
    SDL_Texture* m_texture;
};


#endif //FEC_WEAPON_H
