//
// Created by Ethan Orchard on 07/03/2023.
//

#ifndef FEC_CURSOR_H
#define FEC_CURSOR_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "object.h"

class cursor : public object {
    // Needs a tex, srcRect, destRect
public:

    cursor();

    SDL_Texture* m_tex;

    glm::ivec2 m_coords;

};


#endif //FEC_CURSOR_H
