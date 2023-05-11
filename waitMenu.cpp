//
// Created by Ethan Orchard on 24/04/2023.
//

#include "waitMenu.h"

#include "core.h"

void waitMenu::update(SDL_Keysym _key)
{
    menu::update(_key);

    switch(_key.sym)
    {
        case SDLK_UP:
            if(m_optionHighlighted == 2)
            {
                m_optionHighlighted = 1;
                m_cursor.move(0, -60);
            }
            break;

        case SDLK_DOWN:
            if(m_optionHighlighted == 1)
            {
                m_optionHighlighted = 2;
                m_cursor.move(0, 60);
            }
            break;

        case SDLK_x:
            if(m_optionHighlighted == 1)
            {
                core->selectedCharacter->m_showInventory = true;
                m_optionSelected = 1;
                std::cout << "option 1 selected" << std::endl;

            }
            else if(m_optionHighlighted == 2)
            {
                core->selectedCharacter->m_hasMoved = true;
                m_optionSelected = 2;
                core->cursor.m_DestRect = core->selectedCharacter->m_DestRect;
                core->cursor.m_coords.x = core->selectedCharacter->m_coords.x;
                core->cursor.m_coords.y = core->selectedCharacter->m_coords.y;

                core->selectedCharacter = nullptr;

                for (int i = 0; i < 225; i++)
                {
                    core->moveRangeMap[i].m_draw = false;
                }
            }
    }
}

waitMenu::waitMenu()
{
    m_optionSelected = 0;
    m_optionHighlighted = 1;
}

void waitMenu::draw()
{
    gui::draw();
    SDL_RenderCopy(core->renderer, m_texture, NULL, &m_DestRect);
    SDL_RenderCopy(core->renderer, m_cursor.m_tex, &m_cursor.m_SrcRect, &m_cursor.m_DestRect);
}

void waitMenu::createCursor()
{
    m_cursor.m_tex = core->load_texture("assets/cursor.png");
    m_cursor.setSrcRect(60, 0, 20, 20);
    m_cursor.setDestRect(215, 35, 40, 25);
}

void waitMenu::resetCursor()
{
    menu::resetCursor();

    m_cursor.setSrcRect(60, 0, 20, 20);
    m_cursor.setDestRect(215, 35, 40, 25);
}

