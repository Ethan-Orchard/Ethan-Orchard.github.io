#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <iostream>
#include <vector>

#include "core.h"
//#include "core.cpp"

//#include "gui.cpp"
//#include "waitMenu.cpp"
//#include "character.cpp"
//#include "attackMenu.cpp"
//#include "enemy.cpp"
//#include "combatPreviewMenu.cpp"
//#include "healthDisplay.cpp"

int main()
{

  std::cout << "checkpoint main" << std::endl;

  core core;

  std::cout << "checkpoint 4" << std::endl;

  core.run();

  return 0;
}


