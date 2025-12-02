#include "../include/PosicaoSolo.h"
#include "../include/Planta.h"     // Necessário para delete
#include "../include/Ferramenta.h" // Necessário para delete
#include <algorithm> // Para std::max

PosicaoSolo::PosicaoSolo() {
    // ... (o teu código do construtor com o random mantém-se igual aqui) ...
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

void PosicaoSolo::aumentarAgua(int qtd) {
    this->agua += qtd;
    // O enunciado não define limite máximo explícito para o solo,
    // mas podes limitar se quiseres. Por agora deixamos livre.
}

void PosicaoSolo::diminuirAgua(int qtd) {
    this->agua -= qtd;
    if (this->agua < 0) this->agua = 0; // Não pode haver água negativa
}

void PosicaoSolo::aumentarNutrientes(int qtd) {
    this->nutrientes += qtd;
}

void PosicaoSolo::diminuirNutrientes(int qtd) {
    this->nutrientes -= qtd;
    if (this->nutrientes < 0) this->nutrientes = 0;
}