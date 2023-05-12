//
// Created by Ethan Orchard on 02/03/2023.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "character.h"
#include "item.h"
#include "core.h"
#include "enemy.h"


character::character()
{

    m_health = 100;
    m_strength = 10;
    m_directionFacing = 4;

    m_moveStat = 5;

    m_isAlive = true;
    m_hasMoved = false;

    m_showInventory = false;

    m_width = 70;
    m_height = 70;

    font tempFont;

    for(int i = 0; i < 2; i++)
    {
        m_strengthNum.m_fonts.push_back(tempFont);
        m_skillNum.m_fonts.push_back(tempFont);
        m_speedNum.m_fonts.push_back(tempFont);
        m_defenseNum.m_fonts.push_back(tempFont);
        m_healthNumMax.m_fonts.push_back(tempFont);
        m_healthNumCurrent.m_fonts.push_back(tempFont);
        m_healthDisplay.m_healthMax.m_fonts.push_back(tempFont);
        m_healthDisplay.m_healthCurrent.m_fonts.push_back(tempFont);
    }

    srand(time(0));
}

void character::setCoords()
{
    m_coords.x = m_DestRect.x / 70;
    m_coords.y = m_DestRect.y / 70;
}

void character::setRightFacing(int _x, int _y)
{
    m_rightFacing.x = _x;
    m_rightFacing.y = _y;
    m_rightFacing.w = m_SrcRect.w;
    m_rightFacing.h = m_SrcRect.h;
}

void character::setLeftFacing(int _x, int _y)
{
    m_leftFacing.x = _x;
    m_leftFacing.y = _y;
    m_leftFacing.w = m_SrcRect.w;
    m_leftFacing.h = m_SrcRect.h;
}

void character::setFrontFacing(int _x, int _y)
{
    m_frontFacing.x = _x;
    m_frontFacing.y = _y;
    m_frontFacing.w = m_SrcRect.w;
    m_frontFacing.h = m_SrcRect.h;
}

void character::setBackFacing(int _x, int _y)
{
    m_backFacing.x = _x;
    m_backFacing.y = _y;
    m_backFacing.w = m_SrcRect.w;
    m_backFacing.h = m_SrcRect.h;
}


void character::setHealth(int _change)
{
    m_health += _change;
    if(m_health <= 0)
    {
        m_isAlive = false;
    }
    std::cout << "Player Current Health: " << m_health << std::endl;
}

void character::update()
{
    // do update things
}

std::vector<glm::ivec2> character::findMoveBoundary(glm::ivec2 _boundary)
{
    int yBoundUpper = m_coords.y - m_moveStat;
    int yBoundLower = m_coords.y + m_moveStat;
    int xBoundLeft = m_coords.x - m_moveStat;
    int xBoundRight = m_coords.x + m_moveStat;

    std::vector<glm::ivec2> moveableCoords;
    glm::ivec2 coordsToCheck[50];

    if (yBoundUpper < 0)
    {
        yBoundUpper = 0;
    }
    if(xBoundLeft < 0)
    {
        xBoundLeft = 0;
    }
    if(yBoundLower > _boundary.y)
    {
        yBoundLower = _boundary.y;
    }
    if(xBoundRight > _boundary.x)
    {
        xBoundRight = _boundary.x;
    }

    for (int yCoord = yBoundUpper; yCoord <= yBoundLower; yCoord++)
    {
        for (int xCoord = xBoundLeft; xCoord <= xBoundRight; xCoord++)
        {
            int distanceCheck = 0;
            if(yCoord < m_coords.y)
            {
                distanceCheck += (m_coords.y - yCoord);
            }
            else if(yCoord > m_coords.y)
            {
                distanceCheck += (yCoord - m_coords.y);
            }

            if(xCoord < m_coords.x)
            {
                distanceCheck += (m_coords.x - xCoord);
            }
            else if(xCoord > m_coords.x)
            {
                distanceCheck += (xCoord - m_coords.x);
            }
            if(distanceCheck <= m_moveStat)
            {
                moveableCoords.push_back(glm::ivec2(xCoord, yCoord));
            }
        }
    }

    return moveableCoords;
}

void character::showMoveRange(tile tile[], class tile map[])
{

    for(int i = 0; i < m_moveableCoords.size(); i++)
    {
        if(map[(m_moveableCoords.at(i).y * 15) + m_moveableCoords.at(i).x].m_moveable)
        {
            tile[(m_moveableCoords.at(i).y * 15) + m_moveableCoords.at(i).x].m_draw = true;
        }
    }
}

void character::setSrcImage(std::string _srcImage)
{
    m_srcImage = _srcImage;
}

bool character::checkExperience()
{
    if (m_experience >= 100)
    {
        return true;
    }
    return false;
}

