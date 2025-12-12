//
// Created by 2003j on 02/12/2025.
//

#ifndef ERVADANINHA_H
#define ERVADANINHA_H

#include "Planta.h"

class ErvaDaninha : public Planta {
private:
    int contadorReproducao;

public:
    ErvaDaninha();
    void viver(PosicaoSolo& solo) override;
    bool deveMorrer() const override;
    bool querReproduzir() const override;
    Planta* reproduzir() override;
};

#endif