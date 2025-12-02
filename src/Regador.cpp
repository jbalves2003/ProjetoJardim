//
// Created by 2003j on 02/12/2025.
//

#include "../include/Regador.h"
#include "../include/PosicaoSolo.h"
#include <iostream>

Regador::Regador() : Ferramenta('g', Settings::Regador::capacidade) {}

bool Regador::usar(PosicaoSolo& solo) {
    if (durabilidade > 0) {
        solo.aumentarAgua(Settings::Regador::dose);

        durabilidade -= Settings::Regador::dose;
        if (durabilidade < 0) durabilidade = 0;

        return true;
    }
    return false;
}