//
// Created by 2003j on 02/12/2025.
//

#include "../include/Roseira.h"
#include "../include/PosicaoSolo.h"

Roseira::Roseira() : Planta('r', "Roseira") {
    this->aguaInterna = Settings::Roseira::inicial_agua;
    this->nutrientesInternos = Settings::Roseira::inicial_nutrientes;
}

void Roseira::viver(PosicaoSolo& solo) {
    idade++;

    this->aguaInterna -= Settings::Roseira::perda_agua;
    this->nutrientesInternos -= Settings::Roseira::perda_nutrientes;

    // Agua
    int aguaSolo = solo.getAgua();
    int aguaDesejada = Settings::Roseira::absorcao_agua;
    int aguaAbsorvida = (aguaSolo >= aguaDesejada) ? aguaDesejada : aguaSolo;
    solo.diminuirAgua(aguaAbsorvida);
    this->aguaInterna += aguaAbsorvida;

    // Nutrientes
    int nutrSolo = solo.getNutrientes();
    int nutrDesejados = Settings::Roseira::absorcao_nutrientes;
    int nutrAbsorvidos = (nutrSolo >= nutrDesejados) ? nutrDesejados : nutrSolo;
    solo.diminuirNutrientes(nutrAbsorvidos);
    this->nutrientesInternos += nutrAbsorvidos;
}

bool Roseira::deveMorrer() const {
    if (aguaInterna <= 0 || nutrientesInternos <= 0 || nutrientesInternos >= Settings::Roseira::morre_nutrientes_maior) {
        return true;
    }
    return false;
}

bool Roseira::querReproduzir() const {
    // Nutrientes > 100
    return nutrientesInternos > 100;
}

Planta* Roseira::reproduzir() {
    Roseira* filha = new Roseira();

    this->nutrientesInternos = 100;

    this->aguaInterna /= 2;
    filha->aguaInterna = this->aguaInterna;

    return filha;
}