#include "../include/Jardim.h"
#include <iostream>
#include "../include/Planta.h"
#include "../include/Ferramenta.h"

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
    if (linhas <= 0 || colunas <= 0 || linhas > 26 || colunas > 26) {
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
    for (int c = 0; c < numColunas; ++c) {
        std::cout << (char)('A' + c);
    }
    std::cout << std::endl;

    for (int l = 0; l < numLinhas; ++l) {
        // Imprimir régua lateral (letras das linhas)
        std::cout << (char)('A' + l) << " ";

        for (int c = 0; c < numColunas; ++c) {
            PosicaoSolo& p = solo[l][c];

            if (p.getPlanta() != nullptr) {
                std::cout << p.getPlanta()->getCharRepresentacao();
            } else if (p.getFerramenta() != nullptr) {
                std::cout << p.getFerramenta()->getCharRepresentacao();
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool Jardim::isJardimCriado() const {
    return jardimCriado;
}

PosicaoSolo* Jardim::getPosicao(int linha, int coluna) {
    if (!jardimCriado) return nullptr;
    if (linha < 0 || linha >= numLinhas || coluna < 0 || coluna >= numColunas) {
        return nullptr;
    }
    return &solo[linha][coluna];
}