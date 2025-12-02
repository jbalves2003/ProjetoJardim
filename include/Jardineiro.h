#ifndef JARDINEIRO_H
#define JARDINEIRO_H

#include <vector>
#include "Ferramenta.h"
#include "Settings.h"

class Jardineiro {
private:
    int posLinha, posColuna;
    bool noJardim;

    // Inventário e Mão
    std::vector<Ferramenta*> inventario;
    Ferramenta* ferramentaNaMao;

    // Contadores de ações por turno
    int movimentosRestantes;
    int plantacoesRestantes;
    int colheitasRestantes;
    int entradasSaidasRestantes;

public:
    Jardineiro();
    ~Jardineiro();

    // Getters e Setters
    int getLinha() const;
    int getColuna() const;
    bool estaNoJardim() const;
    void setPosicao(int l, int c);
    void entrarJardim(int l, int c);
    void sairJardim();

    // Gestão de Ferramentas
    bool apanharFerramenta(Ferramenta* f);
    bool comprarFerramenta(Ferramenta* f);
    bool pegarFerramenta(int numeroSerie); // Mete na mão
    void largarFerramenta(); // Tira da mão para o inventário
    Ferramenta* getFerramentaNaMao() const;
    const std::vector<Ferramenta*>& getInventario() const;

    // Gestão de Ações
    bool gastarMovimento();
    bool gastarPlantacao();
    bool gastarColheita();
    bool gastarEntradaSaida();

    // Chamado pelo comando 'avanca' para repor os limites
    void resetarAcoes();
};

#endif