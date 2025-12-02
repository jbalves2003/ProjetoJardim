//
// Created by 2003j on 02/12/2025.
//

#include "../include/FerramentaZ.h"
#include "../include/PosicaoSolo.h"
#include "../include/Planta.h"
#include <iostream>

FerramentaZ::FerramentaZ() : Ferramenta('z', 3) {}

bool FerramentaZ::usar(PosicaoSolo& solo) {
    if (durabilidade > 0) {
        Planta* p = solo.getPlanta();
        if (p != nullptr) {
            std::cout << "ZAS! Picareta magica removeu a planta!" << std::endl;
            delete p;
            solo.setPlanta(nullptr);
            durabilidade--;
            return true;
        }
    }
    return false;
}