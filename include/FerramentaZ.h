//
// Created by 2003j on 02/12/2025.
//

#ifndef FERRAMENTAZ_H
#define FERRAMENTAZ_H
#include "Ferramenta.h"

class FerramentaZ : public Ferramenta {
public:
    FerramentaZ();
    bool usar(PosicaoSolo& solo) override;
};
#endif