void character::levelUp()
{
    m_experience -= 100;
    m_level++;
    //make random number for each stat, if number is above growth rate then increase stat
    // track amount of stats increased, if 0 then reroll all, if 1 reroll a different stat, 2+ is fine, aiming for 3 stats per level

    int random = 0;
    int numStatsIncreased = 0;
    bool validLevel = false;

    int baseHealth = m_health;
    int baseHealthMax = m_healthMax;
    int baseStrength = m_strength;
    int baseSkill = m_skill;
    int baseSpeed = m_speed;
    int baseDefense = m_defense;

    while(!validLevel)
    {

        random = (int)(rand() % 100);

        numStatsIncreased = 0;
        if (random < m_healthGrowth)
        {
            m_health += 1;
            m_healthMax += 1;
            numStatsIncreased++;
        }

        random = (int) (rand() % 100);

        if (random < m_strengthGrowth)
        {
            m_strength += 1;
            numStatsIncreased++;
        }

        random = (int)(rand() % 100);

        if(random < m_skillGrowth)
        {
            m_skill += 1;
            numStatsIncreased++;
        }

        random = (int)(rand() % 100);

        if(random < m_speedGrowth)
        {
            m_speed += 1;
            numStatsIncreased++;
        }

        random = (int)(rand() % 100);

        if(random < m_defenseGrowth)
        {
            m_defense += 1;
            numStatsIncreased++;
        }

        if (numStatsIncreased > 2)
        {
            validLevel = true;
        }
        else
        {
            m_health = baseHealth;
            m_healthMax = baseHealthMax;
            m_strength = baseStrength;
            m_skill = baseSkill;
            m_speed = baseSpeed;
            m_defense = baseDefense;
        }
    }

}

bool character::checkAttackRange()
{

    std::vector<glm::ivec2> attackSpots;
    std::vector<glm::ivec2> attackSpotsEnemies;

    attackSpots.push_back(glm::ivec2(m_coords.x - 1, m_coords.y));
    attackSpots.push_back(glm::ivec2(m_coords.x + 1, m_coords.y));
    attackSpots.push_back(glm::ivec2(m_coords.x, m_coords.y - 1));
    attackSpots.push_back(glm::ivec2(m_coords.x, m_coords.y + 1));


    for(int i = 0; i < attackSpots.size(); i++)
    {
        for(int j = 0; j < core->enemies.size(); j++)
        {
            if(attackSpots.at(i) == core->enemies.at(j)->m_coords)
            {
                attackSpotsEnemies.push_back(attackSpots.at(i));
            }
        }
    }

    if(!attackSpotsEnemies.empty())
    {
        return true;
    }

    return false;
}

void character::attack()
{
    switch (m_directionFacing)
    {
        case 1:
            for (int i = 0; i < core->enemies.size(); i++)
            {
                if (core->enemies.at(i)->m_coords.x == m_coords.x && core->enemies.at(i)->m_coords.y + 1 == m_coords.y)
                {
                    if(m_speed - 5 > core->enemies.at(i)->m_speed)
                    {
                        core->enemies.at(i)->setHealth(-(m_strength - core->enemies.at(i)->m_defense));
                    }
                    core->enemies.at(i)->setHealth(-(m_strength - core->enemies.at(i)->m_defense));
                    setHealth(-(core->enemies.at(i)->m_strength - m_defense));
                    if(core->enemies.at(i)->m_isAlive)
                    {
                        m_experience += 10;
                    }
                    else
                    {
                        m_experience += 60;
                    }
                }
            }
            break;

        case 2:
            for (int i = 0; i < core->enemies.size(); i++)
            {
                if (core->enemies.at(i)->m_coords.y == m_coords.y && core->enemies.at(i)->m_coords.x + 1 == m_coords.x)
                {
                    if(m_speed - 5 > core->enemies.at(i)->m_speed)
                    {
                        core->enemies.at(i)->setHealth(-(m_strength - core->enemies.at(i)->m_defense));
                    }
                    core->enemies.at(i)->setHealth(-(m_strength - core->enemies.at(i)->m_defense));
                    setHealth(-(core->enemies.at(i)->m_strength - m_defense));
                    if(core->enemies.at(i)->m_isAlive)
                    {
                        m_experience += 10;
                    }
                    else
                    {
                        m_experience += 60;
                    }
                }
            }
            break;

        case 3:
            for (int i = 0; i < core->enemies.size(); i++)
            {
                if (core->enemies.at(i)->m_coords.y == m_coords.y && core->enemies.at(i)->m_coords.x - 1 == m_coords.x)
                {
                    if(m_speed - 5 > core->enemies.at(i)->m_speed)
                    {
                        core->enemies.at(i)->setHealth(-(m_strength - core->enemies.at(i)->m_defense));
                    }
                    core->enemies.at(i)->setHealth(-(m_strength - core->enemies.at(i)->m_defense));
                    setHealth(-(core->enemies.at(i)->m_strength - m_defense));
                    if(core->enemies.at(i)->m_isAlive)
                    {
                        m_experience += 10;
                    }
                    else
                    {
                        m_experience += 60;
                    }
                }
            }
            break;

        case 4:
            for (int i = 0; i < core->enemies.size(); i++)
            {
                if (core->enemies.at(i)->m_coords.x == m_coords.x && core->enemies.at(i)->m_coords.y - 1 == m_coords.y)
                {
                    if(m_speed - 5 > core->enemies.at(i)->m_speed)
                    {
                        core->enemies.at(i)->setHealth(-(m_strength - core->enemies.at(i)->m_defense));
                    }
                    core->enemies.at(i)->setHealth(-(m_strength - core->enemies.at(i)->m_defense));
                    setHealth(-(core->enemies.at(i)->m_strength - m_defense));
                    if(core->enemies.at(i)->m_isAlive)
                    {
                        m_experience += 10;
                    }
                    else
                    {
                        m_experience += 60;
                    }
                }
            }
            break;
    }
}

