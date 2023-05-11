//
// Created by Ethan Orchard on 29/03/2023.
//
#ifdef __EMSCRIPTEN__

#include <emscripten.h>

#endif


#include "core.h"



core::core()
{
    std::cout << "checkpoint 5" << std::endl;

    SDL_Window* window = SDL_CreateWindow("FEC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1050, 1050, SDL_WINDOW_RESIZABLE);

    std::cout << "checkpoint 6" << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    std::cout << "checkpoint 7" << std::endl;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    std::cout << "checkpoint 8" << std::endl;
}

void core::loop()
{

    int charsMoved = 0;

    m_enemyPhase = false;

    for(int i = 0; i < characters.size(); i++)
    {
        if(characters.at(i)->m_hasMoved)
        {
            charsMoved++;
        }
    }

    if(charsMoved == characters.size())
    {
        m_enemyPhasePopUp.draw();
        std::cout << "turn reset" << std::endl;
        for(int i = 0; i < enemies.size(); i++)
        {
            enemies.at(i)->update();
        }
        for (int i = 0; i < characters.size(); i++)
        {
            characters.at(i)->m_hasMoved = false;
        }
        m_playerPhasePopUp.draw();
        m_enemyPhase = true;
    }
    else
    {
        m_enemyPhase = false;
    }

    SDL_Event e = {0};
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

        if (e.type == SDL_KEYDOWN)
        {
            bool freeHandling = true;
            if (selectedMenu != nullptr)
            {
                freeHandling = false;
                std::cout << "menu should be open" << std::endl;
                selectedMenu->update(e.key.keysym);
                menuOptionSelected = selectedMenu->getOptionSelected(freeHandling);
                if(menuOptionSelected != 0)
                {
                    selectedMenu = nullptr;
                }
                std::cout << "menu option selected: " << menuOptionSelected << std::endl;
            }
            if(freeHandling)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;

                    case SDLK_LEFT:
                        if (selectedCharacter != nullptr)
                        {
                            if (check_left_bound_move(selectedCharacter))
                            {
                                selectedCharacter->move(-70, 0);
                                selectedCharacter->m_coords.x -= 1;
                                selectedCharacter->m_SrcRect = selectedCharacter->m_leftFacing;
                                selectedCharacter->m_directionFacing = 2;

                                if (check_move_collision(characters, selectedCharacter, enemies))
                                {
                                    selectedCharacter->move(70, 0);
                                    selectedCharacter->m_coords.x += 1;
                                }
                            }
                        }
                        else
                        {
                            if ((cursor.m_coords.x - 1) >= 0)
                            {
                                cursor.move(-70, 0);
                                cursor.m_coords.x -= 1;
                            }
                        }
                        break;

                    case SDLK_RIGHT:
                        if (selectedCharacter != nullptr)
                        {
                            if (check_right_bound_move(selectedCharacter))
                            {
                                selectedCharacter->move(70, 0);
                                selectedCharacter->m_coords.x += 1;
                                selectedCharacter->m_SrcRect = selectedCharacter->m_rightFacing;
                                selectedCharacter->m_directionFacing = 3;
                                if (check_move_collision(characters, selectedCharacter, enemies))
                                {
                                    selectedCharacter->move(-70, 0);
                                    selectedCharacter->m_coords.x -= 1;
                                }
                            }
                        }
                        else
                        {
                            if ((cursor.m_coords.x + 1) <= map_Boundary.x)
                            {
                                cursor.move(70, 0);
                                cursor.m_coords.x += 1;
                            }
                        }
                        break;

                    case SDLK_UP:
                        if (selectedCharacter != nullptr)
                        {
                            if (check_top_bound_move(selectedCharacter))
                            {
                                selectedCharacter->move(0, -70);
                                selectedCharacter->m_coords.y -= 1;
                                selectedCharacter->m_SrcRect = selectedCharacter->m_backFacing;
                                selectedCharacter->m_directionFacing = 1;
                                if (check_move_collision(characters, selectedCharacter, enemies))
                                {
                                    selectedCharacter->move(0, 70);
                                    selectedCharacter->m_coords.y += 1;
                                }
                            }
                        }
                        else
                        {
                            if ((cursor.m_coords.y - 1) >= 0)
                            {
                                cursor.move(0, -70);
                                cursor.m_coords.y -= 1;
                            }
                        }
                        break;

                    case SDLK_DOWN:
                        if (selectedCharacter != nullptr)
                        {
                            if (check_bottom_bound_move(selectedCharacter))
                            {
                                selectedCharacter->move(0, 70);
                                selectedCharacter->m_coords.y += 1;
                                selectedCharacter->m_SrcRect = selectedCharacter->m_frontFacing;
                                selectedCharacter->m_directionFacing = 4;
                                if (check_move_collision(characters, selectedCharacter, enemies))
                                {
                                    selectedCharacter->move(0, -70);
                                    selectedCharacter->m_coords.y -= 1;
                                }
                            }
                        }
                        else
                        {
                            if ((cursor.m_coords.y + 1) <= map_Boundary.y)
                            {
                                cursor.move(0, 70);
                                cursor.m_coords.y += 1;
                            }
                        }
                        break;

                    case SDLK_x:
                        if (selectedCharacter == nullptr)
                        {
                            for (int i = 0; i < characters.size(); i++)
                            {
                                if (cursor.m_coords.x == characters.at(i)->m_coords.x && cursor.m_coords.y == characters.at(i)->m_coords.y)
                                {
                                    if (!characters.at(i)->m_hasMoved)
                                    {
                                        selectedCharacter = characters.at(i);
                                        selectedCharacter->m_startingCoords = characters.at(i)->m_DestRect;
                                        selectedCharacter->m_moveableCoords = selectedCharacter->findMoveBoundary(map_Boundary);
                                    }
                                    else
                                    {
                                        std::cout << "This character has moved this turn" << std::endl;
                                    }
                                }
                            }
                            for(int i = 0; i < enemies.size(); i++)
                            {
                                if (cursor.m_coords.x == enemies.at(i)->m_coords.x && cursor.m_coords.y == enemies.at(i)->m_coords.y)
                                {
                                    enemies.at(i)->m_showInventory = true;
                                }
                            }
                        }
                        else
                        {
                            if(selectedCharacter->checkAttackRange())
                            {
                                selectedMenu = &attackMenu;
                            }
                            else
                            {
                                selectedMenu = &waitMenu;
                            }
                        }
                        break;

                    case SDLK_c:
                        for(int i = 0; i < enemies.size(); i++)
                        {
                            enemies.at(i)->m_showInventory = false;
                        }
                        if(selectedCharacter != nullptr)
                        {
                            if(selectedCharacter->m_showInventory)
                            {
                                selectedCharacter->m_showInventory = false;
                            }
                        }
                        if (selectedCharacter != nullptr)
                        {
                            selectedCharacter->m_DestRect = selectedCharacter->m_startingCoords;
                            selectedCharacter->m_coords.x = selectedCharacter->m_startingCoords.x / 70;
                            selectedCharacter->m_coords.y = selectedCharacter->m_startingCoords.y / 70;
                            selectedCharacter->m_directionFacing = selectedCharacter->m_startingDirection;

                            switch (selectedCharacter->m_startingDirection) {
                                case 1:
                                    selectedCharacter->m_SrcRect = selectedCharacter->m_frontFacing;
                                    break;

                                case 2:
                                    selectedCharacter->m_SrcRect = selectedCharacter->m_leftFacing;
                                    break;

                                case 3:
                                    selectedCharacter->m_SrcRect = selectedCharacter->m_rightFacing;
                                    break;

                                case 4:
                                    selectedCharacter->m_SrcRect = selectedCharacter->m_backFacing;
                                    break;
                            }


                            cursor.m_DestRect = selectedCharacter->m_startingCoords;
                            cursor.m_coords.x = selectedCharacter->m_startingCoords.x / 70;
                            cursor.m_coords.y = selectedCharacter->m_startingCoords.y / 70;

                            for (int i = 0; i < 225; i++) {
                                moveRangeMap[i].m_draw = false;
                            }
                            selectedCharacter = nullptr;
                        }
                        break;

                    case SDLK_m:
                        if(selectedCharacter != nullptr)
                        {
                            selectedCharacter->attack();
                        }
                        break;

                    case SDLK_n:
                        for(int i = 0; i < enemies.size(); i++)
                        {
                            enemies.at(i)->update();
                        }
                        break;

                    case SDLK_r:
                        for (int i = 0; i < characters.size(); i++) {
                            characters.at(i)->m_hasMoved = false;
                        }
                        break;

                    case SDLK_e:
                        if (selectedCharacter != nullptr) {
                            if (selectedCharacter->m_showInventory) {
                                selectedCharacter->m_showInventory = false;
                            } else {
                                selectedCharacter->m_showInventory = true;
                            }
                        }
                        break;
                }
            }
        }
    }

    SDL_RenderClear(renderer);

    for(int i = 0; i < 225; i++)
    {
        SDL_RenderCopy(renderer, map[i].m_texture, &map[i].m_SrcRect, &map[i].m_DestRect);
    }

    for (int i = 0; i < characters.size(); i++)
    {
        if(characters.at(i) == selectedCharacter)
        {
            characters.at(i)->showMoveRange(moveRangeMap);
        }
    }

    for(int i = 0; i < 225; i++)
    {
        if (moveRangeMap[i].m_draw)
        {
            SDL_RenderCopy(renderer, moveRangeMap[i].m_texture, &moveRangeMap[i].m_SrcRect, &moveRangeMap[i].m_DestRect);
        }
    }
    for (int i = 0; i < characters.size(); i++)
    {
        if (characters.at(i)->m_isAlive)
        {
            SDL_RenderCopy(renderer, characters.at(i)->m_texture, &characters.at(i)->m_SrcRect, &characters.at(i)->m_DestRect);
        }
        else
        {
            characters.erase(characters.begin() + i);
            i--;
        }
    }

    for(int i = 0; i < enemies.size(); i++)
    {
        if(enemies.at(i)->m_isAlive)
        {
            SDL_RenderCopy(renderer, enemies.at(i)->m_texture, &enemies.at(i)->m_SrcRect, &enemies.at(i)->m_DestRect);
        }
        else
        {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }


    if (selectedCharacter == nullptr)
    {
        SDL_RenderCopy(renderer, cursor.m_tex, &cursor.m_SrcRect, &cursor.m_DestRect);
    }
    if(selectedCharacter != nullptr)
    {
        if(selectedCharacter->m_showInventory)
        {
            SDL_RenderCopy(renderer, inventory.m_texture, &inventory.m_SrcRect, &inventory.m_DestRect);
            selectedCharacter->drawStats();
            for(int i = 0; i < m_strengthWord.m_fonts.size(); i++)
            {
                SDL_RenderCopy(renderer, m_strengthWord.m_fonts.at(i).m_texture, &m_strengthWord.m_fonts.at(i).m_SrcRect, &m_strengthWord.m_fonts.at(i).m_DestRect);
            }
            for(int i = 0; i < m_skillWord.m_fonts.size(); i++)
            {
                SDL_RenderCopy(renderer, m_skillWord.m_fonts.at(i).m_texture, &m_skillWord.m_fonts.at(i).m_SrcRect, &m_skillWord.m_fonts.at(i).m_DestRect);
            }
            for(int i = 0; i < m_speedWord.m_fonts.size(); i++)
            {
                SDL_RenderCopy(renderer, m_speedWord.m_fonts.at(i).m_texture, &m_speedWord.m_fonts.at(i).m_SrcRect, &m_speedWord.m_fonts.at(i).m_DestRect);
            }
            for(int i = 0; i < m_defenseWord.m_fonts.size(); i++)
            {
                SDL_RenderCopy(renderer, m_defenseWord.m_fonts.at(i).m_texture, &m_defenseWord.m_fonts.at(i).m_SrcRect, &m_defenseWord.m_fonts.at(i).m_DestRect);
            }
            for(int i = 0; i < m_healthWord.m_fonts.size(); i++)
            {
                SDL_RenderCopy(renderer, m_healthWord.m_fonts.at(i).m_texture, &m_healthWord.m_fonts.at(i).m_SrcRect, &m_healthWord.m_fonts.at(i).m_DestRect);
            }
        }
    }

    for(int i = 0; i < enemies.size(); i++)
    {
        if(enemies.at(i)->m_showInventory)
        {
            SDL_RenderCopy(renderer, inventory.m_texture, &inventory.m_SrcRect, &inventory.m_DestRect);
            enemies.at(i)->drawStats();
            for(int i = 0; i < m_strengthWord.m_fonts.size(); i++)
            {
                SDL_RenderCopy(renderer, m_strengthWord.m_fonts.at(i).m_texture, &m_strengthWord.m_fonts.at(i).m_SrcRect, &m_strengthWord.m_fonts.at(i).m_DestRect);
            }
            for(int i = 0; i < m_skillWord.m_fonts.size(); i++)
            {
                SDL_RenderCopy(renderer, m_skillWord.m_fonts.at(i).m_texture, &m_skillWord.m_fonts.at(i).m_SrcRect, &m_skillWord.m_fonts.at(i).m_DestRect);
            }
            for(int i = 0; i < m_speedWord.m_fonts.size(); i++)
            {
                SDL_RenderCopy(renderer, m_speedWord.m_fonts.at(i).m_texture, &m_speedWord.m_fonts.at(i).m_SrcRect, &m_speedWord.m_fonts.at(i).m_DestRect);
            }
            for(int i = 0; i < m_defenseWord.m_fonts.size(); i++)
            {
                SDL_RenderCopy(renderer, m_defenseWord.m_fonts.at(i).m_texture, &m_defenseWord.m_fonts.at(i).m_SrcRect, &m_defenseWord.m_fonts.at(i).m_DestRect);
            }
            for(int i = 0; i < m_healthWord.m_fonts.size(); i++)
            {
                SDL_RenderCopy(renderer, m_healthWord.m_fonts.at(i).m_texture, &m_healthWord.m_fonts.at(i).m_SrcRect, &m_healthWord.m_fonts.at(i).m_DestRect);
            }
        }
    }

    if (selectedMenu != nullptr)
    {
        selectedMenu->draw();
    }

    SDL_RenderPresent(renderer);
}

