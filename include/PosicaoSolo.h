#ifndef PROJETO_POSICAOSOLO_H
#define PROJETO_POSICAOSOLO_H

#include "Settings.h"
#include <random>
#include <chrono>

// Forward declarations
class Planta;
class Ferramenta;

class PosicaoSolo {
private:
    int agua;
    int nutrientes;
    Planta* planta;
    Ferramenta* ferramenta;

public:
    PosicaoSolo();

    // Getters
    int getAgua() const;
    int getNutrientes() const;
    Planta* getPlanta() const;
    Ferramenta* getFerramenta() const;

    // Setters e Modificadores
    void setPlanta(Planta* p);
    void setFerramenta(Ferramenta* f);

    // Métodos para as plantas/ferramentas usarem
    void aumentarAgua(int qtd);
    void diminuirAgua(int qtd);
    void aumentarNutrientes(int qtd);
    void diminuirNutrientes(int qtd);
};

#endif