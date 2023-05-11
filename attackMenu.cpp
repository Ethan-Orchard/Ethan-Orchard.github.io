//
// Created by Ethan Orchard on 24/04/2023.
//

#include "attackMenu.h"
#include "core.h"

attackMenu::attackMenu()
{
    m_optionSelected = 0;
    m_optionHighlighted = 1;
}

void attackMenu::update(SDL_Keysym _key)
{
    menu::update(_key);

    switch (_key.sym)
    {
        case SDLK_UP:
            if(m_optionHighlighted == 2)
            {
                m_optionHighlighted = 1;
                m_cursor.move(0, -40);
            }
            else if(m_optionHighlighted == 3)
            {
                m_optionHighlighted = 2;
                m_cursor.move(0, -40);
            }
            break;

        case SDLK_DOWN:
            if(m_optionHighlighted == 1)
            {
                m_optionHighlighted = 2;
                m_cursor.move(0, 40);
            }
            else if(m_optionHighlighted == 2)
            {
                m_optionHighlighted = 3;
                m_cursor.move(0, 40);
            }
            break;

        case SDLK_x:
            if(m_optionHighlighted == 1)
            {
                m_optionSelected = 1;
                std::cout << "option 1 selection attack menu" << std::endl;
                core->selectedMenu = &core->combatPreviewMenu;
            }
            else if(m_optionHighlighted == 2)
            {
                m_optionSelected = 2;
                core->selectedCharacter->m_showInventory = true;
            }
            else if(m_optionHighlighted == 3)
            {
                m_optionSelected = 3;
                core->selectedCharacter->m_hasMoved = true;
                core->cursor.m_DestRect = core->selectedCharacter->m_DestRect;
                core->cursor.m_coords.x = core->selectedCharacter->m_coords.x;
                core->cursor.m_coords.y = core->selectedCharacter->m_coords.y;

                core->selectedCharacter = nullptr;

                for (int i = 0; i < 225; i++)
                {
                    core->moveRangeMap[i].m_draw = false;
                }
            }
            break;
    }
}

void attackMenu::draw()
{
    gui::draw();

    SDL_RenderCopy(core->renderer, m_texture, NULL, &m_DestRect);
    SDL_RenderCopy(core->renderer, m_cursor.m_tex, &m_cursor.m_SrcRect, &m_cursor.m_DestRect);
}

void attackMenu::createCursor()
{
    m_cursor.m_tex = core->load_texture("assets/cursor.png");
    m_cursor.setSrcRect(60, 0, 20, 20);
    m_cursor.setDestRect(215, 25, 40, 25);
}

void attackMenu::resetCursor()
{
    menu::resetCursor();

    m_cursor.setSrcRect(60, 0, 20, 20);
    m_cursor.setDestRect(215, 25, 40, 25);
}
