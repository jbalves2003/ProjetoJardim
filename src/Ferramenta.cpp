#include "../include/Ferramenta.h"

static int proximoNumeroSerie = 1;

Ferramenta::Ferramenta(char representacao, int durabilidade)
    : charRepresentacao(representacao), durabilidade(durabilidade) 
{
    this->numeroSerie = proximoNumeroSerie++;
}

char Ferramenta::getCharRepresentacao() const { return charRepresentacao; }
int Ferramenta::getNumeroSerie() const { return numeroSerie; }
int Ferramenta::getDurabilidade() const { return durabilidade; }

bool Ferramenta::quebrou() const {
    return durabilidade == 0;
}