void core::s_loop(void *user_data)
{
    core* self = (core*) user_data;
    self->loop();
}

void core::run()
{
    for (int i = 0; i < 225; i++)
    {
        map[i].setValues(20, 10, "assets/TileSet1.png", false);
        map[i].m_texture = load_texture(map[i].m_srcImage);
        map[i].setSrcRect(32, 16, 16, 16);
        map[i].setDestRect((i % 15) * 70, (i / 15) * 70, 70, 70);
    }
    for (int i = 0; i < 225; i++)
    {
        moveRangeMap[i].setValues(20, 10, "assets/TileSet1.png", false);
        moveRangeMap[i].m_texture = load_texture(moveRangeMap[i].m_srcImage);
        moveRangeMap[i].setSrcRect(272, 0, 16, 16);
        moveRangeMap[i].setDestRect((i % 15) * 70, (i / 15) * 70, 70, 70);
        moveRangeMap[i].m_draw = false;
    }

    char1.setSrcImage("assets/pkmn_teddiursa.png");


    char1.name = "char1";


    createCharacter(&char1, "assets/LordStats.txt");


    char2.setSrcImage("assets/pkmn_mudkip2.png");

    char2.name = "char2";

    createCharacter(&char2, "assets/CalebStats.txt");


    char3.setSrcImage("assets/pkmn_squirtle.png");

    char3.name = "char3";

    char3.setSrcRect(0, 0, 30, 30);
    char3.setDestRect(840, 280, map[0].m_width, map[0].m_height);

    char3.setCoords();

    char3.setFrontFacing(0, 0);
    char3.setLeftFacing(0, 30);
    char3.setRightFacing(0, 60);
    char3.setBackFacing(0, 90);

    char3.core = this;

    characters.push_back(&char3);

    for (int i = 0; i < characters.size(); i++)
    {
        characters.at(i)->m_texture = load_texture(characters.at(i)->m_srcImage);
    }

    createEnemy(&enemy1);

    enemy1.m_SrcString = ("assets/logo.png");

    enemy1.core = this;

    for(int i = 0; i < enemies.size(); i++)
    {
        enemies.at(i)->m_texture = load_texture(enemies.at(i)->m_SrcString);
    }

    quit = false;

    cursor.m_tex = load_texture("assets/cursor.png");

    cursor.setSrcRect(0, 0, 40, 40);
    cursor.setDestRect(0, 0, 70, 70);

    selectedCharacter = nullptr;

    menuOptionSelected = 0;

    inventory.m_SrcString = "assets/inventory.png";
    inventory.m_texture = load_texture(inventory.m_SrcString);

    inventory.setSrcRect(0, 0, 240, 160);
    inventory.setDestRect(0, 0, 1050, 1050);

    waitMenu.m_SrcString = "assets/waitMenu.png";
    waitMenu.core = this;
    waitMenu.m_texture = load_texture(waitMenu.m_SrcString);
    waitMenu.createCursor();

    waitMenu.setDestRect(0,0,210,150);

    attackMenu.m_SrcString = "assets/attackMenu.png";
    attackMenu.core = this;
    attackMenu.m_texture = load_texture(attackMenu.m_SrcString);
    attackMenu.createCursor();

    attackMenu.setDestRect(0, 0, 210, 150);

    combatPreviewMenu.m_SrcString = "assets/combatPreviewMenu.png";
    combatPreviewMenu.core = this;
    combatPreviewMenu.m_texture = load_texture(combatPreviewMenu.m_SrcString);

    combatPreviewMenu.setDestRect(150, -15, 450, 200);

    combatPreviewMenu.loadWordTextures();

    selectedMenu = nullptr;

    map_Boundary.x = 14;
    map_Boundary.y = 12;

    m_enemyPhasePopUp.m_texture = load_texture("assets/EnemyPhase.png");

    m_enemyPhasePopUp.setSrcRect(0, 80, 250, 20);
    m_enemyPhasePopUp.setDestRect(550, 550, 1100, 50);

    m_enemyPhasePopUp.core = this;

    m_playerPhasePopUp.m_texture = load_texture("assets/PlayerPhase.png");

    m_playerPhasePopUp.setSrcRect(0, 80, 250, 20);
    m_playerPhasePopUp.setDestRect(550, 550, 11100, 50);

    m_playerPhasePopUp.core = this;

    font tempFont;

    for(int i = 0; i < 8; i++)
    {
        m_strengthWord.m_fonts.push_back(tempFont);
    }

    for(int i = 0; i < 8; i++)
    {
        m_strengthWord.m_fonts.at(i).m_srcImage = "assets/font2.png";
        m_strengthWord.m_fonts.at(i).m_texture = load_texture(m_strengthWord.m_fonts.at(i).m_srcImage);
    }

    m_strengthWord.m_fonts.at(0).setSrcRect(89, 32, 16, 16);
    m_strengthWord.m_fonts.at(0).setDestRect(500, 120, 32, 32);

    m_strengthWord.m_fonts.at(1).setSrcRect(105, 32, 16, 16);
    m_strengthWord.m_fonts.at(1).setDestRect(532, 120, 32, 32);

    m_strengthWord.m_fonts.at(2).setSrcRect(73, 32, 16, 16);
    m_strengthWord.m_fonts.at(2).setDestRect(564, 120, 32, 32);

    m_strengthWord.m_fonts.at(3).setSrcRect(73, 16, 16, 16);
    m_strengthWord.m_fonts.at(3).setDestRect(596, 120, 32, 32);

    m_strengthWord.m_fonts.at(4).setSrcRect(9, 32, 16, 16);
    m_strengthWord.m_fonts.at(4).setDestRect(628, 120, 32, 32);

    m_strengthWord.m_fonts.at(5).setSrcRect(105, 16, 16, 16);
    m_strengthWord.m_fonts.at(5).setDestRect(660, 120, 32, 32);

    m_strengthWord.m_fonts.at(6).setSrcRect(105, 32, 16, 16);
    m_strengthWord.m_fonts.at(6).setDestRect(692, 120, 32, 32);

    m_strengthWord.m_fonts.at(7).setSrcRect(121, 16, 16, 16);
    m_strengthWord.m_fonts.at(7).setDestRect(724, 120, 32, 32);

    for(int i = 0; i < 5; i++)
    {
        m_skillWord.m_fonts.push_back(tempFont);
    }

    for(int i = 0; i < m_skillWord.m_fonts.size(); i++)
    {
        m_skillWord.m_fonts.at(i).m_srcImage = "assets/font2.png";
        m_skillWord.m_fonts.at(i).m_texture = load_texture(m_skillWord.m_fonts.at(i).m_srcImage);
    }

    m_skillWord.m_fonts.at(0).setSrcRect(89, 32, 16, 16);
    m_skillWord.m_fonts.at(0).setDestRect(500, 170, 32, 32);

    m_skillWord.m_fonts.at(1).setSrcRect(169, 16, 16, 16);
    m_skillWord.m_fonts.at(1).setDestRect(532, 170, 32, 32);

    m_skillWord.m_fonts.at(2).setSrcRect(137, 16, 16, 16);
    m_skillWord.m_fonts.at(2).setDestRect(564, 170, 32, 32);

    m_skillWord.m_fonts.at(3).setSrcRect(185, 16, 16, 16);
    m_skillWord.m_fonts.at(3).setDestRect(596, 170, 32, 32);

    m_skillWord.m_fonts.at(4).setSrcRect(185, 16, 16, 16);
    m_skillWord.m_fonts.at(4).setDestRect(628, 170, 32, 32);

    for(int i = 0; i < 5; i++)
    {
        m_speedWord.m_fonts.push_back(tempFont);
    }

    for(int i = 0; i < m_speedWord.m_fonts.size(); i++)
    {
        m_speedWord.m_fonts.at(i).m_srcImage = "assets/font2.png";
        m_speedWord.m_fonts.at(i).m_texture = load_texture(m_speedWord.m_fonts.at(i).m_srcImage);
    }

    m_speedWord.m_fonts.at(0).setSrcRect(89, 32, 16, 16);
    m_speedWord.m_fonts.at(0).setDestRect(500, 220, 32, 32);

    m_speedWord.m_fonts.at(1).setSrcRect(41, 32, 16, 16);
    m_speedWord.m_fonts.at(1).setDestRect(532, 220, 32, 32);

    m_speedWord.m_fonts.at(2).setSrcRect(73, 16, 16, 16);
    m_speedWord.m_fonts.at(2).setDestRect(564, 220, 32, 32);

    m_speedWord.m_fonts.at(3).setSrcRect(73, 16, 16, 16);
    m_speedWord.m_fonts.at(3).setDestRect(596, 220, 32, 32);

    m_speedWord.m_fonts.at(4).setSrcRect(57, 16, 16, 16);
    m_speedWord.m_fonts.at(4).setDestRect(628, 220, 32, 32);


    for(int i = 0; i < 7; i++)
    {
        m_defenseWord.m_fonts.push_back(tempFont);
    }

    for(int i = 0; i < m_defenseWord.m_fonts.size(); i++)
    {
        m_defenseWord.m_fonts.at(i).m_srcImage = "assets/font2.png";
        m_defenseWord.m_fonts.at(i).m_texture = load_texture(m_defenseWord.m_fonts.at(i).m_srcImage);
    }

    m_defenseWord.m_fonts.at(0).setSrcRect(57, 16, 16, 16);
    m_defenseWord.m_fonts.at(0).setDestRect(500, 270, 32, 32);

    m_defenseWord.m_fonts.at(1).setSrcRect(73, 16, 16, 16);
    m_defenseWord.m_fonts.at(1).setDestRect(532, 270, 32, 32);

    m_defenseWord.m_fonts.at(2).setSrcRect(89, 16, 16, 16);
    m_defenseWord.m_fonts.at(2).setDestRect(564, 270, 32, 32);

    m_defenseWord.m_fonts.at(3).setSrcRect(73, 16, 16, 16);
    m_defenseWord.m_fonts.at(3).setDestRect(596, 270, 32, 32);

    m_defenseWord.m_fonts.at(4).setSrcRect(9, 32, 16, 16);
    m_defenseWord.m_fonts.at(4).setDestRect(628, 270, 32, 32);

    m_defenseWord.m_fonts.at(5).setSrcRect(89, 32, 16, 16);
    m_defenseWord.m_fonts.at(5).setDestRect(660, 270, 32, 32);

    m_defenseWord.m_fonts.at(6).setSrcRect(73, 16, 16, 16);
    m_defenseWord.m_fonts.at(6).setDestRect(696, 270, 32, 32);

    for(int i = 0; i < 6; i++)
    {
        m_healthWord.m_fonts.push_back(tempFont);
    }

    for(int i = 0; i < m_healthWord.m_fonts.size(); i++)
    {
        m_healthWord.m_fonts.at(i).m_srcImage = "assets/font2.png";
        m_healthWord.m_fonts.at(i).m_texture = load_texture(m_healthWord.m_fonts.at(i).m_srcImage);
    }

    m_healthWord.m_fonts.at(0).setSrcRect(121, 16, 16, 16);
    m_healthWord.m_fonts.at(0).setDestRect(40, 800, 32, 32);

    m_healthWord.m_fonts.at(1).setSrcRect(73, 16, 16, 16);
    m_healthWord.m_fonts.at(1).setDestRect(72, 800, 32, 32);

    m_healthWord.m_fonts.at(2).setSrcRect(9, 16, 16, 16);
    m_healthWord.m_fonts.at(2).setDestRect(104, 800, 32, 32);

    m_healthWord.m_fonts.at(3).setSrcRect(185, 16, 16, 16);
    m_healthWord.m_fonts.at(3).setDestRect(136, 800, 32, 32);

    m_healthWord.m_fonts.at(4).setSrcRect(105, 32, 16, 16);
    m_healthWord.m_fonts.at(4).setDestRect(168, 800, 32, 32);

    m_healthWord.m_fonts.at(5).setSrcRect(121, 16, 16, 16);
    m_healthWord.m_fonts.at(5).setDestRect(200, 800, 32, 32);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(s_loop, this, 0, 1);
#else
    while (!quit)
    {
        loop();
    }

#endif
}

