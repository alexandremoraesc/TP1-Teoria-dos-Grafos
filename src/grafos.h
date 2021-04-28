#include <vector>
#include <string>
#include <iostream>
#include "aresta.h"

using namespace std;

#ifndef GRAFOS_H
#define GRAFOS_H

class Grafo {
    public:
        Grafo();
        vector<vector<int>> BFS(int);
        vector<vector<int>> DFS(int);
        void printArestas();
        void printVertices();
        void setNumVertices(int);
        void setNumArestas(int);
        void setMatrizAdj(vector<vector<bool>>);
        void setListaAdj (vector<vector<int>>);
        void addAresta(Aresta);
        vector<int> getGraus();
        int getGrauMin();
        int getGrauMax();
        int getGrauMed();
        int getMedianaGrau();
        int getDistancia(int, int, vector<vector<int>>);
        int getDiametro();
        int getNumVertices();
        int getNumArestas();
        vector<vector<int>> getComponentesConexas();
        bool matriz;
        vector<vector<int>> componentesconexas;
        
    private:
        vector<int> grausVertices;
        int numVertices;
        int numArestas;
        vector<vector<bool>> matrizAdj;
        vector<vector<int>> listaAdj;
        vector<Aresta> arestas;
        vector<int> vertices;

};

#endif