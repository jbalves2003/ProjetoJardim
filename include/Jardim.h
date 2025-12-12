#ifndef JARDIM_H
#define JARDIM_H

#include "PosicaoSolo.h"

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
    void limparJardim();
    
    void exibirJardim(int linhaJardineiro = -1, int colunaJardineiro = -1) const;
    bool isJardimCriado() const;
    PosicaoSolo* getPosicao(int linha, int coluna);
    
    int getNumLinhas() const { return numLinhas; }
    int getNumColunas() const { return numColunas; }
};

#endif