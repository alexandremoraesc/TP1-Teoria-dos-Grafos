#include <string>
#include <fstream>
#include <iostream>
#include "grafos.h"

using namespace std; 

#ifndef MENU_H
#define MENU_H

class Menu {
    public:
        Menu();
        void receberArquivo();
        void lerArquivo(string);
        void escreverSaida (Grafo);
        void mostrarMenu();
        void estudoDeCaso(Grafo);
        void printDijk(Grafo, string);
        void printBFS(Grafo, string);
        void printDFS(Grafo, string);
        void printMST(Grafo, string);
        void printDistancia(Grafo, string);

    private:
        bool continuar; 


};

#endif
