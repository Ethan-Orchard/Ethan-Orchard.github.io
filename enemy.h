//
// Created by Ethan Orchard on 27/04/2023.
//

#pragma once

#ifndef FEC_ENEMY_H
#define FEC_ENEMY_H

#include "object.h"
#include "word.h"
#include "healthDisplay.h"

#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <vector>

class character;

class enemy : public object {

public:

    enemy();

    std::string m_SrcString;
    SDL_Texture* m_texture;

    int m_level;
    int m_experience;

    glm::ivec2 m_coords;

    int m_moveStat;
    int m_health;
    int m_healthMax;
    int m_strength;
    int m_skill;
    int m_speed;
    int m_defense;

    bool m_isAlive;
    bool m_hasMoved;

    bool m_showInventory;

    glm::ivec2 m_spriteSize;

    std::vector<glm::ivec2> m_moveableCoords;
    std::vector<character*> m_attackOptions;

    std::vector<glm::ivec2> findMoveBoundary(glm::ivec2 _boundary);

    std::vector<character*> findAttackOptions();

    void update();

    void attack(character* _charToAttack);

    void setHealth(int _change);

    word m_strengthNum;
    word m_skillNum;
    word m_speedNum;
    word m_defenseNum;
    word m_healthNumCurrent;
    word m_healthNumMax;


    SDL_Rect setNumDisplay(int _number);

    SDL_Rect zeroSrcRect;
    SDL_Rect oneSrcRect;
    SDL_Rect twoSrcRect;
    SDL_Rect threeSrcRect;
    SDL_Rect fourSrcRect;
    SDL_Rect fiveSrcRect;
    SDL_Rect sixSrcRect;
    SDL_Rect sevenSrcRect;
    SDL_Rect eightSrcRect;
    SDL_Rect nineSrcRect;

    void setNumRects();

    void drawStats();

    healthDisplay m_healthDisplay;

    void setHealthDisplayNums();

};


#endif //FEC_ENEMY_H
