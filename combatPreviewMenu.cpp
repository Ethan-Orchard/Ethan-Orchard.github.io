//
// Created by Ethan Orchard on 11/05/2023.
//

#include "combatPreviewMenu.h"
#include "core.h"

combatPreviewMenu::combatPreviewMenu()
{

    m_optionSelected = 0;

    setNumRects();

    font tempFont;

    for (int i = 0; i < 6; i++)
    {
        m_damageWord.m_fonts.push_back(tempFont);
    }

    m_damageWord.m_fonts.at(0).setSrcRect(57, 16, 16, 16);
    m_damageWord.m_fonts.at(0).setDestRect(150, 50, 32, 32);

    m_damageWord.m_fonts.at(1).setSrcRect(9, 16, 16, 16);
    m_damageWord.m_fonts.at(1).setDestRect(182, 50, 32, 32);

    m_damageWord.m_fonts.at(2).setSrcRect(201, 16, 16, 16);
    m_damageWord.m_fonts.at(2).setDestRect(214, 50, 32, 32);

    m_damageWord.m_fonts.at(3).setSrcRect(9, 16, 16, 16);
    m_damageWord.m_fonts.at(3).setDestRect(246, 50, 32, 32);

    m_damageWord.m_fonts.at(4).setSrcRect(105, 16, 16, 16);
    m_damageWord.m_fonts.at(4).setDestRect(278, 50, 32, 32);

    m_damageWord.m_fonts.at(5).setSrcRect(73, 16, 16, 16);
    m_damageWord.m_fonts.at(5).setDestRect(310, 50, 32, 32);

    for(int i = 0; i < 6; i++)
    {
        m_healthWord.m_fonts.push_back(tempFont);
    }

    m_healthWord.m_fonts.at(0).setSrcRect(121, 16, 16, 16);
    m_healthWord.m_fonts.at(0).setDestRect(150, 100, 32, 32);

    m_healthWord.m_fonts.at(1).setSrcRect(73, 16, 16, 16);
    m_healthWord.m_fonts.at(1).setDestRect(182, 100, 32, 32);

    m_healthWord.m_fonts.at(2).setSrcRect(9, 16, 16, 16);
    m_healthWord.m_fonts.at(2).setDestRect(214, 100, 32, 32);

    m_healthWord.m_fonts.at(3).setSrcRect(185, 16, 16, 16);
    m_healthWord.m_fonts.at(3).setDestRect(246, 100, 32, 32);

    m_healthWord.m_fonts.at(4).setSrcRect(105, 32, 16, 16);
    m_healthWord.m_fonts.at(4).setDestRect(278, 100, 32, 32);

    m_healthWord.m_fonts.at(5).setSrcRect(121, 16, 16, 16);
    m_healthWord.m_fonts.at(5).setDestRect(310, 100, 32, 32);

    for(int i = 0; i < 6; i++)
    {
        m_doubleWord.m_fonts.push_back(tempFont);
    }

    m_doubleWord.m_fonts.at(0).setSrcRect(57, 16, 16, 16);
    m_doubleWord.m_fonts.at(0).setDestRect(150, 150, 32, 32);

    m_doubleWord.m_fonts.at(1).setSrcRect(25, 32, 16, 16);
    m_doubleWord.m_fonts.at(1).setDestRect(182, 150, 32, 32);

    m_doubleWord.m_fonts.at(2).setSrcRect(121, 32, 16, 16);
    m_doubleWord.m_fonts.at(2).setDestRect(214, 150, 32, 32);

    m_doubleWord.m_fonts.at(3).setSrcRect(25, 16, 16, 16);
    m_doubleWord.m_fonts.at(3).setDestRect(246, 150, 32, 32);

    m_doubleWord.m_fonts.at(4).setSrcRect(185, 16, 16, 16);
    m_doubleWord.m_fonts.at(4).setDestRect(278, 150, 32, 32);

    m_doubleWord.m_fonts.at(5).setSrcRect(73, 16, 16, 16);
    m_doubleWord.m_fonts.at(5).setDestRect(310, 150, 32, 32);

    for(int i = 0; i < 2; i++)
    {
        m_damageNumPlayer.m_fonts.push_back(tempFont);
        m_healthNumPlayer.m_fonts.push_back(tempFont);
        m_doubleNumPlayer.m_fonts.push_back(tempFont);
        m_damageNumEnemy.m_fonts.push_back(tempFont);
        m_healthNumEnemy.m_fonts.push_back(tempFont);
        m_doubleNumEnemy.m_fonts.push_back(tempFont);
    }

    m_damageNumPlayer.m_fonts.at(0).setDestRect(400, 50, 32, 32);
    m_damageNumPlayer.m_fonts.at(1).setDestRect(432, 50, 32, 32);

    m_damageNumEnemy.m_fonts.at(0).setDestRect(500, 50, 32,32);
    m_damageNumEnemy.m_fonts.at(1).setDestRect(532, 50, 32,32);

    m_healthNumPlayer.m_fonts.at(0).setDestRect(400, 100, 32, 32);
    m_healthNumPlayer.m_fonts.at(1).setDestRect(432, 100, 32, 32);

    m_healthNumEnemy.m_fonts.at(0).setDestRect(500, 100, 32, 32);
    m_healthNumEnemy.m_fonts.at(1).setDestRect(532, 100, 32, 32);

    m_doubleNumPlayer.m_fonts.at(0).setDestRect(400, 150, 32, 32);
    m_doubleNumEnemy.m_fonts.at(0).setDestRect(500, 150, 32, 32);
}

