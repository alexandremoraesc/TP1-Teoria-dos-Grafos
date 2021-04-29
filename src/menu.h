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

    private:
        bool continuar; 


};

#endif
