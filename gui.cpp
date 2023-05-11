//
// Created by Ethan Orchard on 30/03/2023.
//

#include "gui.h"
#include "core.h"

void gui::draw()
{
    SDL_RenderCopy(core->renderer, m_texture, &m_SrcRect, &m_DestRect);
}
