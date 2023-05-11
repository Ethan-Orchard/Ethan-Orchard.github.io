//
// Created by Ethan Orchard on 24/04/2023.
//

#ifndef FEC_FONT_H
#define FEC_FONT_H

#include <SDL2/SDL.h>
#include <string>

#include "object.h"

class font : public object {

public:
    font();

    std::string m_srcImage;
    SDL_Texture* m_texture;
};


#endif //FEC_FONT_H
