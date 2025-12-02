//
// Created by 2003j on 02/12/2025.
//

#ifndef PACOTEADUBO_H
#define PACOTEADUBO_H
#include "Ferramenta.h"

class PacoteAdubo : public Ferramenta {
public:
    PacoteAdubo();
    bool usar(PosicaoSolo& solo) override;
};
#endif