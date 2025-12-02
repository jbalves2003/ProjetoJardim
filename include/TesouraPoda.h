//
// Created by 2003j on 02/12/2025.
//

#ifndef TESOURAPODA_H
#define TESOURAPODA_H
#include "Ferramenta.h"

class TesouraPoda : public Ferramenta {
public:
    TesouraPoda();
    bool usar(PosicaoSolo& solo) override;
};
#endif