SDL_Rect character::setNumDisplay(int _number)
{
    switch(_number)
    {
        case 0:
            return zeroSrcRect;
            break;

        case 1:
            return oneSrcRect;
            break;

        case 2:
            return twoSrcRect;
            break;

        case 3:
            return threeSrcRect;
            break;

        case 4:
            return fourSrcRect;
            break;

        case 5:
            return fiveSrcRect;
            break;

        case 6:
            return sixSrcRect;
            break;

        case 7:
            return sevenSrcRect;
            break;

        case 8:
            return eightSrcRect;
            break;

        case 9:
            return nineSrcRect;
            break;

        default:
            return zeroSrcRect;
            break;
    }

}

void character::setNumRects()
{
    zeroSrcRect.x = 0;
    zeroSrcRect.y = 31;
    zeroSrcRect.w = 8;
    zeroSrcRect.h = 9;

    oneSrcRect.x = 8;
    oneSrcRect.y = 31;
    oneSrcRect.w = 8;
    oneSrcRect.h = 9;

    twoSrcRect.x = 16;
    twoSrcRect.y = 31;
    twoSrcRect.w = 8;
    twoSrcRect.h = 9;

    threeSrcRect.x = 24;
    threeSrcRect.y = 31;
    threeSrcRect.w = 8;
    threeSrcRect.h = 9;

    fourSrcRect.x = 32;
    fourSrcRect.y = 31;
    fourSrcRect.w = 8;
    fourSrcRect.h = 9;

    fiveSrcRect.x = 40;
    fiveSrcRect.y = 31;
    fiveSrcRect.w = 8;
    fiveSrcRect.h = 9;

    sixSrcRect.x = 48;
    sixSrcRect.y = 31;
    sixSrcRect.w = 8;
    sixSrcRect.h = 9;

    sevenSrcRect.x = 56;
    sevenSrcRect.y = 31;
    sevenSrcRect.w = 8;
    sevenSrcRect.h = 9;

    eightSrcRect.x = 64;
    eightSrcRect.y = 31;
    eightSrcRect.w = 8;
    eightSrcRect.h = 9;

    nineSrcRect.x = 72;
    nineSrcRect.y = 31;
    nineSrcRect.w = 8;
    nineSrcRect.h = 9;
}

