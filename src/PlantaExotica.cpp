//
// Created by 2003j on 02/12/2025.
//

#include "../include/PlantaExotica.h"
#include "../include/PosicaoSolo.h"

PlantaExotica::PlantaExotica() : Planta('x', "Planta Exotica (Sugadora)") {
    this->aguaInterna = 100;
    this->nutrientesInternos = 100;
}

void PlantaExotica::viver(PosicaoSolo& solo) {
    idade++;
    solo.diminuirAgua(10);
    this->aguaInterna += 10;

    solo.diminuirNutrientes(10);
    this->nutrientesInternos += 10;

    this->aguaInterna -= 5;
    this->nutrientesInternos -= 5;
}

bool PlantaExotica::deveMorrer() const {
    if (aguaInterna < 20 || nutrientesInternos < 20) return true;
    return false;
}

bool PlantaExotica::querReproduzir() const {
    return (aguaInterna > 200 && nutrientesInternos > 200);
}

Planta* PlantaExotica::reproduzir() {
    PlantaExotica* filha = new PlantaExotica();
    this->aguaInterna /= 2;
    this->nutrientesInternos /= 2;
    return filha;
}