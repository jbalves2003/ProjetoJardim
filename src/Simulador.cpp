//
// Created by 2003j on 13/10/2025.
//

#include "../include/Simulador.h"
#include <sstream>
#include <iostream>


Simulador::Simulador() : aExecutar(true) {}

void Simulador::run() {
    std::cout << "Simulador de Jardim!" << std::endl;
    std::cout << "jardim: jardim <linhas> <colunas>" << std::endl;

    std::string linhaComando;
    while (aExecutar) {
        std::cout << "> ";
        if (!std::getline(std::cin, linhaComando)) {
            break;
        }

        if (linhaComando.empty()) {
            continue;
        }

        processarLinhaComando(linhaComando);
    }
}

void Simulador::processarLinhaComando(const std::string& linha) {
    std::istringstream iss(linha);
    std::string comando;
    iss >> comando;

    if (comando == "fim") {
        std::cout << "Encerrando o simulador." << std::endl;
        aExecutar = false;
        return;
    }

    if (comando == "jardim") {
        int linhas, colunas;
        if (iss >> linhas >> colunas) {
            if (jardim.criarJardim(linhas, colunas)) {
                jardim.exibirJardim();
            }
        } else {
            std::cout << "Erro: Sintaxe. Uso: jardim <linhas> <colunas>" << std::endl;
        }
        return;
    }

    if (comando == "executa") {
        std::string nomeFicheiro;
        iss >> nomeFicheiro;
        if (!nomeFicheiro.empty()) {
             std::cout << "Comando 'executa' validado para o ficheiro '" << nomeFicheiro << "'." << std::endl;
        } else {
            std::cout << "Erro: Sintaxe. Uso: executa <nome-ficheiro>" << std::endl;
        }
        return;
    }

    // todos os comandos a partir da cricao do jardim
    if (!jardim.isJardimCriado()) {
        std::cout << "Erro: O jardim ainda nao foi criado. Execute o comando 'jardim' primeiro." << std::endl;
        return;
    }


    if (comando == "avanca") {
        int n = 1;
        iss >> n;
        if (n > 0) {
            std::cout << "Comando 'avanca' validado para " << n << " instante(s)." << std::endl;
            jardim.resetaPlantasPorInstante();
        } else {
            std::cout << "Erro: O numero de instantes deve ser positivo." << std::endl;
        }
    } else if (comando == "lplantas" || comando == "larea" || comando == "lferr" || comando == "larga" || comando == "sai") {
        std::cout << "Comando '" << comando << "' validado." << std::endl;
    } else if (comando == "e" || comando == "d" || comando == "c" || comando == "b") {
        std::cout << "Comando de movimento '" << comando << "' validado." << std::endl;
    } else if (comando == "lplanta" || comando == "lsolo" || comando == "colhe" || comando == "entra") {
        std::string coords;
        if (iss >> coords && coords.length() == 2) {
             std::cout << "Comando '" << comando << "' validado para a posicao " << coords << "." << std::endl;
        } else {
            std::cout << "Erro: Sintaxe. Uso: " << comando << " <l><c>" << std::endl;
        }
    } else if (comando == "planta") {
        if (!jardim.podePlantar()) {
            std::cout << "Erro: Nao e permitido plantar mais de 2 plantas no mesmo instante." << std::endl;
            return;
        }

        std::string coords, tipoStr;
        if (iss >> coords >> tipoStr && coords.length() == 2 && tipoStr.length() == 1) {
            std::cout << "Comando 'planta' validado para " << coords << " com tipo '" << tipoStr[0] << "'." << std::endl;
            jardim.incrementaPlantasPorInstante(); // Increment the plant count
        } else {
            std::cout << "Erro: Sintaxe. Uso: planta <l><c> <tipo>" << std::endl;
        }
    } else if (comando == "compra") {
        std::string tipoStr;
        if (iss >> tipoStr && tipoStr.length() == 1) {
             std::cout << "Comando 'compra' validado para o tipo '" << tipoStr[0] << "'." << std::endl;
        } else {
            std::cout << "Erro: Sintaxe. Uso: compra <tipo>" << std::endl;
        }
    } else if (comando == "pega") {
        int numSerie;
        if (iss >> numSerie) {
            std::cout << "Comando 'pega' validado para a ferramenta " << numSerie << "." << std::endl;
        } else {
             std::cout << "Erro: Sintaxe. Uso: pega <numero_serie>" << std::endl;
        }
    } else if (comando == "grava" || comando == "recupera" || comando == "apaga") {
        std::string nome;
        if (iss >> nome) {
            std::cout << "Comando '" << comando << "' validado com o nome '" << nome << "'." << std::endl;
        } else {
            std::cout << "Erro: Sintaxe. Uso: " << comando << " <nome>" << std::endl;
        }
    } else {
        std::cout << "Comando desconhecido: '" << comando << "'" << std::endl;
    }
}
