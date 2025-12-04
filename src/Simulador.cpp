//
// Created by 2003j on 13/10/2025.
//

#include "../include/Simulador.h"
#include <sstream>
#include <iostream>


#include "../include/Simulador.h"
#include "../include/Cato.h"
#include "../include/Roseira.h"
#include "../include/ErvaDaninha.h"
#include "../include/PlantaExotica.h"
#include "../include/Regador.h"
#include "../include/PacoteAdubo.h"
#include "../include/TesouraPoda.h"
#include "../include/FerramentaZ.h"

#include <sstream>
#include <iostream>

Simulador::Simulador() : aExecutar(true) {}

void Simulador::run() {
    std::cout << "Bem-vindo ao Simulador de Jardim!" << std::endl;
    std::cout << "Para comecar, crie um jardim: jardim <linhas> <colunas>" << std::endl;

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
        // Implementar leitura de ficheiro depois
        std::cout << "Comando executa ainda nao implementado." << std::endl;
        return;
    }

    if (!jardim.isJardimCriado()) {
        std::cout << "Erro: O jardim ainda nao foi criado. Execute o comando 'jardim' primeiro." << std::endl;
        return;
    }

    // --- COMANDOS DO JOGO ---

    if (comando == "avanca") {
        int n = 1;
        iss >> n;
        if (n > 0) {
            std::cout << "Comando 'avanca' validado para " << n << " instante(s). (Logica de tempo na prox fase)" << std::endl;
            // Aqui chamarás o motor de tempo
            jardineiro.resetarAcoes(); // Por agora só resetamos as ações
        } else {
            std::cout << "Erro: O numero de instantes deve ser positivo." << std::endl;
        }

    } else if (comando == "planta") {
        std::string coords, tipoStr;
        if (iss >> coords >> tipoStr && coords.length() == 2 && tipoStr.length() == 1) {
            // Converter coordenadas
            int l = (coords[0] >= 'a') ? coords[0] - 'a' : coords[0] - 'A';
            int c = (coords[1] >= 'a') ? coords[1] - 'a' : coords[1] - 'A';

            // Verificar limite de ações
            if (!jardineiro.gastarPlantacao()) {
                std::cout << "O jardineiro nao pode plantar mais neste turno." << std::endl;
                return;
            }

            PosicaoSolo* pSolo = jardim.getPosicao(l, c);
            if (pSolo == nullptr) {
                std::cout << "Posicao invalida." << std::endl;
                return;
            }
            if (pSolo->getPlanta() != nullptr) {
                std::cout << "Ja existe uma planta nessa posicao." << std::endl;
                return;
            }

            // Criar a planta
            Planta* novaPlanta = nullptr;
            char tipo = tipoStr[0];
            if (tipo == 'c') novaPlanta = new Cato();
            else if (tipo == 'r') novaPlanta = new Roseira();
            else if (tipo == 'e') novaPlanta = new ErvaDaninha();
            else if (tipo == 'x') novaPlanta = new PlantaExotica();
            else {
                std::cout << "Tipo de planta desconhecido (c, r, e, x)." << std::endl;
                return;
            }

            pSolo->setPlanta(novaPlanta);
            std::cout << "Planta colocada com sucesso." << std::endl;
            jardim.exibirJardim();

        } else {
            std::cout << "Erro: Sintaxe. Uso: planta <l><c> <tipo>" << std::endl;
        }

    } else if (comando == "colhe") {
        std::string coords;
        if (iss >> coords && coords.length() == 2) {
            int l = (coords[0] >= 'a') ? coords[0] - 'a' : coords[0] - 'A';
            int c = (coords[1] >= 'a') ? coords[1] - 'a' : coords[1] - 'A';

            if (!jardineiro.gastarColheita()) {
                std::cout << "O jardineiro nao pode colher mais neste turno." << std::endl;
                return;
            }

            PosicaoSolo* pSolo = jardim.getPosicao(l, c);
            if (pSolo && pSolo->getPlanta() != nullptr) {
                delete pSolo->getPlanta(); // Apaga o objeto da memória
                pSolo->setPlanta(nullptr); // Limpa o ponteiro no solo
                std::cout << "Planta colhida." << std::endl;
                jardim.exibirJardim();
            } else {
                std::cout << "Nao ha planta para colher ai." << std::endl;
            }
        } else {
            std::cout << "Erro: Sintaxe. Uso: colhe <l><c>" << std::endl;
        }

    } else if (comando == "compra") {
        std::string tipoStr;
        if (iss >> tipoStr && tipoStr.length() == 1) {
            char tipo = tipoStr[0];
            Ferramenta* novaF = nullptr;

            if (tipo == 'g') novaF = new Regador();
            else if (tipo == 'a') novaF = new PacoteAdubo();
            else if (tipo == 't') novaF = new TesouraPoda();
            else if (tipo == 'z') novaF = new FerramentaZ();
            else {
                std::cout << "Ferramenta desconhecida (g, a, t, z)." << std::endl;
                return;
            }

            if (jardineiro.comprarFerramenta(novaF)) {
                std::cout << "Ferramenta comprada! ID: " << novaF->getNumeroSerie() << std::endl;
            } else {
                delete novaF;
                std::cout << "Erro ao comprar ferramenta." << std::endl;
            }
        } else {
            std::cout << "Erro: Sintaxe. Uso: compra <tipo>" << std::endl;
        }

    } else if (comando == "pega") {
        int id;
        if (iss >> id) {
            if (jardineiro.pegarFerramenta(id)) {
                std::cout << "Ferramenta " << id << " equipada na mao." << std::endl;
            } else {
                std::cout << "Ferramenta " << id << " nao encontrada no inventario." << std::endl;
            }
        } else {
            std::cout << "Erro: Sintaxe. Uso: pega <id>" << std::endl;
        }

    } else if (comando == "larga") {
        jardineiro.largarFerramenta();
        std::cout << "Ferramenta largada para o inventario." << std::endl;

    } else if (comando == "lferr") {
        std::cout << "--- Inventario ---" << std::endl;
        // Listar ferramenta na mão
        Ferramenta* mao = jardineiro.getFerramentaNaMao();
        if (mao) {
            std::cout << "MAO: " << mao->getCharRepresentacao() << " (ID: " << mao->getNumeroSerie() << ")" << std::endl;
        } else {
            std::cout << "MAO: Vazia" << std::endl;
        }
        // Listar mochila
        for (Ferramenta* f : jardineiro.getInventario()) {
            std::cout << "MOCHILA: " << f->getCharRepresentacao() << " (ID: " << f->getNumeroSerie() << ")" << std::endl;
        }

    } else if (comando == "lplantas" || comando == "larea" || comando == "lplanta" || comando == "lsolo") {
        // Implementar listagens detalhadas depois
        std::cout << "Comando de listagem validado (logica completa em breve)." << std::endl;

    } else if (comando == "e" || comando == "d" || comando == "c" || comando == "b" || comando == "entra" || comando == "sai") {
        // Implementar movimento depois
        std::cout << "Comando de movimento validado (logica completa em breve)." << std::endl;

    } else {
        std::cout << "Comando desconhecido: '" << comando << "'" << std::endl;
    }
}