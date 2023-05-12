//
// Created by Ethan Orchard on 29/03/2023.
//

#pragma once

#ifndef FEC_CORE_H
#define FEC_CORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <fstream>

#include "tile.h"
#include "character.h"
#include "object.h"
#include "cursor.h"
#include "gui.h"
#include "characterData.h"
#include "font.h"
#include "menu.h"
#include "waitMenu.h"
#include "attackMenu.h"
#include "enemy.h"
#include "item.h"
#include "weapon.h"
#include "word.h"
#include "combatPreviewMenu.h"
#include "healthDisplay.h"


class core{
public:


    core();

    void run();
    void loop();
    static void s_loop(void* user_data);

    SDL_Texture* load_texture(const std::string& _path);

    bool check_move_collision(std::vector<character*> _characters, character* _selected_character, std::vector<enemy*>);

    bool check_top_bound_move(character* _selected_character);
    bool check_right_bound_move(character* _selected_character);
    bool check_left_bound_move(character* _selected_character);
    bool check_bottom_bound_move(character* _selected_character);

    void createCharacter(character* _character, std::string _fileName);

    void createEnemy(enemy* _enemy);

    void createTile();

    std::vector<std::string> stripWhitespaces(std::string _string);

    SDL_Renderer* renderer;
    tile map[225];
    tile moveRangeMap[225];

    int mapSize;

    std::vector<character*> characters;

    std::vector<enemy*> enemies;

    character char1;
    character char2;
    character char3;

    enemy enemy1;

    character* selectedCharacter;

    bool quit;

    cursor cursor;

    gui inventory;

    waitMenu waitMenu;
    attackMenu attackMenu;
    combatPreviewMenu combatPreviewMenu;

    int menuOptionSelected;

    menu* selectedMenu;

    glm::ivec2 map_Boundary;
    glm::ivec2 display_Boundary;

    std::vector<font> m_fonts;

    int gamestate;

    gui m_enemyPhasePopUp;
    gui m_playerPhasePopUp;

    bool m_enemyPhase;

    font m_letters;

    word m_strengthWord;
    word m_skillWord;
    word m_speedWord;
    word m_defenseWord;
    word m_healthWord;


private:

};


#endif //FEC_CORE_H
