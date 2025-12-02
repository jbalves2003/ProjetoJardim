//
// Created by 2003j on 02/12/2025.
//

#include "../include/TesouraPoda.h"
#include "../include/PosicaoSolo.h"
#include "../include/Planta.h"
#include <iostream>

TesouraPoda::TesouraPoda() : Ferramenta('t', -1) {}

bool TesouraPoda::usar(PosicaoSolo& solo) {
    Planta* p = solo.getPlanta();

    if (p != nullptr && p->getBeleza() == "feia") {
        std::cout << "Tesoura cortou uma planta feia!" << std::endl;
        delete p; // Elimina o objeto
        solo.setPlanta(nullptr); // Esvazia o solo
        return true;
    }
    return false;
}