//
// Created by 2003j on 09/10/2025.
//

#ifndef JARDIM_H
#define JARDIM_H

#include "PosicaoSolo.h"

class Jardineiro;
class Planta;
class Ferramenta;

class Jardim {
private:
    int numLinhas;
    int numColunas;
    PosicaoSolo** solo;

    bool jardimCriado;

public:
    Jardim();
    ~Jardim();

    bool criarJardim(int linhas, int colunas);

    void exibirJardim(int linhaJardineiro = -1, int colunaJardineiro = -1) const;

    bool isJardimCriado() const;

    PosicaoSolo* getPosicao(int linha, int coluna);

    int getNumLinhas() const { return numLinhas; }
    int getNumColunas() const { return numColunas; }
};

#endif //JARDIM_H