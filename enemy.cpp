//
// Created by Ethan Orchard on 27/04/2023.
//

#include "enemy.h"
#include "character.h"
#include "core.h"

#include <iostream>


std::vector<glm::ivec2> enemy::findMoveBoundary(glm::ivec2 _boundary)
{
    int yBoundUpper = m_coords.y - m_moveStat;
    int yBoundLower = m_coords.y + m_moveStat;
    int xBoundLeft = m_coords.x - m_moveStat;
    int xBoundRight = m_coords.x + m_moveStat;

    std::vector<glm::ivec2> moveableCoords;

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

std::vector<character*> enemy::findAttackOptions()
{
    std::vector<character*> attackOptions;
    for(int i = 0; i < m_moveableCoords.size(); i++)
    {
        for(int j = 0; j < core->characters.size(); j++)
        {
            if(m_moveableCoords.at(i) == core->characters.at(j)->m_coords)
            {
                attackOptions.push_back(core->characters.at(j));
            }
        }
    }

    return attackOptions;
}

void enemy::update()
{
    m_moveableCoords = findMoveBoundary(core->map_Boundary);

    m_attackOptions = findAttackOptions();

    int highestDamageNum = 0;
    int highestDamagePos = 0;
    int currentDamage = 0;

    if(!m_attackOptions.empty())
    {
        for (int i = 0; i < m_attackOptions.size(); i++)
        {
            if(m_speed > m_attackOptions.at(i)->m_speed + 5)
            {
                currentDamage = 2 * (m_strength - m_attackOptions.at(i)->m_defense);
            }
            else
            {
                currentDamage = m_strength - m_attackOptions.at(i)->m_defense;
            }

            if (currentDamage > highestDamageNum)
            {
                highestDamageNum = currentDamage;
                highestDamagePos = i;
            }
        }

        attack(m_attackOptions.at(highestDamagePos));
    }
}

void enemy::attack(character *_charToAttack)
{

    std::vector<glm::ivec2> attackSpots;
    std::vector<glm::ivec2> moveableAttackSpots;

    bool spotTaken = false;

    attackSpots.push_back(glm::ivec2(_charToAttack->m_coords.x - 1, _charToAttack->m_coords.y));
    attackSpots.push_back(glm::ivec2(_charToAttack->m_coords.x + 1, _charToAttack->m_coords.y));
    attackSpots.push_back(glm::ivec2(_charToAttack->m_coords.x, _charToAttack->m_coords.y - 1));
    attackSpots.push_back(glm::ivec2(_charToAttack->m_coords.x, _charToAttack->m_coords.y + 1));

    for(int i = 0; i < attackSpots.size(); i++)
    {
        spotTaken = false;
        if (std::find(m_moveableCoords.begin(), m_moveableCoords.end(), attackSpots.at(i)) != m_moveableCoords.end())
        {
            for(int j = 0; j < core->characters.size(); j++)
            {
                if(attackSpots.at(i).x == core->characters.at(j)->m_coords.x && attackSpots.at(i).y == core->characters.at(j)->m_coords.y)
                {

                    spotTaken = true;
                }
                if(attackSpots.at(i).x == core->enemies.at(j)->m_coords.x && attackSpots.at(i).y == core->enemies.at(j)->m_coords.y)
                {
                    spotTaken = true;
                }

            }
            if(!spotTaken)
            {
                moveableAttackSpots.push_back(attackSpots.at(i));
            }
        }
    }

    if(!moveableAttackSpots.empty())
    {
        m_coords = moveableAttackSpots.at(0);
        setDestRect(m_coords.x * 70, m_coords.y * 70, 70, 70);
        if(m_speed - 5 > _charToAttack->m_speed)
        {
            _charToAttack->setHealth(-(m_strength - _charToAttack->m_defense));
        }
        _charToAttack->setHealth(-(m_strength - _charToAttack->m_defense));
        setHealth(-(_charToAttack->m_strength - m_defense));
    }
}

enemy::enemy()
{
    m_isAlive = true;

    font tempFont;

    for(int i = 0; i < 2; i++)
    {
        m_strengthNum.m_fonts.push_back(tempFont);
        m_skillNum.m_fonts.push_back(tempFont);
        m_speedNum.m_fonts.push_back(tempFont);
        m_defenseNum.m_fonts.push_back(tempFont);
        m_healthNumMax.m_fonts.push_back(tempFont);
        m_healthNumCurrent.m_fonts.push_back(tempFont);
        m_healthDisplay.m_healthCurrent.m_fonts.push_back(tempFont);
        m_healthDisplay.m_healthMax.m_fonts.push_back(tempFont);
    }
}

void enemy::setHealth(int _change)
{
    m_health += _change;
    if(m_health <= 0)
    {
        m_isAlive = false;
    }
    std::cout << "Enemy Current Health: " << m_health << std::endl;
}

SDL_Rect enemy::setNumDisplay(int _number)
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

void enemy::setNumRects()
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

void enemy::drawStats()
{

    m_strengthNum.m_fonts.at(0).m_SrcRect = setNumDisplay(m_strength / 10);
    m_strengthNum.m_fonts.at(1).m_SrcRect = setNumDisplay(m_strength % 10);

    m_strengthNum.m_fonts.at(0).setDestRect(725, 120, 32, 32);
    m_strengthNum.m_fonts.at(1).setDestRect(757, 120, 32, 32);

    for(int i = 0; i < m_strengthNum.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_strengthNum.m_fonts.at(i).m_texture, &m_strengthNum.m_fonts.at(i).m_SrcRect, &m_strengthNum.m_fonts.at(i).m_DestRect);
    }

    m_skillNum.m_fonts.at(0).m_SrcRect = setNumDisplay(m_skill / 10);
    m_skillNum.m_fonts.at(1).m_SrcRect = setNumDisplay(m_skill % 10);

    m_skillNum.m_fonts.at(0).setDestRect(725, 170, 32, 32);
    m_skillNum.m_fonts.at(1).setDestRect(757, 170, 32, 32);

    for(int i = 0; i < m_skillNum.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_skillNum.m_fonts.at(i).m_texture, &m_skillNum.m_fonts.at(i).m_SrcRect, &m_skillNum.m_fonts.at(i).m_DestRect);
    }

    m_speedNum.m_fonts.at(0).m_SrcRect = setNumDisplay(m_speed / 10);
    m_speedNum.m_fonts.at(1).m_SrcRect = setNumDisplay(m_speed % 10);

    m_speedNum.m_fonts.at(0).setDestRect(725, 220, 32, 32);
    m_speedNum.m_fonts.at(1).setDestRect(757, 220, 32, 32);

    for(int i = 0; i < m_speedNum.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_speedNum.m_fonts.at(i).m_texture, &m_speedNum.m_fonts.at(i).m_SrcRect, &m_speedNum.m_fonts.at(i).m_DestRect);
    }

    m_defenseNum.m_fonts.at(0).m_SrcRect = setNumDisplay(m_defense / 10);
    m_defenseNum.m_fonts.at(1).m_SrcRect = setNumDisplay(m_defense % 10);

    m_defenseNum.m_fonts.at(0).setDestRect(725, 270, 32, 32);
    m_defenseNum.m_fonts.at(1).setDestRect(757, 270, 32, 32);

    for(int i = 0; i < m_defenseNum.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_defenseNum.m_fonts.at(i).m_texture, &m_defenseNum.m_fonts.at(i).m_SrcRect, &m_defenseNum.m_fonts.at(i).m_DestRect);
    }

    m_healthNumCurrent.m_fonts.at(0).m_SrcRect = setNumDisplay(m_health / 10);
    m_healthNumCurrent.m_fonts.at(1).m_SrcRect = setNumDisplay(m_health % 10);

    m_healthNumCurrent.m_fonts.at(0).setDestRect(215, 800, 32, 32);
    m_healthNumCurrent.m_fonts.at(1).setDestRect(247, 800, 32, 32);

    for(int i = 0; i < m_healthNumCurrent.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_healthNumCurrent.m_fonts.at(i).m_texture, &m_healthNumCurrent.m_fonts.at(i).m_SrcRect, &m_healthNumCurrent.m_fonts.at(i).m_DestRect);
    }

    m_healthNumMax.m_fonts.at(0).m_SrcRect = setNumDisplay(m_healthMax / 10);
    m_healthNumMax.m_fonts.at(1).m_SrcRect = setNumDisplay(m_healthMax % 10);

    m_healthNumMax.m_fonts.at(0).setDestRect(285, 800, 32, 32);
    m_healthNumMax.m_fonts.at(1).setDestRect(317, 800, 32, 32);

    for(int i = 0; i < m_healthNumMax.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_healthNumMax.m_fonts.at(i).m_texture, &m_healthNumMax.m_fonts.at(i).m_SrcRect, &m_healthNumMax.m_fonts.at(i).m_DestRect);
    }
}

void enemy::setHealthDisplayNums()
{
    m_healthDisplay.m_healthCurrent.m_fonts.at(0).m_SrcRect = setNumDisplay(m_health / 10);
    m_healthDisplay.m_healthCurrent.m_fonts.at(1).m_SrcRect = setNumDisplay(m_health % 10);

    m_healthDisplay.m_healthCurrent.m_fonts.at(0).setDestRect(130, 1025, 16, 16);
    m_healthDisplay.m_healthCurrent.m_fonts.at(1).setDestRect(146, 1025, 16, 16);

    m_healthDisplay.m_healthMax.m_fonts.at(0).m_SrcRect = setNumDisplay(m_healthMax / 10);
    m_healthDisplay.m_healthMax.m_fonts.at(1).m_SrcRect = setNumDisplay(m_healthMax % 10);

    m_healthDisplay.m_healthMax.m_fonts.at(0).setDestRect(170, 1025, 16, 16);
    m_healthDisplay.m_healthMax.m_fonts.at(1).setDestRect(186, 1025, 16, 16);
}

