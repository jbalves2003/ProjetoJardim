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
#include <fstream>

Simulador::Simulador() : aExecutar(true) {
    std::srand(std::time(nullptr));
}

void Simulador::run() {
    std::cout << "Bem-vindo ao Simulador de Jardim!" << std::endl;
    std::cout << "Comandos: jardim, planta, colhe, avanca, executa, grava, recupera..." << std::endl;

    std::string linhaComando;
    while (aExecutar) {
        std::cout << "> ";
        if (!std::getline(std::cin, linhaComando)) break;
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
        } else std::cout << "Erro: Sintaxe. Uso: jardim <linhas> <colunas>" << std::endl;
        return;
    }

    // Ler Ficheiro
    if (comando == "executa") {
        std::string nome;
        if (iss >> nome) {
            std::ifstream f(nome);
            if (f.is_open()) {
                std::cout << "--- Executando " << nome << " ---" << std::endl;
                std::string l;
                while (std::getline(f, l)) {
                    if (l.empty()) continue;
                    std::cout << ">> " << l << std::endl;
                    processarLinhaComando(l);
                }
                f.close();
                std::cout << "--- Fim de " << nome << " ---" << std::endl;
            } else std::cout << "Erro ao abrir " << nome << std::endl;
        }
        return;
    }

    // --- GRAVA estado
    if (comando == "grava") {
        if (!jardim.isJardimCriado()) { std::cout << "Nada para gravar." << std::endl; return; }
        std::string nome;
        if (iss >> nome) {
            std::ofstream f(nome);
            if (f.is_open()) {
                //  Dimensoes
                f << jardim.getNumLinhas() << " " << jardim.getNumColunas() << std::endl;
                //  Jardineiro
                f << jardineiro.getLinha() << " " << jardineiro.getColuna() << std::endl;
                //  Inventario
                f << jardineiro.getInventario().size() << std::endl;
                for(auto* ferr : jardineiro.getInventario())
                    f << ferr->getCharRepresentacao() << " " << ferr->getNumeroSerie() << " " << ferr->getDurabilidade() << std::endl;
                // Mao
                if(jardineiro.getFerramentaNaMao()) {
                    f << "1 " << jardineiro.getFerramentaNaMao()->getCharRepresentacao() << " "
                      << jardineiro.getFerramentaNaMao()->getNumeroSerie() << " " << jardineiro.getFerramentaNaMao()->getDurabilidade() << std::endl;
                } else f << "0" << std::endl;
                // 4. Tabuleiro
                for(int l=0; l<jardim.getNumLinhas(); ++l) {
                    for(int c=0; c<jardim.getNumColunas(); ++c) {
                        PosicaoSolo* p = jardim.getPosicao(l, c);
                        f << p->getAgua() << " " << p->getNutrientes() << " ";
                        // Planta
                        if(p->getPlanta()) f << "1 " << p->getPlanta()->getCharRepresentacao() << " " << p->getPlanta()->getIdade() << " ";
                        else f << "0 ";
                        // Ferramenta Chao
                        if(p->getFerramenta()) f << "1 " << p->getFerramenta()->getCharRepresentacao() << " " << p->getFerramenta()->getNumeroSerie() << " " << p->getFerramenta()->getDurabilidade() << " ";
                        else f << "0 ";
                        f << std::endl;
                    }
                }
                f.close();
                std::cout << "Gravado em " << nome << std::endl;
            } else std::cout << "Erro ao gravar." << std::endl;
        }
        return;
    }

    // recupera estado
    if (comando == "recupera") {
        std::string nome;
        if (iss >> nome) {
            std::ifstream f(nome);
            if (f.is_open()) {
                jardim.limparJardim();
                jardineiro.resetarAcoes();
                while(!jardineiro.getInventario().empty()) {
                    break;
                }
                jardineiro.removerFerramentaMao();

                int L, C; f >> L >> C;
                jardim.criarJardim(L, C);

                int jL, jC; f >> jL >> jC;
                if(jL != -1) jardineiro.entrarJardim(jL, jC);

                int qtdInv; f >> qtdInv;
                for(int i=0; i<qtdInv; ++i) {
                    char t; int id, d; f >> t >> id >> d;
                    Ferramenta* nf=nullptr;
                    if(t=='g') nf=new Regador(); else if(t=='a') nf=new PacoteAdubo();
                    else if(t=='t') nf=new TesouraPoda(); else if(t=='z') nf=new FerramentaZ();
                    if(nf) jardineiro.comprarFerramenta(nf);
                }
                int temMao; f >> temMao;
                if(temMao) {
                    char t; int id, d; f >> t >> id >> d;
                    Ferramenta* nf=nullptr;
                    if(t=='g') nf=new Regador(); else if(t=='a') nf=new PacoteAdubo();
                    else if(t=='t') nf=new TesouraPoda(); else if(t=='z') nf=new FerramentaZ();
                    if(nf) { jardineiro.comprarFerramenta(nf); jardineiro.pegarFerramenta(nf->getNumeroSerie()); }
                }

                for(int l=0; l<L; ++l) {
                    for(int c=0; c<C; ++c) {
                        int a, n; f >> a >> n;
                        PosicaoSolo* p = jardim.getPosicao(l, c);
                        p->setAgua(a); p->setNutrientes(n);

                        int temP; f >> temP;
                        if(temP) {
                            char t; int idad; f >> t >> idad;
                            Planta* np=nullptr;
                            if(t=='c') np=new Cato(); else if(t=='r') np=new Roseira();
                            else if(t=='e') np=new ErvaDaninha(); else if(t=='x') np=new PlantaExotica();
                            if(np) p->setPlanta(np);
                        }
                        int temF; f >> temF;
                        if(temF) {
                            char t; int id, d; f >> t >> id >> d;
                            Ferramenta* nf=nullptr;
                            if(t=='g') nf=new Regador(); else if(t=='a') nf=new PacoteAdubo();
                            else if(t=='t') nf=new TesouraPoda(); else if(t=='z') nf=new FerramentaZ();
                            if(nf) p->setFerramenta(nf);
                        }
                    }
                }
                f.close();
                std::cout << "Recuperado de " << nome << std::endl;
                jardim.exibirJardim(jardineiro.getLinha(), jardineiro.getColuna());
            } else std::cout << "Ficheiro nao encontrado." << std::endl;
        }
        return;
    }

    if (!jardim.isJardimCriado()) {
        std::cout << "Erro: O jardim ainda nao foi criado." << std::endl;
        return;
    }

    if (comando == "avanca") {
        int n = 1; iss >> n; if (n <= 0) n = 1;
        std::cout << "Simulando " << n << " instantes..." << std::endl;
        for (int i = 0; i < n; ++i) {
            if (jardineiro.estaNoJardim() && jardineiro.getFerramentaNaMao()) {
                Ferramenta* f = jardineiro.getFerramentaNaMao();
                PosicaoSolo* s = jardim.getPosicao(jardineiro.getLinha(), jardineiro.getColuna());
                if (s && f->usar(*s) && f->quebrou()) {
                    std::cout << "Ferramenta " << f->getCharRepresentacao() << " partiu-se!" << std::endl;
                    jardineiro.removerFerramentaMao(); delete f;
                }
            }
            struct Bebes { int l; int c; Planta* p; };
            std::vector<Bebes> mat;
            for (int l = 0; l < jardim.getNumLinhas(); ++l) {
                for (int c = 0; c < jardim.getNumColunas(); ++c) {
                    PosicaoSolo* p = jardim.getPosicao(l, c);
                    Planta* pl = p->getPlanta();
                    if (pl) {
                        pl->viver(*p);
                        if (pl->deveMorrer()) { delete pl; p->setPlanta(nullptr); continue; }
                        if (pl->querReproduzir()) {
                            int dl[]={-1,1,0,0}, dc[]={0,0,-1,1};
                            for(int k=0;k<4;++k) {
                                int nl=l+dl[k], nc=c+dc[k];
                                PosicaoSolo* viz = jardim.getPosicao(nl, nc);
                                if(viz && !viz->getPlanta()) { mat.push_back({nl, nc, pl->reproduzir()}); break; }
                            }
                        }
                    }
                }
            }
            for (const auto& b : mat) {
                PosicaoSolo* s = jardim.getPosicao(b.l, b.c);
                if (!s->getPlanta()) s->setPlanta(b.p); else delete b.p;
            }
        }
        jardineiro.resetarAcoes();
        std::cout << "Passaram " << n << " instantes." << std::endl;
        jardim.exibirJardim(jardineiro.getLinha(), jardineiro.getColuna());

    } else if (comando == "e" || comando == "d" || comando == "c" || comando == "b" || comando == "entra") {
        int nl = jardineiro.getLinha(), nc = jardineiro.getColuna();
        if (comando == "entra") {
            std::string c; if (iss >> c && c.length()==2) {
                nl = (c[0]>='a'?c[0]-'a':c[0]-'A'); nc = (c[1]>='a'?c[1]-'a':c[1]-'A');
                if((!jardineiro.estaNoJardim() && !jardineiro.gastarEntradaSaida()) || (jardineiro.estaNoJardim() && !jardineiro.gastarMovimento())) {
                    std::cout << "Sem acoes." << std::endl; return;
                }
            } else { std::cout << "Erro sintaxe." << std::endl; return; }
        } else {
            if (!jardineiro.estaNoJardim()) { std::cout << "Nao esta no jardim." << std::endl; return; }
            if(comando=="e") nc--; else if(comando=="d") nc++; else if(comando=="c") nl--; else if(comando=="b") nl++;
            if(!jardineiro.gastarMovimento()) { std::cout << "Sem movimentos." << std::endl; return; }
        }
        PosicaoSolo* ps = jardim.getPosicao(nl, nc);
        if (!ps) { std::cout << "Fora limites." << std::endl; return; }
        if (comando=="entra" && !jardineiro.estaNoJardim()) jardineiro.entrarJardim(nl, nc); else jardineiro.setPosicao(nl, nc);
        std::cout << "Moveu-se para " << (char)('A'+nl) << (char)('A'+nc) << std::endl;
        if (ps->getFerramenta()) {
            Ferramenta* f = ps->getFerramenta();
            if(jardineiro.apanharFerramenta(f)) {
                ps->setFerramenta(nullptr);
                std::cout << "Apanhou " << f->getCharRepresentacao() << std::endl;
                for(int i=0;i<20;++i) {
                    int rL=rand()%jardim.getNumLinhas(), rC=rand()%jardim.getNumColunas();
                    PosicaoSolo* rp = jardim.getPosicao(rL, rC);
                    if(rp && !rp->getFerramenta() && (rL!=nl || rC!=nc)) {
                        int x=rand()%4; Ferramenta* nf=nullptr;
                        if(x==0) nf=new Regador(); else if(x==1) nf=new PacoteAdubo(); else if(x==2) nf=new TesouraPoda(); else nf=new FerramentaZ();
                        rp->setFerramenta(nf); break;
                    }
                }
            }
        }
        jardim.exibirJardim(jardineiro.getLinha(), jardineiro.getColuna());

    } else if (comando == "sai") {
        if(jardineiro.estaNoJardim() && jardineiro.gastarEntradaSaida()) { jardineiro.sairJardim(); std::cout << "Saiu." << std::endl; }
        else std::cout << "Nao pode sair." << std::endl;

    } else if (comando == "planta") {
        std::string c, t;
        if(iss >> c >> t && jardineiro.gastarPlantacao()) {
            int l=(c[0]>='a'?c[0]-'a':c[0]-'A'), col=(c[1]>='a'?c[1]-'a':c[1]-'A');
            PosicaoSolo* ps = jardim.getPosicao(l, col);
            if(ps && !ps->getPlanta()) {
                Planta* np=nullptr;
                if(t[0]=='c') np=new Cato(); else if(t[0]=='r') np=new Roseira(); else if(t[0]=='e') np=new ErvaDaninha(); else if(t[0]=='x') np=new PlantaExotica();
                if(np) { ps->setPlanta(np); std::cout << "Plantou " << np->getEspecie() << std::endl; jardim.exibirJardim(jardineiro.getLinha(), jardineiro.getColuna()); }
            } else std::cout << "Ocupado ou invalido." << std::endl;
        } else std::cout << "Erro ou sem acoes." << std::endl;

    } else if (comando == "colhe") {
        std::string c;
        if(iss >> c && jardineiro.gastarColheita()) {
            int l=(c[0]>='a'?c[0]-'a':c[0]-'A'), col=(c[1]>='a'?c[1]-'a':c[1]-'A');
            PosicaoSolo* ps = jardim.getPosicao(l, col);
            if(ps && ps->getPlanta()) { delete ps->getPlanta(); ps->setPlanta(nullptr); std::cout << "Colhido." << std::endl; jardim.exibirJardim(jardineiro.getLinha(), jardineiro.getColuna()); }
            else std::cout << "Nada para colher." << std::endl;
        }

    } else if (comando == "compra") {
        std::string t; iss >> t;
        Ferramenta* f=nullptr;
        if(t[0]=='g') f=new Regador(); else if(t[0]=='a') f=new PacoteAdubo(); else if(t[0]=='t') f=new TesouraPoda(); else if(t[0]=='z') f=new FerramentaZ();
        if(f) { jardineiro.comprarFerramenta(f); std::cout << "Comprou ID " << f->getNumeroSerie() << std::endl; }

    } else if (comando == "pega") {
        int id; iss >> id;
        if(jardineiro.pegarFerramenta(id)) std::cout << "Equipado." << std::endl; else std::cout << "Nao existe." << std::endl;

    } else if (comando == "larga") {
        jardineiro.largarFerramenta(); std::cout << "Largado." << std::endl;

    } else if (comando == "lferr") {
        std::cout << "--- Inventario ---" << std::endl;
        if(jardineiro.getFerramentaNaMao()) std::cout << "MAO: " << jardineiro.getFerramentaNaMao()->getCharRepresentacao() << " [" << jardineiro.getFerramentaNaMao()->getNumeroSerie() << "]" << std::endl;
        else std::cout << "MAO: Vazia" << std::endl;
        for(auto* f : jardineiro.getInventario()) std::cout << "MOCHILA: " << f->getCharRepresentacao() << " [" << f->getNumeroSerie() << "]" << std::endl;

    } else if (comando == "lsolo") {
        std::string c; iss >> c;
        int l=(c[0]>='a'?c[0]-'a':c[0]-'A'), col=(c[1]>='a'?c[1]-'a':c[1]-'A');
        PosicaoSolo* p = jardim.getPosicao(l, col);
        if(p) {
            std::cout << "Agua: " << p->getAgua() << " Nutr: " << p->getNutrientes() << std::endl;
            if(p->getPlanta()) std::cout << "Planta: " << p->getPlanta()->getEspecie() << " (Idade: " << p->getPlanta()->getIdade() << ")" << std::endl;
            if(p->getFerramenta()) std::cout << "Ferr: " << p->getFerramenta()->getCharRepresentacao() << std::endl;
        }

    } else if (comando == "lplantas") {
        for(int l=0; l<jardim.getNumLinhas(); ++l)
            for(int c=0; c<jardim.getNumColunas(); ++c) {
                PosicaoSolo* p = jardim.getPosicao(l, c);
                if(p->getPlanta()) std::cout << (char)('A'+l) << (char)('A'+c) << ": " << p->getPlanta()->getEspecie() << std::endl;
            }

    } else if (comando == "larea") {
        for(int l=0; l<jardim.getNumLinhas(); ++l)
            for(int c=0; c<jardim.getNumColunas(); ++c) {
                PosicaoSolo* p = jardim.getPosicao(l, c);
                if(p->getPlanta() || p->getFerramenta()) {
                    std::cout << (char)('A'+l) << (char)('A'+c) << ": ";
                    if(p->getPlanta()) std::cout << p->getPlanta()->getEspecie() << " ";
                    if(p->getFerramenta()) std::cout << "[" << p->getFerramenta()->getCharRepresentacao() << "]";
                    std::cout << std::endl;
                }
            }

    } else {
        std::cout << "Comando desconhecido." << std::endl;
    }
}