SDL_Texture* core::load_texture(const std::string& _path)
{
    SDL_Surface* s = IMG_Load(_path.c_str());

    if(!s)
    {
        throw std::runtime_error(_path);
    }

    SDL_Texture* rtn = SDL_CreateTextureFromSurface(renderer, s);

    SDL_FreeSurface(s);

    return rtn;
}

bool core::check_move_collision(std::vector<character*> _characters, character* _selected_character, std::vector<enemy*> _enemies)
{
    for(int i = 0; i < _characters.size(); i++)
    {
        if (_characters.at(i) != _selected_character)
        {
            if(_selected_character->m_coords.x == _characters.at(i)->m_coords.x && _selected_character->m_coords.y == _characters.at(i)->m_coords.y)
            {
                return true;
            }
        }
    }

    for(int i = 0; i < _enemies.size(); i++)
    {
        if(_selected_character->m_coords.x == _enemies.at(i)->m_coords.x && _selected_character->m_coords.y == _enemies.at(i)->m_coords.y)
        {
            return true;
        }
    }

    return false;
}

bool core::check_top_bound_move(character* _selected_character)
{
    if(!std::count(_selected_character->m_moveableCoords.begin(), _selected_character->m_moveableCoords.end(), glm::ivec2(_selected_character->m_coords.x, _selected_character->m_coords.y - 1)))
    {
        return false;
    }

    return true;
}

