//
// Created by Ethan Orchard on 24/04/2023.
//

#include "menu.h"
#include "core.h"

void menu::update(SDL_Keysym _key) {

}

int menu::getOptionSelected(bool _freeHandling)
{

    m_tempOptionSelected = 0;

    if (m_optionSelected != 0)
    {
        std::cout << "resetting selected menu" << std::endl;
        m_tempOptionSelected = core->selectedMenu->m_optionSelected;
        core->selectedMenu->m_optionSelected = 0;
        core->selectedMenu->m_optionHighlighted = 1;
        core->selectedMenu->resetCursor();
        core->selectedMenu = nullptr;
        _freeHandling = true;

    }
    return m_tempOptionSelected;
}

void menu::resetCursor()
{

}
