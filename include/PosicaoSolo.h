#ifndef PROJETO_POSICAOSOLO_H
#define PROJETO_POSICAOSOLO_H


class Planta;
class Ferramenta;

class PosicaoSolo {
private:
    int agua;
    int nutrientes;
    Planta* planta;
    Ferramenta* ferramenta;

public:
    PosicaoSolo();
};

#endif