bool core::check_right_bound_move(character* _selected_character)
{
    if(!std::count(_selected_character->m_moveableCoords.begin(), _selected_character->m_moveableCoords.end(), glm::ivec2(_selected_character->m_coords.x + 1, _selected_character->m_coords.y)))
    {
        return false;
    }

    return true;
}

bool core::check_left_bound_move(character* _selected_character)
{
    if(!std::count(_selected_character->m_moveableCoords.begin(), _selected_character->m_moveableCoords.end(), glm::ivec2(_selected_character->m_coords.x - 1, _selected_character->m_coords.y)))
    {
        return false;
    }

    return true;
}

bool core::check_bottom_bound_move(character* _selected_character)
{
    if(!std::count(_selected_character->m_moveableCoords.begin(), _selected_character->m_moveableCoords.end(), glm::ivec2(_selected_character->m_coords.x, _selected_character->m_coords.y + 1)))
    {
        return false;
    }

    return true;
}

void core::createCharacter(character* _character, std::string _fileName)
{
    std::cout << "checkpoint 6bx " << _fileName << std::endl;

    std::fstream data_file;

    data_file.open(_fileName, std::ios::in);

    std::string stats[20];
    int i = 0;

    if(data_file.is_open())
    {

        std::string data;
        while(getline(data_file, data))
        {
            stats[i] = data;
            i++;
        }
        data_file.close();
    }

    _character->m_health = std::stoi(stats[0]);
    _character->m_healthMax = std::stoi(stats[0]);
    _character->m_strength = std::stoi(stats[1]);
    _character->m_skill = std::stoi(stats[2]);
    _character->m_speed = std::stoi(stats[3]);
    _character->m_defense = std::stoi(stats[4]);
    _character->m_moveStat = std::stoi(stats[5]);
    _character->m_spriteSize.x = std::stoi(stats[6]);
    _character->m_spriteSize.y = std::stoi(stats[7]);

    _character->setSrcRect(0, 0, _character->m_spriteSize.x, _character->m_spriteSize.y);
    _character->setDestRect(std::stoi(stats[8]) * _character->m_width, std::stoi(stats[9]) * _character->m_height, _character->m_width, _character->m_height);

    _character->setCoords();

    _character->setFrontFacing(0, 0);
    _character->setBackFacing(0, _character->m_spriteSize.y * 3);
    _character->setRightFacing(0, _character->m_spriteSize.y * 2);
    _character->setLeftFacing(0, _character->m_spriteSize.y);

    _character->m_healthGrowth = std::stoi(stats[10]);
    _character->m_strengthGrowth = std::stoi(stats[11]);
    _character->m_skillGrowth = std::stoi(stats[12]);
    _character->m_speedGrowth = std::stoi(stats[13]);
    _character->m_defenseGrowth = std::stoi(stats[14]);

    _character->core = this;

    for(int i = 0; i < _character->m_strengthNum.m_fonts.size(); i++)
    {
       _character->m_strengthNum.m_fonts.at(i).m_texture = load_texture("assets/font.png");
       _character->m_skillNum.m_fonts.at(i).m_texture = load_texture("assets/font.png");
       _character->m_speedNum.m_fonts.at(i).m_texture = load_texture("assets/font.png");
       _character->m_defenseNum.m_fonts.at(i).m_texture = load_texture("assets/font.png");
       _character->m_healthNumCurrent.m_fonts.at(i).m_texture = load_texture("assets/font.png");
       _character->m_healthNumMax.m_fonts.at(i).m_texture = load_texture("assets/font.png");
    }

    _character->setNumRects();

    characters.push_back(_character);
}

