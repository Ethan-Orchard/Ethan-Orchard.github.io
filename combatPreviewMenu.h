//
// Created by Ethan Orchard on 11/05/2023.
//

#ifndef FEC_COMBATPREVIEWMENU_H
#define FEC_COMBATPREVIEWMENU_H

#include "menu.h"
#include "word.h"

class combatPreviewMenu : public menu {

public:

    combatPreviewMenu();

    void update(SDL_Keysym _key);

    word m_damageWord;
    word m_healthWord;
    word m_doubleWord;

    word m_damageNumPlayer;
    word m_healthNumPlayer;
    word m_doubleNumPlayer;

    word m_damageNumEnemy;
    word m_healthNumEnemy;
    word m_doubleNumEnemy;

    SDL_Rect zeroSrcRect;
    SDL_Rect oneSrcRect;
    SDL_Rect twoSrcRect;
    SDL_Rect threeSrcRect;
    SDL_Rect fourSrcRect;
    SDL_Rect fiveSrcRect;
    SDL_Rect sixSrcRect;
    SDL_Rect sevenSrcRect;
    SDL_Rect eightSrcRect;
    SDL_Rect nineSrcRect;

    void draw();

    void createCursor();

    void loadWordTextures();

    void setPlayerNums(int _damage, int _health, bool _double);

    void setEnemyNums(int _damage, int _health, bool _double);

    SDL_Rect setNumDisplay(int _number);

    void resetCursor();

    void setNumRects();

};


#endif //FEC_COMBATPREVIEWMENU_H
