#include "../include/Jardineiro.h"
#include <iostream>

Jardineiro::Jardineiro() 
    : posLinha(-1), posColuna(-1), noJardim(false), ferramentaNaMao(nullptr) 
{
    resetarAcoes();
}

Jardineiro::~Jardineiro() {
    for (Ferramenta* f : inventario) {
        delete f;
    }
    inventario.clear();
    
    if (ferramentaNaMao != nullptr) {
        delete ferramentaNaMao;
    }
}

int Jardineiro::getLinha() const { return posLinha; }
int Jardineiro::getColuna() const { return posColuna; }
bool Jardineiro::estaNoJardim() const { return noJardim; }

void Jardineiro::setPosicao(int l, int c) {
    posLinha = l;
    posColuna = c;
}

void Jardineiro::entrarJardim(int l, int c) {
    posLinha = l;
    posColuna = c;
    noJardim = true;
}

void Jardineiro::sairJardim() {
    noJardim = false;
    posLinha = -1;
    posColuna = -1;
}

bool Jardineiro::apanharFerramenta(Ferramenta* f) {
    if (f == nullptr) return false;
    inventario.push_back(f);
    return true;
}

bool Jardineiro::comprarFerramenta(Ferramenta* f) {
    return apanharFerramenta(f);
}

bool Jardineiro::pegarFerramenta(int numeroSerie) {
    if (ferramentaNaMao != nullptr) {
        inventario.push_back(ferramentaNaMao);
        ferramentaNaMao = nullptr;
    }

    for (auto it = inventario.begin(); it != inventario.end(); ++it) {
        if ((*it)->getNumeroSerie() == numeroSerie) {
            ferramentaNaMao = *it;
            inventario.erase(it);
            return true;
        }
    }
    return false;
}

void Jardineiro::largarFerramenta() {
    if (ferramentaNaMao != nullptr) {
        inventario.push_back(ferramentaNaMao);
        ferramentaNaMao = nullptr;
    }
}

void Jardineiro::removerFerramentaMao() {

    ferramentaNaMao = nullptr;
}

Ferramenta* Jardineiro::getFerramentaNaMao() const {
    return ferramentaNaMao;
}

const std::vector<Ferramenta*>& Jardineiro::getInventario() const {
    return inventario;
}

void Jardineiro::resetarAcoes() {
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    plantacoesRestantes = Settings::Jardineiro::max_plantacoes;
    colheitasRestantes = Settings::Jardineiro::max_colheitas;
    entradasSaidasRestantes = Settings::Jardineiro::max_entradas_saidas;
}

bool Jardineiro::gastarMovimento() {
    if (movimentosRestantes > 0) {
        movimentosRestantes--;
        return true;
    }
    return false;
}

bool Jardineiro::gastarPlantacao() {
    if (plantacoesRestantes > 0) {
        plantacoesRestantes--;
        return true;
    }
    return false;
}

bool Jardineiro::gastarColheita() {
    if (colheitasRestantes > 0) {
        colheitasRestantes--;
        return true;
    }
    return false;
}

bool Jardineiro::gastarEntradaSaida() {
    if (entradasSaidasRestantes > 0) {
        entradasSaidasRestantes--;
        return true;
    }
    return false;
}