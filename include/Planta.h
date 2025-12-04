#ifndef PLANTA_H
#define PLANTA_H

#include "Settings.h"
#include <string>

class PosicaoSolo;

class Planta {
protected:
    int id;
    char charRepresentacao;
    std::string especie;

    int aguaInterna;
    int nutrientesInternos;
    int idade;

public:
    Planta(char representacao, std::string especie);
    virtual ~Planta() = default;
    virtual std::string getBeleza() const { return "neutra"; }

    char getCharRepresentacao() const;
    std::string getEspecie() const;
    int getAgua() const;
    int getNutrientes() const;
    int getId() const;

    virtual void viver(PosicaoSolo& solo) = 0;

    // Verifica se a planta morre ou nao
    virtual bool deveMorrer() const = 0;

    // Verifica se a planta se quer reproduzir
    virtual bool querReproduzir() const = 0;

    virtual Planta* reproduzir() = 0;
};

#endif