#include "../include/ErvaDaninha.h"
#include "../include/PosicaoSolo.h"

ErvaDaninha::ErvaDaninha() : Planta('e', "Erva Daninha"), contadorReproducao(0) {
    this->aguaInterna = Settings::ErvaDaninha::inicial_agua;
    this->nutrientesInternos = Settings::ErvaDaninha::inicial_nutrientes;
}

void ErvaDaninha::viver(PosicaoSolo& solo) {
    idade++;

    contadorReproducao++;

    if (solo.getAgua() >= Settings::ErvaDaninha::absorcao_agua) {
        solo.diminuirAgua(Settings::ErvaDaninha::absorcao_agua);
        this->aguaInterna += Settings::ErvaDaninha::absorcao_agua;
    }

    if (solo.getNutrientes() >= Settings::ErvaDaninha::absorcao_nutrientes) {
        solo.diminuirNutrientes(Settings::ErvaDaninha::absorcao_nutrientes);
        this->nutrientesInternos += Settings::ErvaDaninha::absorcao_nutrientes;
    }
}

bool ErvaDaninha::deveMorrer() const {
    if (idade >= Settings::ErvaDaninha::morre_instantes) {
        return true;
    }
    return false;
}

bool ErvaDaninha::querReproduzir() const {
    // Regra: Nutrientes > 30 E passaram 5 instantes desde a última vez
    if (nutrientesInternos > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
        contadorReproducao >= Settings::ErvaDaninha::multiplica_instantes) {
        return true;
        }
    return false;
}

Planta* ErvaDaninha::reproduzir() {
    this->contadorReproducao = 0;


    return new ErvaDaninha();
}