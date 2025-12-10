//
// Created by 2003j on 13/10/2025.
//

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
#include <cstdlib>
#include <ctime>
#include <vector>

Simulador::Simulador() : aExecutar(true) {
    std::srand(std::time(nullptr));
}

void Simulador::run() {
    std::cout << "Bem-vindo ao Simulador de Jardim!" << std::endl;
    std::cout << "Para comecar, crie um jardim: jardim <linhas> <colunas>" << std::endl;

    std::string linhaComando;
    while (aExecutar) {
        std::cout << "> ";
        if (!std::getline(std::cin, linhaComando)) {
            break;
        }
        if (linhaComando.empty()) continue;
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
                jardim.exibirJardim(jardineiro.getLinha(), jardineiro.getColuna());
            }
        } else {
            std::cout << "Erro: Sintaxe. Uso: jardim <linhas> <colunas>" << std::endl;
        }
        return;
    }

    if (comando == "executa") {
        std::cout << "Comando executa ainda nao implementado." << std::endl;
        return;
    }

    if (!jardim.isJardimCriado()) {
        std::cout << "Erro: O jardim ainda nao foi criado." << std::endl;
        return;
    }

    // --- MOTOR DE TEMPO (AVANCA) ---
    if (comando == "avanca") {
        int n = 1;
        iss >> n;
        if (n <= 0) n = 1;

        std::cout << "Simulando " << n << " instantes..." << std::endl;

        for (int i = 0; i < n; ++i) {

            // 1. AÇÃO AUTOMÁTICA DA FERRAMENTA NA MÃO
            if (jardineiro.estaNoJardim() && jardineiro.getFerramentaNaMao() != nullptr) {
                Ferramenta* f = jardineiro.getFerramentaNaMao();
                PosicaoSolo* soloJardineiro = jardim.getPosicao(jardineiro.getLinha(), jardineiro.getColuna());

                if (soloJardineiro != nullptr) {
                    bool usou = f->usar(*soloJardineiro);
                    if (usou && f->quebrou()) {
                        std::cout << "A ferramenta " << f->getCharRepresentacao() << " (ID: " << f->getNumeroSerie() << ") partiu-se!" << std::endl;
                        jardineiro.removerFerramentaMao();
                        delete f;
                    }
                }
            }

            // 2. CICLO DE VIDA DAS PLANTAS
            struct Bebes { int l; int c; Planta* p; };
            std::vector<Bebes> maternidade;

            for (int l = 0; l < jardim.getNumLinhas(); ++l) {
                for (int c = 0; c < jardim.getNumColunas(); ++c) {
                    PosicaoSolo* pSolo = jardim.getPosicao(l, c);
                    Planta* planta = pSolo->getPlanta();

                    if (planta != nullptr) {
                        // Viver
                        planta->viver(*pSolo);

                        // Morrer
                        if (planta->deveMorrer()) {
                            delete planta;
                            pSolo->setPlanta(nullptr);
                            continue;
                        }

                        // Reproduzir
                        if (planta->querReproduzir()) {
                            int dl[] = {-1, 1, 0, 0};
                            int dc[] = {0, 0, -1, 1};

                            for (int k = 0; k < 4; ++k) {
                                int nl = l + dl[k];
                                int nc = c + dc[k];
                                PosicaoSolo* vizinho = jardim.getPosicao(nl, nc);

                                if (vizinho != nullptr && vizinho->getPlanta() == nullptr) {
                                    Planta* novaPlanta = planta->reproduzir();
                                    maternidade.push_back({nl, nc, novaPlanta});
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            // 3. PROCESSAR NASCIMENTOS
            for (const auto& bb : maternidade) {
                PosicaoSolo* pSolo = jardim.getPosicao(bb.l, bb.c);
                if (pSolo->getPlanta() == nullptr) {
                    pSolo->setPlanta(bb.p);
                } else {
                    delete bb.p;
                }
            }
        }

        jardineiro.resetarAcoes();
        std::cout << "Passaram " << n << " instantes." << std::endl;
        jardim.exibirJardim(jardineiro.getLinha(), jardineiro.getColuna());

    }
    // --- MOVIMENTO ---
    else if (comando == "e" || comando == "d" || comando == "c" || comando == "b" || comando == "entra") {
        int nl = jardineiro.getLinha();
        int nc = jardineiro.getColuna();

        if (comando == "entra") {
            std::string coords;
            if (iss >> coords && coords.length() == 2) {
                nl = (coords[0] >= 'a') ? coords[0] - 'a' : coords[0] - 'A';
                nc = (coords[1] >= 'a') ? coords[1] - 'a' : coords[1] - 'A';

                if (!jardineiro.estaNoJardim()) {
                    if (!jardineiro.gastarEntradaSaida()) { std::cout << "Sem entradas." << std::endl; return; }
                } else {
                    if (!jardineiro.gastarMovimento()) { std::cout << "Sem movimentos." << std::endl; return; }
                }
            } else { std::cout << "Erro sintaxe." << std::endl; return; }
        } else {
            if (!jardineiro.estaNoJardim()) { std::cout << "Nao esta no jardim." << std::endl; return; }
            if (comando == "e") nc--;
            else if (comando == "d") nc++;
            else if (comando == "c") nl--;
            else if (comando == "b") nl++;
            if (!jardineiro.gastarMovimento()) { std::cout << "Sem movimentos." << std::endl; return; }
        }

        PosicaoSolo* pSolo = jardim.getPosicao(nl, nc);
        if (!pSolo) { std::cout << "Fora dos limites." << std::endl; return; }

        if (comando == "entra" && !jardineiro.estaNoJardim()) jardineiro.entrarJardim(nl, nc);
        else jardineiro.setPosicao(nl, nc);

        std::cout << "Moveu-se para " << (char)('A' + nl) << (char)('A' + nc) << std::endl;

        // Apanhar Ferramenta
        if (pSolo->getFerramenta()) {
            Ferramenta* f = pSolo->getFerramenta();
            if (jardineiro.apanharFerramenta(f)) {
                pSolo->setFerramenta(nullptr);
                std::cout << "Apanhou: " << f->getCharRepresentacao() << " [" << f->getNumeroSerie() << "]" << std::endl;

                // Spawn Mágico
                for(int i=0; i<20; ++i) {
                    int rL = std::rand() % jardim.getNumLinhas();
                    int rC = std::rand() % jardim.getNumColunas();
                    PosicaoSolo* randP = jardim.getPosicao(rL, rC);
                    if(randP && !randP->getFerramenta() && (rL!=nl || rC!=nc)) {
                        int t = std::rand()%4;
                        Ferramenta* nf=nullptr;
                        if(t==0) nf=new Regador(); else if(t==1) nf=new PacoteAdubo();
                        else if(t==2) nf=new TesouraPoda(); else nf=new FerramentaZ();
                        randP->setFerramenta(nf);
                        break;
                    }
                }
            }
        }
        jardim.exibirJardim(jardineiro.getLinha(), jardineiro.getColuna());

    } else if (comando == "sai") {
        if(jardineiro.estaNoJardim() && jardineiro.gastarEntradaSaida()) {
            jardineiro.sairJardim();
            std::cout << "Saiu do jardim." << std::endl;
        } else std::cout << "Nao pode sair." << std::endl;

    } else if (comando == "planta") {
        std::string c, t;
        if(iss >> c >> t) {
            int l = (c[0]>='a'?c[0]-'a':c[0]-'A');
            int col = (c[1]>='a'?c[1]-'a':c[1]-'A');
            if(!jardineiro.gastarPlantacao()) { std::cout << "Sem plantacoes." << std::endl; return; }
            PosicaoSolo* ps = jardim.getPosicao(l, col);
            if(ps && !ps->getPlanta()) {
                Planta* np = nullptr;
                if(t[0]=='c') np=new Cato(); else if(t[0]=='r') np=new Roseira();
                else if(t[0]=='e') np=new ErvaDaninha(); else if(t[0]=='x') np=new PlantaExotica();
                if(np) { ps->setPlanta(np); std::cout << "Plantou " << np->getEspecie() << std::endl; jardim.exibirJardim(jardineiro.getLinha(), jardineiro.getColuna()); }
                else std::cout << "Tipo invalido." << std::endl;
            } else std::cout << "Posicao ocupada ou invalida." << std::endl;
        }

    } else if (comando == "colhe") {
        std::string c;
        if(iss >> c) {
            int l = (c[0]>='a'?c[0]-'a':c[0]-'A');
            int col = (c[1]>='a'?c[1]-'a':c[1]-'A');
            if(!jardineiro.gastarColheita()) { std::cout << "Sem colheitas." << std::endl; return; }
            PosicaoSolo* ps = jardim.getPosicao(l, col);
            if(ps && ps->getPlanta()) { delete ps->getPlanta(); ps->setPlanta(nullptr); std::cout << "Colhido." << std::endl; jardim.exibirJardim(jardineiro.getLinha(), jardineiro.getColuna()); }
            else std::cout << "Nada para colher." << std::endl;
        }

    } else if (comando == "compra") {
        std::string t; iss >> t;
        Ferramenta* f=nullptr;
        if(t[0]=='g') f=new Regador(); else if(t[0]=='a') f=new PacoteAdubo();
        else if(t[0]=='t') f=new TesouraPoda(); else if(t[0]=='z') f=new FerramentaZ();
        if(f) { jardineiro.comprarFerramenta(f); std::cout << "Comprou ID " << f->getNumeroSerie() << std::endl; }

    } else if (comando == "pega") {
        int id; iss >> id;
        if(jardineiro.pegarFerramenta(id)) std::cout << "Equipado." << std::endl;
        else std::cout << "Nao encontrado." << std::endl;

    } else if (comando == "larga") {
        jardineiro.largarFerramenta();
        std::cout << "Largado." << std::endl;

    } else if (comando == "lferr") {
        std::cout << "--- Inventario ---" << std::endl;
        if(jardineiro.getFerramentaNaMao()) std::cout << "MAO: " << jardineiro.getFerramentaNaMao()->getCharRepresentacao() << " [" << jardineiro.getFerramentaNaMao()->getNumeroSerie() << "]" << std::endl;
        else std::cout << "MAO: Vazia" << std::endl;
        for(auto* f : jardineiro.getInventario()) std::cout << "MOCHILA: " << f->getCharRepresentacao() << " [" << f->getNumeroSerie() << "]" << std::endl;

    } else if (comando == "lplantas" || comando == "lsolo" || comando == "lplanta" || comando == "larea") {
        std::cout << "Listagens detalhadas em breve." << std::endl;
    } else {
        std::cout << "Comando desconhecido." << std::endl;
    }
}