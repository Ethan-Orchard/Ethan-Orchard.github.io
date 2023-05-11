//
// Created by Ethan Orchard on 24/04/2023.
//

#ifndef FEC_ATTACKMENU_H
#define FEC_ATTACKMENU_H

#include "menu.h"

class attackMenu : public menu {

public:

    attackMenu();

    void update(SDL_Keysym _key);

    void draw();

    void createCursor();

    void resetCursor();
};


#endif //FEC_ATTACKMENU_H
