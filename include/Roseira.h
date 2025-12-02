//
// Created by 2003j on 02/12/2025.
//

#ifndef ROSEIRA_H
#define ROSEIRA_H

#include "Planta.h"

class Roseira : public Planta {
public:
    Roseira();

    void viver(PosicaoSolo& solo) override;
    bool deveMorrer() const override;
    bool querReproduzir() const override;
    Planta* reproduzir() override;
};

#endif