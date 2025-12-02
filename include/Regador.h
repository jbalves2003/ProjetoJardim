//
// Created by 2003j on 02/12/2025.
//

#ifndef REGADOR_H
#define REGADOR_H
#include "Ferramenta.h"

class Regador : public Ferramenta {
public:
    Regador();
    bool usar(PosicaoSolo& solo) override;
};
#endif