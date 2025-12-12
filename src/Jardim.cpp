#include "../include/Jardim.h"
#include <iostream>
#include "../include/Planta.h"
#include "../include/Ferramenta.h"

Jardim::Jardim() : numLinhas(0), numColunas(0), solo(nullptr), jardimCriado(false) {}

Jardim::~Jardim() {
    limparJardim();
}

void Jardim::limparJardim() {
    if (solo != nullptr) {
        for (int i = 0; i < numLinhas; ++i) {
            delete[] solo[i];
        }
        delete[] solo;
        solo = nullptr;
    }
    numLinhas = 0;
    numColunas = 0;
    jardimCriado = false;
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

void Jardim::exibirJardim(int linhaJardineiro, int colunaJardineiro) const {
    if (!jardimCriado) {
        std::cout << "O jardim ainda nao foi criado." << std::endl;
        return;
    }
    std::cout << "  ";
    for (int c = 0; c < numColunas; ++c) std::cout << (char)('A' + c);
    std::cout << std::endl;

    for (int l = 0; l < numLinhas; ++l) {
        std::cout << (char)('A' + l) << " ";
        for (int c = 0; c < numColunas; ++c) {
            if (l == linhaJardineiro && c == colunaJardineiro) {
                std::cout << "*";
                continue;
            }
            PosicaoSolo& p = solo[l][c];
            if (p.getPlanta()) std::cout << p.getPlanta()->getCharRepresentacao();
            else if (p.getFerramenta()) std::cout << p.getFerramenta()->getCharRepresentacao();
            else std::cout << " ";
        }
        std::cout << std::endl;
    }
}

bool Jardim::isJardimCriado() const { return jardimCriado; }

PosicaoSolo* Jardim::getPosicao(int linha, int coluna) {
    if (!jardimCriado || linha < 0 || linha >= numLinhas || coluna < 0 || coluna >= numColunas) return nullptr;
    return &solo[linha][coluna];
}