void combatPreviewMenu::update(SDL_Keysym _key)
{
    menu::update(_key);

    switch(_key.sym)
    {
        case SDLK_x:
            core->selectedCharacter->attack();
            if(core->selectedCharacter->checkExperience())
            {
                core->selectedCharacter->levelUp();
            }
            core->selectedCharacter->m_hasMoved = true;
            core->cursor.m_DestRect = core->selectedCharacter->m_DestRect;
            core->cursor.m_coords.x = core->selectedCharacter->m_coords.x;
            core->cursor.m_coords.y = core->selectedCharacter->m_coords.y;

            core->selectedCharacter = nullptr;

            for (int i = 0; i < 225; i++)
            {
                core->moveRangeMap[i].m_draw = false;
            }

        case SDLK_c:
            core->selectedMenu = &core->attackMenu;
    }
}

void combatPreviewMenu::createCursor()
{
    m_cursor.m_tex = core->load_texture("assets/cursor.png");
    m_cursor.setSrcRect(60, 0, 20, 20);
    m_cursor.setDestRect(215, 25, 40, 25);
}

void combatPreviewMenu::draw()
{
    gui::draw();

    SDL_RenderCopy(core->renderer, m_texture, NULL, &m_DestRect);

    enemy* _enemy;

    _enemy = core->selectedCharacter->findEnemyToAttack();

    if(core->selectedCharacter->m_speed - 5 > _enemy->m_speed)
    {
        setPlayerNums(core->selectedCharacter->m_strength - _enemy->m_defense, core->selectedCharacter->m_health, true);
    }
    else
    {
        setPlayerNums(core->selectedCharacter->m_strength - _enemy->m_defense, core->selectedCharacter->m_health, false);
    }


    if(_enemy->m_speed - 5 > core->selectedCharacter->m_speed)
    {
        setEnemyNums(_enemy->m_strength - core->selectedCharacter->m_defense, _enemy->m_health, true);
    }
    else
    {
        setEnemyNums(_enemy->m_strength - core->selectedCharacter->m_defense, _enemy->m_health, false);
    }

    for(int i = 0; i < m_damageWord.m_fonts.size(); i++)
    {
        SDL_RenderCopy(core->renderer, m_damageWord.m_fonts.at(i).m_texture, &m_damageWord.m_fonts.at(i).m_SrcRect, &m_damageWord.m_fonts.at(i).m_DestRect);
        SDL_RenderCopy(core->renderer, m_healthWord.m_fonts.at(i).m_texture, &m_healthWord.m_fonts.at(i).m_SrcRect, &m_healthWord.m_fonts.at(i).m_DestRect);
        SDL_RenderCopy(core->renderer, m_doubleWord.m_fonts.at(i).m_texture, &m_doubleWord.m_fonts.at(i).m_SrcRect, &m_doubleWord.m_fonts.at(i).m_DestRect);
    }

    for(int i = 0; i < 2; i++)
    {
        SDL_RenderCopy(core->renderer, m_damageNumPlayer.m_fonts.at(i).m_texture, &m_damageNumPlayer.m_fonts.at(i).m_SrcRect, &m_damageNumPlayer.m_fonts.at(i).m_DestRect);
        SDL_RenderCopy(core->renderer, m_damageNumEnemy.m_fonts.at(i).m_texture, &m_damageNumEnemy.m_fonts.at(i).m_SrcRect, &m_damageNumEnemy.m_fonts.at(i).m_DestRect);
        SDL_RenderCopy(core->renderer, m_healthNumPlayer.m_fonts.at(i).m_texture, &m_healthNumPlayer.m_fonts.at(i).m_SrcRect, &m_healthNumPlayer.m_fonts.at(i).m_DestRect);
        SDL_RenderCopy(core->renderer, m_healthNumEnemy.m_fonts.at(i).m_texture, &m_healthNumEnemy.m_fonts.at(i).m_SrcRect, &m_healthNumEnemy.m_fonts.at(i).m_DestRect);
    }

    SDL_RenderCopy(core->renderer, m_doubleNumPlayer.m_fonts.at(0).m_texture, &m_doubleNumPlayer.m_fonts.at(0).m_SrcRect, &m_doubleNumPlayer.m_fonts.at(0).m_DestRect);
    SDL_RenderCopy(core->renderer, m_doubleNumEnemy.m_fonts.at(0).m_texture, &m_doubleNumEnemy.m_fonts.at(0).m_SrcRect, &m_doubleNumEnemy.m_fonts.at(0).m_DestRect);
}

