//
// Created by 2003j on 02/12/2025.
//

#ifndef PLANTAEXOTICA_H
#define PLANTAEXOTICA_H

#include "Planta.h"

class PlantaExotica : public Planta {
public:
    PlantaExotica();
    void viver(PosicaoSolo& solo) override;
    bool deveMorrer() const override;
    bool querReproduzir() const override;
    Planta* reproduzir() override;
};

#endif