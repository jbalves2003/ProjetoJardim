//
// Created by 2003j on 02/12/2025.
//


#include "../include/Cato.h"
#include "../include/PosicaoSolo.h"
#include <iostream>

Cato::Cato() : Planta('c', "Cato"), contagemAguaExcessiva(0), contagemSemNutrientes(0) {

}

void Cato::viver(PosicaoSolo& solo) {
    idade++;

    //  Absorve 25% da água do solo
    int aguaNoSolo = solo.getAgua();
    int aguaAbsorvida = aguaNoSolo * Settings::Cacto::absorcao_agua_percentagem / 100;
    solo.diminuirAgua(aguaAbsorvida);
    this->aguaInterna += aguaAbsorvida;

    // 5 unidades de nutrientes
    int nutrNoSolo = solo.getNutrientes();
    int nutrDesejados = Settings::Cacto::absorcao_nutrientes;
    int nutrAbsorvidos = (nutrNoSolo >= nutrDesejados) ? nutrDesejados : nutrNoSolo;
    solo.diminuirNutrientes(nutrAbsorvidos);
    this->nutrientesInternos += nutrAbsorvidos;


    // Se água no solo > 100
    if (solo.getAgua() > Settings::Cacto::morre_agua_solo_maior) {
        contagemAguaExcessiva++;
    } else {
        contagemAguaExcessiva = 0;
    }

    // Se nutrientes no solo == 0
    if (solo.getNutrientes() == 0) {
        contagemSemNutrientes++;
    } else {
        contagemSemNutrientes = 0;
    }
}

bool Cato::deveMorrer() const {
    //  contagens > 3
    return (contagemAguaExcessiva >= Settings::Cacto::morre_agua_solo_instantes) ||
           (contagemSemNutrientes > Settings::Cacto::morre_nutrientes_solo_instantes);
}

bool Cato::querReproduzir() const {
    // Nutrientes > 100 e Agua > 50
    return (nutrientesInternos > Settings::Cacto::multiplica_nutrientes_maior) &&
           (aguaInterna > Settings::Cacto::multiplica_agua_maior);
}

Planta* Cato::reproduzir() {
    Cato* filho = new Cato();

    this->aguaInterna /= 2;
    this->nutrientesInternos /= 2;

    filho->aguaInterna = this->aguaInterna;
    filho->nutrientesInternos = this->nutrientesInternos;

    return filho;
}