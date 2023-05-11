//
// Created by Ethan Orchard on 24/04/2023.
//

#ifndef FEC_WAITMENU_H
#define FEC_WAITMENU_H

#include "menu.h"

class waitMenu : public menu {

public:

    waitMenu();

    void update(SDL_Keysym _key);

    void draw();

    void createCursor();

    void resetCursor();

};


#endif //FEC_WAITMENU_H
