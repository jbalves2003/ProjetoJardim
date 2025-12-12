//
// Created by 2003j on 13/10/2025.
//


#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Jardim.h"
#include "Jardineiro.h"
#include <string>

class Simulador {
public:
    Simulador();
    void run();

private:
    Jardim jardim;
    Jardineiro jardineiro;
    bool aExecutar;

    void processarLinhaComando(const std::string& linha);
};

#endif //SIMULADOR_H