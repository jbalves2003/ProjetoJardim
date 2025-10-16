#include "../include/PosicaoSolo.h"
#include <algorithm>
#include <chrono>
#include <random>
#include "../include/Settings.h"
PosicaoSolo::PosicaoSolo() {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    std::uniform_int_distribution<int> distAgua(Settings::Jardim::agua_min, Settings::Jardim::agua_max);
    std::uniform_int_distribution<int> distNutrientes(Settings::Jardim::nutrientes_min, Settings::Jardim::nutrientes_max);

    this->agua = distAgua(rng);
    this->nutrientes = distNutrientes(rng);
    this->planta = nullptr;
    this->ferramenta = nullptr;
}