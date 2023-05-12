//
// Created by Ethan Orchard on 12/05/2023.
//

#ifndef FEC_HEALTHDISPLAY_H
#define FEC_HEALTHDISPLAY_H

#include "gui.h"
#include "word.h"

class healthDisplay : public gui {

public:

    healthDisplay();

    SDL_Texture* m_texture;

    void draw(bool _player);

    word m_healthCurrent;
    word m_healthMax;

    word m_healthWord;
    word m_playerWord;
    word m_enemyWord;

};


#endif //FEC_HEALTHDISPLAY_H
