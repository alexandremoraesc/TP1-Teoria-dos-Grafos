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
        vector<vector<double>> Dijk(int);
        vector<Aresta> Kruskal();
        void printArestas();
        void printVertices();
        void setNumVertices(int);
        void setNumArestas(int);
        void setMatrizAdj(vector<vector<double>>);
        void setListaAdj (vector<vector<int>>);
        void addAresta(Aresta);
        vector<int> getGraus();
        int getGrauMin();
        int getGrauMax();
        int getGrauMed();
        int getMedianaGrau();
        vector<double> getDistancia(int, int);
        vector<double> getDistanciaDijk(int, int);
        int getDiametro();
        int getNumVertices();
        int getNumArestas();
        double getExcent(int, vector<double>);
        vector<double> getPath(vector<double>, int);
        vector<vector<int>> getComponentesConexas();
        bool matriz;
        vector<vector<int>> componentesconexas;
        map<pair<int, int>, double> arestasPesos;  
        bool arestaNeg; 
        bool existePeso;
        bool cleared; 
        double MSTSum; 

    private:
        vector<int> grausVertices;
        int numVertices;
        int numArestas;
        vector<vector<double>> matrizAdj;
        vector<vector<int>> listaAdj;
        vector<Aresta> arestas;
        vector<int> vertices;

};

#endif