std::vector<std::string> core::stripWhitespaces(std::string _string)
{

    std::vector<std::string> currentString;
    std::vector<std::string> finishedString;

    for(int i = 0; i < _string.size(); i++)
    {
        //if(_string[i] != " ")
        //{
            //currentString.push_back(_string[i]);
            //TODO get help here
        //}
        //else
        //{
            //finishedString.push_back(currentString);
            //currentString.empty();
        //}
    }

    return finishedString;
}

void core::createEnemy(enemy *_enemy)
{
    std::fstream data_file;

    data_file.open("assets/enemy.txt", std::ios::in);

    std::string stats[20];
    int i = 0;

    if(data_file.is_open())
    {

        std::string data;
        while(getline(data_file, data))
        {
            stats[i] = data;
            i++;
        }
        data_file.close();
    }

    _enemy->m_health = std::stoi(stats[0]);
    _enemy->m_healthMax = std::stoi(stats[0]);
    _enemy->m_strength = std::stoi(stats[1]);
    _enemy->m_skill = std::stoi(stats[2]);
    _enemy->m_speed = std::stoi(stats[3]);
    _enemy->m_defense = std::stoi(stats[4]);
    _enemy->m_moveStat = std::stoi(stats[5]);
    _enemy->m_spriteSize.x = std::stoi(stats[6]);
    _enemy->m_spriteSize.y = std::stoi(stats[7]);

    _enemy->m_coords.x = (std::stoi(stats[8]));
    _enemy->m_coords.y = (std::stoi(stats[9]));

    _enemy->setSrcRect(0,0, _enemy->m_spriteSize.x, _enemy->m_spriteSize.y);
    _enemy->setDestRect(_enemy->m_coords.x * 70, _enemy->m_coords.y * 70, 70, 70);

    for(int i = 0; i < 2; i++)
    {
        _enemy->m_strengthNum.m_fonts.at(i).m_texture = load_texture("assets/font.png");
        _enemy->m_skillNum.m_fonts.at(i).m_texture = load_texture("assets/font.png");
        _enemy->m_speedNum.m_fonts.at(i).m_texture = load_texture("assets/font.png");
        _enemy->m_defenseNum.m_fonts.at(i).m_texture = load_texture("assets/font.png");
        _enemy->m_healthNumCurrent.m_fonts.at(i).m_texture = load_texture("assets/font.png");
        _enemy->m_healthNumMax.m_fonts.at(i).m_texture = load_texture("assets/font.png");
    }

    _enemy->setNumRects();

    enemies.push_back(_enemy);
}