void combatPreviewMenu::resetCursor() {
    menu::resetCursor();
}

void combatPreviewMenu::setNumRects()
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

void combatPreviewMenu::setPlayerNums(int _damage, int _health, bool _double)
{
    m_damageNumPlayer.m_fonts.at(0).m_SrcRect = setNumDisplay(_damage / 10);
    m_damageNumPlayer.m_fonts.at(1).m_SrcRect = setNumDisplay(_damage % 10);

    m_healthNumPlayer.m_fonts.at(0).m_SrcRect = setNumDisplay(_health / 10);
    m_healthNumPlayer.m_fonts.at(1).m_SrcRect = setNumDisplay(_health % 10);


    if(_double)
    {
        m_doubleNumPlayer.m_fonts.at(0).setSrcRect(188, 32, 16, 16);
    }
    else
    {
        m_doubleNumPlayer.m_fonts.at(0).setSrcRect(9, 32, 16, 16);
    }

}

SDL_Rect combatPreviewMenu::setNumDisplay(int _number)
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

void combatPreviewMenu::setEnemyNums(int _damage, int _health, bool _double)
{
    m_damageNumEnemy.m_fonts.at(0).m_SrcRect = setNumDisplay(_damage / 10);
    m_damageNumEnemy.m_fonts.at(1).m_SrcRect = setNumDisplay(_damage % 10);

    m_healthNumEnemy.m_fonts.at(0).m_SrcRect = setNumDisplay(_health / 10);
    m_healthNumEnemy.m_fonts.at(1).m_SrcRect = setNumDisplay(_health % 10);


    if(_double)
    {
        m_doubleNumEnemy.m_fonts.at(0).setSrcRect(188, 32, 16, 16);
    }
    else
    {
        m_doubleNumEnemy.m_fonts.at(0).setSrcRect(9, 32, 16, 16);
    }
}

void combatPreviewMenu::loadWordTextures()
{
    for (int i = 0; i < m_damageWord.m_fonts.size(); i++)
    {
        m_damageWord.m_fonts.at(i).m_texture = core->load_texture("assets/font2.png");
    }
    for(int i = 0; i < m_healthWord.m_fonts.size(); i++)
    {
        m_healthWord.m_fonts.at(i).m_srcImage = "assets/font2.png";
        m_healthWord.m_fonts.at(i).m_texture = core->load_texture(m_healthWord.m_fonts.at(i).m_srcImage);
    }
    for(int i = 0; i < m_doubleWord.m_fonts.size(); i++)
    {
        m_doubleWord.m_fonts.at(i).m_texture = core->load_texture("assets/font2.png");
    }
    for(int i = 0; i < 2; i++)
    {
        m_damageNumPlayer.m_fonts.at(i).m_texture = core->load_texture("assets/font.png");
        m_healthNumPlayer.m_fonts.at(i).m_texture = core->load_texture("assets/font.png");
        m_damageNumEnemy.m_fonts.at(i).m_texture = core->load_texture("assets/font.png");
        m_healthNumEnemy.m_fonts.at(i).m_texture = core->load_texture("assets/font.png");
    }

    m_doubleNumPlayer.m_fonts.at(0).m_texture = core->load_texture("assets/font2.png");
    m_doubleNumEnemy.m_fonts.at(0).m_texture = core->load_texture("assets/font2.png");
}
