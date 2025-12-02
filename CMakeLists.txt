cmake_minimum_required(VERSION 3.29)
project(Projeto)

set(CMAKE_CXX_STANDARD 20)

add_executable(Projeto main.cpp
        include/Settings.h
        src/Jardim.cpp
        src/Jardineiro.cpp
        src/PosicaoSolo.cpp
        include/Planta.h
        src/Planta.cpp
        src/Ferramenta.cpp
        include/Simulador.h
        src/Simulador.cpp
        include/Ferramenta.h
        include/cato.h
        src/Cato.cpp
        src/Roseira.cpp
        include/ErvaDaninha.h
        src/Regador.cpp
        include/FerramentaZ.h
        include/PacoteAdubo.h
        include/PlantaExotica.h
        include/TesouraPoda.h
        src/ErvaDaninha.cpp
        src/PacoteAdubo.cpp
        src/PlantaExotica.cpp
        src/TesouraPoda.cpp
        src/FerramentaZ.cpp)
