//
// Created by 2003j on 13/10/2025.
//

// Ficheiro: Simulador.h

#ifndef SIMULADOR_H
#define SIMULADOR_H
#include <string>
#include "../include/Simulador.h"
#include "../include/Jardim.h"
class Simulador {
public:
    Simulador();
    void run();

private:
    Jardim jardim;
    bool aExecutar;
    void processarLinhaComando(const std::string& linha);
};

#endif