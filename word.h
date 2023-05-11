//
// Created by Ethan Orchard on 10/05/2023.
//

#pragma once

#ifndef FEC_WORD_H
#define FEC_WORD_H

#include <vector>

#include "object.h"
#include "font.h"

class word: public object {

public:

    std::vector<font> m_fonts;

};


#endif //FEC_WORD_H
