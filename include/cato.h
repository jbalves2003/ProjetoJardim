//
// Created by 2003j on 02/12/2025.
//

#ifndef CATO_H
#define CATO_H

#include "Planta.h"

class Cato : public Planta {
private:
    int contagemAguaExcessiva;
    int contagemSemNutrientes;

public:
    Cato();

    // Implementação das regras do Cato
    void viver(PosicaoSolo& solo) override;
    bool deveMorrer() const override;
    bool querReproduzir() const override;
    Planta* reproduzir() override;
};

#endif
