//
// Created by Ethan Orchard on 30/03/2023.
//

#ifndef FEC_GUI_H
#define FEC_GUI_H

#include <string>
#include <SDL2/SDL.h>

#include "object.h"


class gui : public object{

public:

    virtual void draw();

    SDL_Texture* m_texture;
    std::string m_SrcString;

};


#endif //FEC_GUI_H
