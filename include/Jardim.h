//
// Created by 2003j on 09/10/2025.
//

#ifndef JARDIM_H
#define JARDIM_H

#include <vector>
#include "PosicaoSolo.h"

class Jardineiro;
class Planta;
class Ferramenta;

class Jardim {
private:
    int numLinhas;
    int numColunas;
    int PlantasPorInstante;
    PosicaoSolo** solo;

    bool jardimCriado;

public:
    Jardim();
    ~Jardim();

    bool criarJardim(int linhas, int colunas);
    void exibirJardim() const;

    bool isJardimCriado() const;

    void resetaPlantasPorInstante();
    bool podePlantar() const;
    void incrementaPlantasPorInstante();
};

#endif