void character::drawStats()
{

    m_strengthNum.m_fonts.at(0).m_SrcRect = setNumDisplay(m_strength / 10);
    m_strengthNum.m_fonts.at(1).m_SrcRect = setNumDisplay(m_strength % 10);

    m_strengthNum.m_fonts.at(0).setDestRect(800, 120, 32, 32);
    m_strengthNum.m_fonts.at(1).setDestRect(832, 120, 32, 32);

    for(int i = 0; i < m_strengthNum.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_strengthNum.m_fonts.at(i).m_texture, &m_strengthNum.m_fonts.at(i).m_SrcRect, &m_strengthNum.m_fonts.at(i).m_DestRect);
    }

    m_skillNum.m_fonts.at(0).m_SrcRect = setNumDisplay(m_skill / 10);
    m_skillNum.m_fonts.at(1).m_SrcRect = setNumDisplay(m_skill % 10);

    m_skillNum.m_fonts.at(0).setDestRect(800, 170, 32, 32);
    m_skillNum.m_fonts.at(1).setDestRect(832, 170, 32, 32);

    for(int i = 0; i < m_skillNum.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_skillNum.m_fonts.at(i).m_texture, &m_skillNum.m_fonts.at(i).m_SrcRect, &m_skillNum.m_fonts.at(i).m_DestRect);
    }

    m_speedNum.m_fonts.at(0).m_SrcRect = setNumDisplay(m_speed / 10);
    m_speedNum.m_fonts.at(1).m_SrcRect = setNumDisplay(m_speed % 10);

    m_speedNum.m_fonts.at(0).setDestRect(800, 220, 32, 32);
    m_speedNum.m_fonts.at(1).setDestRect(832, 220, 32, 32);

    for(int i = 0; i < m_speedNum.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_speedNum.m_fonts.at(i).m_texture, &m_speedNum.m_fonts.at(i).m_SrcRect, &m_speedNum.m_fonts.at(i).m_DestRect);
    }

    m_defenseNum.m_fonts.at(0).m_SrcRect = setNumDisplay(m_defense / 10);
    m_defenseNum.m_fonts.at(1).m_SrcRect = setNumDisplay(m_defense % 10);

    m_defenseNum.m_fonts.at(0).setDestRect(800, 270, 32, 32);
    m_defenseNum.m_fonts.at(1).setDestRect(832, 270, 32, 32);

    for(int i = 0; i < m_defenseNum.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_defenseNum.m_fonts.at(i).m_texture, &m_defenseNum.m_fonts.at(i).m_SrcRect, &m_defenseNum.m_fonts.at(i).m_DestRect);
    }

    m_healthNumCurrent.m_fonts.at(0).m_SrcRect = setNumDisplay(m_health / 10);
    m_healthNumCurrent.m_fonts.at(1).m_SrcRect = setNumDisplay(m_health % 10);

    m_healthNumCurrent.m_fonts.at(0).setDestRect(250, 800, 32, 32);
    m_healthNumCurrent.m_fonts.at(1).setDestRect(282, 800, 32, 32);

    for(int i = 0; i < m_healthNumCurrent.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_healthNumCurrent.m_fonts.at(i).m_texture, &m_healthNumCurrent.m_fonts.at(i).m_SrcRect, &m_healthNumCurrent.m_fonts.at(i).m_DestRect);
    }

    m_healthNumMax.m_fonts.at(0).m_SrcRect = setNumDisplay(m_healthMax / 10);
    m_healthNumMax.m_fonts.at(1).m_SrcRect = setNumDisplay(m_healthMax % 10);

    m_healthNumMax.m_fonts.at(0).setDestRect(325, 800, 32, 32);
    m_healthNumMax.m_fonts.at(1).setDestRect(357, 800, 32, 32);

    for(int i = 0; i < m_healthNumMax.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_healthNumMax.m_fonts.at(i).m_texture, &m_healthNumMax.m_fonts.at(i).m_SrcRect, &m_healthNumMax.m_fonts.at(i).m_DestRect);
    }
}

enemy* character::findEnemyToAttack()
{
    switch(m_directionFacing)
    {
        case 1:
            for(int i = 0; i < core->enemies.size(); i++)
            {
                if (core->enemies.at(i)->m_coords.y + 1 == m_coords.y && core->enemies.at(i)->m_coords.x == m_coords.x)
                {
                    return core->enemies.at(i);
                }
            }

        case 2:
            for(int i = 0; i < core->enemies.size(); i++)
            {
                if (core->enemies.at(i)->m_coords.y == m_coords.y && core->enemies.at(i)->m_coords.x + 1 == m_coords.x)
                {
                    return core->enemies.at(i);
                }
            }

        case 3:
            for(int i = 0; i < core->enemies.size(); i++)
            {
                if (core->enemies.at(i)->m_coords.y == m_coords.y && core->enemies.at(i)->m_coords.x - 1 == m_coords.x)
                {
                    return core->enemies.at(i);
                }
            }

        case 4:
            for(int i = 0; i < core->enemies.size(); i++)
            {
                if (core->enemies.at(i)->m_coords.x == m_coords.x && core->enemies.at(i)->m_coords.y - 1 == m_coords.y)
                {
                    return core->enemies.at(i);
                }
            }
    }
}

void character::setHealthDisplayNums()
{
    m_healthDisplay.m_healthCurrent.m_fonts.at(0).m_SrcRect = setNumDisplay(m_health / 10);
    m_healthDisplay.m_healthCurrent.m_fonts.at(1).m_SrcRect = setNumDisplay(m_health % 10);

    m_healthDisplay.m_healthCurrent.m_fonts.at(0).setDestRect(130, 875, 16, 16);
    m_healthDisplay.m_healthCurrent.m_fonts.at(1).setDestRect(146, 875, 16, 16);

    m_healthDisplay.m_healthMax.m_fonts.at(0).m_SrcRect = setNumDisplay(m_healthMax / 10);
    m_healthDisplay.m_healthMax.m_fonts.at(1).m_SrcRect = setNumDisplay(m_healthMax % 10);

    m_healthDisplay.m_healthMax.m_fonts.at(0).setDestRect(170, 875, 16, 16);
    m_healthDisplay.m_healthMax.m_fonts.at(1).setDestRect(186, 875, 16, 16);
}

