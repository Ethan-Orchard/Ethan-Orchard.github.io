//
// Created by Ethan Orchard on 24/04/2023.
//

#ifndef FEC_MENU_H
#define FEC_MENU_H

#include "gui.h"
#include "cursor.h"

class menu : public gui {

public:
    virtual void update(SDL_Keysym _key);
    virtual void resetCursor();

    int getOptionSelected(bool _freeHandling);

    int m_optionHighlighted;
    int m_optionSelected;
    int m_tempOptionSelected;

    cursor m_cursor;
};


#endif //FEC_MENU_H
