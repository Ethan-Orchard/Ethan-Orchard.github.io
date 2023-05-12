//
// Created by Ethan Orchard on 02/03/2023.
//
#pragma once

#ifndef FEC_CHARACTER_H
#define FEC_CHARACTER_H

#include <string>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <vector>

#include "object.h"
#include "tile.h"
#include "characterData.h"
#include "word.h"
#include "healthDisplay.h"

class item;
class core;
class enemy;

class character : public object {


public:

    character();

    void setSrcImage(std::string _srcImage);

    void setRightFacing(int _x, int _y);
    void setLeftFacing(int _x, int _y);
    void setFrontFacing(int _x, int _y);
    void setBackFacing(int _x, int _y);

    void setCoords();

    void setHealth(int _change);

    void showMoveRange(tile tile[], class tile map[]);

    std::vector<glm::ivec2> findMoveBoundary(glm::ivec2 _boundary);

    void update();

    bool checkAttackRange();

    bool checkExperience();

    void levelUp();

    void attack();

    std::string m_srcImage;
    SDL_Texture* m_texture;
    SDL_Rect m_rightFacing;
    SDL_Rect m_leftFacing;
    SDL_Rect m_frontFacing;
    SDL_Rect m_backFacing;

    int m_width;
    int m_height;

    class core* core;

    glm::ivec2 m_spriteSize;

    int m_spriteSheetX;
    int m_spriteSheetY;

    //Make a struct for spriteSheet values "tex, coords etc instantiate struct per spritesheet for animations.

    int m_directionFacing;
    // 1 - up, 2 - left, 3- right, 4 down

    glm::ivec2 m_coords;

    std::vector<glm::ivec2> m_moveableCoords;

    std::string name;

    int m_level;
    int m_experience;

    int m_moveStat;
    int m_health;
    int m_healthMax;
    int m_strength;
    int m_skill;
    int m_speed;
    int m_defense;

    int m_healthGrowth;
    int m_strengthGrowth;
    int m_skillGrowth;
    int m_speedGrowth;
    int m_defenseGrowth;

    bool m_isAlive;
    bool m_showMoveRange;
    bool m_hasMoved;

    bool m_showInventory;
    //remove later, here for testing - pre core/states

    SDL_Rect m_startingCoords;
    int m_startingDirection;

    characterData characterData;

    std::vector<item> inventory;

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

    enemy* findEnemyToAttack();

    healthDisplay m_healthDisplay;

    void setHealthDisplayNums();
};


#endif //FEC_CHARACTER_H
