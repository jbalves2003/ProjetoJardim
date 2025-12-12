#include "../include/PosicaoSolo.h"
#include "../include/Planta.h"
#include "../include/Ferramenta.h"
#include "../include/Settings.h"
#include <random>
#include <chrono>

PosicaoSolo::PosicaoSolo() {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distAgua(Settings::Jardim::agua_min, Settings::Jardim::agua_max);
    std::uniform_int_distribution<int> distNutrientes(Settings::Jardim::nutrientes_min, Settings::Jardim::nutrientes_max);

    this->agua = distAgua(rng);
    this->nutrientes = distNutrientes(rng);
    this->planta = nullptr;
    this->ferramenta = nullptr;
}

int PosicaoSolo::getAgua() const { return agua; }
int PosicaoSolo::getNutrientes() const { return nutrientes; }
Planta* PosicaoSolo::getPlanta() const { return planta; }
Ferramenta* PosicaoSolo::getFerramenta() const { return ferramenta; }

void PosicaoSolo::setPlanta(Planta* p) { this->planta = p; }
void PosicaoSolo::setFerramenta(Ferramenta* f) { this->ferramenta = f; }

void PosicaoSolo::setAgua(int a) { this->agua = a; }
void PosicaoSolo::setNutrientes(int n) { this->nutrientes = n; }

void PosicaoSolo::aumentarAgua(int qtd) { this->agua += qtd; }
void PosicaoSolo::diminuirAgua(int qtd) { this->agua -= qtd; if (this->agua < 0) this->agua = 0; }
void PosicaoSolo::aumentarNutrientes(int qtd) { this->nutrientes += qtd; }
void PosicaoSolo::diminuirNutrientes(int qtd) { this->nutrientes -= qtd; if (this->nutrientes < 0) this->nutrientes = 0; }