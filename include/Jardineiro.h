#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <vector>
#include "Ferramenta.h"
#include "Settings.h"

class Jardineiro {
private:
    int posLinha, posColuna;
    bool noJardim;

    std::vector<Ferramenta*> inventario;
    Ferramenta* ferramentaNaMao;

    int movimentosRestantes;
    int plantacoesRestantes;
    int colheitasRestantes;
    int entradasSaidasRestantes;

public:
    Jardineiro();
    ~Jardineiro();

    int getLinha() const;
    int getColuna() const;
    bool estaNoJardim() const;
    void setPosicao(int l, int c);
    void entrarJardim(int l, int c);
    void sairJardim();

    bool apanharFerramenta(Ferramenta* f);
    bool comprarFerramenta(Ferramenta* f);
    bool pegarFerramenta(int numeroSerie);
    void largarFerramenta();

    void removerFerramentaMao();

    Ferramenta* getFerramentaNaMao() const;
    const std::vector<Ferramenta*>& getInventario() const;

    bool gastarMovimento();
    bool gastarPlantacao();
    bool gastarColheita();
    bool gastarEntradaSaida();

    void resetarAcoes();
};

#endif