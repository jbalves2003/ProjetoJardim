//
// Created by 2003j on 02/12/2025.
//

#include "../include/PacoteAdubo.h"
#include "../include/PosicaoSolo.h"

PacoteAdubo::PacoteAdubo() : Ferramenta('a', Settings::Adubo::capacidade) {}

bool PacoteAdubo::usar(PosicaoSolo& solo) {
    if (durabilidade > 0) {
        solo.aumentarNutrientes(Settings::Adubo::dose);

        durabilidade -= Settings::Adubo::dose;
        if (durabilidade < 0) durabilidade = 0;

        return true;
    }
    return false;
}