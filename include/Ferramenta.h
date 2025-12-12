#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include "Settings.h"

class PosicaoSolo;

class Ferramenta {
protected:
    int numeroSerie;
    int durabilidade;
    char charRepresentacao;

public:
    Ferramenta(char representacao, int durabilidade);
    virtual ~Ferramenta() = default;

    virtual char getCharRepresentacao() const;
    int getNumeroSerie() const;
    int getDurabilidade() const;


    virtual bool usar(PosicaoSolo& solo) = 0;

    // Verifica se a ferramenta se partiu
    virtual bool quebrou() const;
};

#endif