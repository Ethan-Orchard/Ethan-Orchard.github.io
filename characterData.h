//
// Created by Ethan Orchard on 20/04/2023.
//

#ifndef FEC_CHARACTERDATA_H
#define FEC_CHARACTERDATA_H



#include <string>
#include <SDL2/SDL.h>

struct characterData {

    std::string m_srcImage;
    SDL_Rect m_rightFacing;
    SDL_Rect m_leftFacing;
    SDL_Rect m_frontFacing;
    SDL_Rect m_backFacing;

    int m_moveStat;
    int m_health;
    int m_strength;
    int m_skill;
    int m_speed;
    int m_defense;

};

#endif //FEC_CHARACTERDATA_H
