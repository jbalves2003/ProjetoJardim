#include "../include/Jardim.h"
#include <iostream>

Jardim::Jardim() : numLinhas(0), numColunas(0), solo(nullptr), jardimCriado(false) {}

Jardim::~Jardim() {
    if (solo != nullptr) {
        for (int i = 0; i < numLinhas; ++i) {
            delete[] solo[i];
        }
        delete[] solo;
    }
}

bool Jardim::criarJardim(int linhas, int colunas) {
    if (jardimCriado) {
        std::cout << "Erro: O jardim ja foi criado." << std::endl;
        return false;
    }
    if (linhas <= 0 || colunas <= 0 ||   linhas > 26 || colunas > 26) {
        std::cout << "Erro: Dimensoes do jardim invalidas (max 26x26)." << std::endl;
        return false;
    }

    this->numLinhas = linhas;
    this->numColunas = colunas;

    solo = new PosicaoSolo*[numLinhas];
    for (int i = 0; i < numLinhas; ++i) {
        solo[i] = new PosicaoSolo[numColunas];
    }

    jardimCriado = true;
    std::cout << "Jardim de " << numLinhas << "x" << numColunas << " criado com sucesso." << std::endl;
    return true;
}

void Jardim::exibirJardim() const {
    if (!jardimCriado) {
        std::cout << "O jardim ainda nao foi criado." << std::endl;
        return;
    }

    std::cout << "  ";
    for (int j = 0; j < numColunas; ++j) {
        std::cout << (char)('A' + j);
    }
    std::cout << std::endl;

    for (int i = 0; i < numLinhas; ++i) {
        std::cout << (char)('A' + i) << " ";
        for (int j = 0; j < numColunas; ++j) {
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

bool Jardim::isJardimCriado() const {
    return jardimCriado;
}

void Jardim::resetaPlantasPorInstante() {
    PlantasPorInstante = 0;
}

bool Jardim::podePlantar() const {
    return PlantasPorInstante < 2;
}

void Jardim::incrementaPlantasPorInstante() {
    ++PlantasPorInstante;
}
