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

    int getAgua() const;
    int getNutrientes() const;
    Planta* getPlanta() const;
    Ferramenta* getFerramenta() const;

    void setPlanta(Planta* p);
    void setFerramenta(Ferramenta* f);

    // --- NOVOS SETTERS PARA O LOAD ---
    void setAgua(int a);
    void setNutrientes(int n);

    void aumentarAgua(int qtd);
    void diminuirAgua(int qtd);
    void aumentarNutrientes(int qtd);
    void diminuirNutrientes(int qtd);
};

#endif