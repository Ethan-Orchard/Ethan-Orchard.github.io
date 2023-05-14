//
// Created by Ethan Orchard on 12/05/2023.
//

#include "healthDisplay.h"
#include "core.h"

void healthDisplay::draw(bool _player) {

    //gui::draw();

    SDL_RenderCopy(core->renderer, m_texture, NULL, &m_DestRect);

    if(_player)
    {
        for(int i = 0; i < m_playerWord.m_fonts.size(); i++)
        {
            SDL_RenderCopy(core->renderer, m_playerWord.m_fonts.at(i).m_texture, &m_playerWord.m_fonts.at(i).m_SrcRect, &m_playerWord.m_fonts.at(i).m_DestRect);
        }
    }
    else
    {
        for(int i = 0; i < m_enemyWord.m_fonts.size(); i++)
        {
            SDL_RenderCopy(core->renderer, m_enemyWord.m_fonts.at(i).m_texture, &m_enemyWord.m_fonts.at(i).m_SrcRect, &m_enemyWord.m_fonts.at(i).m_DestRect);
        }
    }

    for(int i = 0; i < m_healthWord.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_healthWord.m_fonts.at(i).m_texture, &m_healthWord.m_fonts.at(i).m_SrcRect, &m_healthWord.m_fonts.at(i).m_DestRect);
    }

    for(int i = 0; i < 2; i++)
    {
        SDL_RenderCopy(core->renderer, m_healthCurrent.m_fonts.at(i).m_texture, &m_healthCurrent.m_fonts.at(i).m_SrcRect, &m_healthCurrent.m_fonts.at(i).m_DestRect);
        SDL_RenderCopy(core->renderer, m_healthMax.m_fonts.at(i).m_texture, &m_healthMax.m_fonts.at(i).m_SrcRect, &m_healthMax.m_fonts.at(i).m_DestRect);
    }
}

healthDisplay::healthDisplay()
{

    setDestRect(0, 900, 250, 250);

    font tempFont;

    for (int i = 0; i < 6; i++)
    {
        m_playerWord.m_fonts.push_back(tempFont);
        m_healthWord.m_fonts.push_back(tempFont);
    }

    for(int i = 0; i < 5; i++)
    {
        m_enemyWord.m_fonts.push_back(tempFont);
    }

    m_playerWord.m_fonts.at(0).setSrcRect(41, 32, 16, 16);
    m_playerWord.m_fonts.at(0).setDestRect(50, 925, 32, 32);

    m_playerWord.m_fonts.at(1).setSrcRect(185, 16, 16, 16);
    m_playerWord.m_fonts.at(1).setDestRect(82, 925, 32, 32);

    m_playerWord.m_fonts.at(2).setSrcRect(9, 16, 16, 16);
    m_playerWord.m_fonts.at(2).setDestRect(114, 925, 32, 32);

    m_playerWord.m_fonts.at(3).setSrcRect(185, 32, 16, 16);
    m_playerWord.m_fonts.at(3).setDestRect(146, 925, 32, 32);

    m_playerWord.m_fonts.at(4).setSrcRect(73, 16, 16, 16);
    m_playerWord.m_fonts.at(4).setDestRect(178, 925, 32, 32);

    m_playerWord.m_fonts.at(5).setSrcRect(73, 32, 16, 16);
    m_playerWord.m_fonts.at(5).setDestRect(210, 925, 32, 32);



    m_healthWord.m_fonts.at(0).setSrcRect(121, 16, 16, 16);
    m_healthWord.m_fonts.at(0).setDestRect(15, 1025, 16, 16);

    m_healthWord.m_fonts.at(1).setSrcRect(73, 16, 16, 16);
    m_healthWord.m_fonts.at(1).setDestRect(31, 1025, 16, 16);

    m_healthWord.m_fonts.at(2).setSrcRect(9, 16, 16, 16);
    m_healthWord.m_fonts.at(2).setDestRect(47, 1025, 16, 16);

    m_healthWord.m_fonts.at(3).setSrcRect(185, 16, 16, 16);
    m_healthWord.m_fonts.at(3).setDestRect(63, 1025, 16, 16);

    m_healthWord.m_fonts.at(4).setSrcRect(105, 32, 16, 16);
    m_healthWord.m_fonts.at(4).setDestRect(79, 1025, 16, 16);

    m_healthWord.m_fonts.at(5).setSrcRect(121, 16, 16, 16);
    m_healthWord.m_fonts.at(5).setDestRect(95, 1025, 16, 16);



    m_enemyWord.m_fonts.at(0).setSrcRect(73, 16, 16, 16);
    m_enemyWord.m_fonts.at(0).setDestRect(50, 925, 32, 32);

    m_enemyWord.m_fonts.at(1).setSrcRect(9, 32, 16, 16);
    m_enemyWord.m_fonts.at(1).setDestRect(82, 925, 32, 32);

    m_enemyWord.m_fonts.at(2).setSrcRect(73, 16, 16, 16);
    m_enemyWord.m_fonts.at(2).setDestRect(114, 925, 32, 32);

    m_enemyWord.m_fonts.at(3).setSrcRect(201, 16, 16, 16);
    m_enemyWord.m_fonts.at(3).setDestRect(146, 925, 32, 32);

    m_enemyWord.m_fonts.at(4).setSrcRect(185, 32, 16, 16);
    m_enemyWord.m_fonts.at(4).setDestRect(178, 925, 32, 32);
}
