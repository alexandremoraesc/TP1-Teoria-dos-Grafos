#include <vector>
#include <string>
#include <iostream>
#include "aresta.h"
#include <map>

using namespace std;

#ifndef GRAFOS_H
#define GRAFOS_H

class Grafo {
    public:
        Grafo();
        vector<vector<int>> BFS(int);
        vector<vector<int>> DFS(int);
        vector<int> Dijk(int);
        void printArestas();
        void printVertices();
        void setNumVertices(int);
        void setNumArestas(int);
        void setMatrizAdj(vector<vector<int>>);
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
        void printPath(vector<int>, int);
        vector<vector<int>> getComponentesConexas();
        bool matriz;
        vector<vector<int>> componentesconexas;
        map<pair<int, int>, int> arestasPesos;  
        bool arestaNeg; 

    private:
        vector<int> grausVertices;
        int numVertices;
        int numArestas;
        vector<vector<int>> matrizAdj;
        vector<vector<int>> listaAdj;
        vector<Aresta> arestas;
        vector<int> vertices;

};

#endif