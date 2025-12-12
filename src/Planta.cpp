#include "../include/Planta.h"

static int proximoIdPlanta = 1;

Planta::Planta(char representacao, std::string especie)
    : charRepresentacao(representacao), especie(especie),
      aguaInterna(0), nutrientesInternos(0), idade(0)
{
    this->id = proximoIdPlanta++;
}

char Planta::getCharRepresentacao() const { return charRepresentacao; }
std::string Planta::getEspecie() const { return especie; }
int Planta::getAgua() const { return aguaInterna; }
int Planta::getNutrientes() const { return nutrientesInternos; }
int Planta::getId() const { return id; }

int Planta::getIdade() const { return idade; }