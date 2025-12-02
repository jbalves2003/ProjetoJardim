#ifndef FERRAMENTA_H
#define FERRAMENTA_H

#include "Settings.h"

class PosicaoSolo; // Forward declaration

class Ferramenta {
protected:
    int numeroSerie;
    int durabilidade; // -1 para infinito
    char charRepresentacao;

public:
    Ferramenta(char representacao, int durabilidade);
    virtual ~Ferramenta() = default;

    virtual char getCharRepresentacao() const;
    int getNumeroSerie() const;
    int getDurabilidade() const;

    // Ação principal: Usar a ferramenta numa posição
    // Retorna true se a ferramenta foi usada com sucesso
    virtual bool usar(PosicaoSolo& solo) = 0;

    // Verifica se a ferramenta se partiu/gastou
    virtual bool quebrou() const;
};

#endif