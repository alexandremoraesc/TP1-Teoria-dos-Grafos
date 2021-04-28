#include "grafos.h"
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include <limits.h>


using namespace std;

Grafo::Grafo() {};

vector<vector<int>> Grafo::BFS(int v) {
    if (matriz) {
        //Define o vetor de vértices marcados e a fila Q
        vector<int> explorados;
        vector<int> visitados(numVertices+1, 0);
        queue<int> Q;

        vector<vector<int>> nivelPai(numVertices+1, vector<int>(2));

        explorados.push_back(v);
        visitados[v] = 1;
        Q.push(v);

        while(Q.size() != 0) {
            int a = Q.front();
            Q.pop();

            vector<bool> vizinhos = matrizAdj.at(a);

            for (int i=1; i<vizinhos.size(); i++) {
                if (vizinhos[i] == 1) {
                    if(visitados[vizinhos[i]] == 0) {
                        visitados[vizinhos[i]] = 1;
                        explorados.push_back(vizinhos[i]);
                        Q.push(i);
                        nivelPai.at(i).at(0) = a;
                        nivelPai.at(i).at(1) = nivelPai.at(a).at(1) + 1;
                    }
                }
            }
            
        }
        nivelPai.push_back(explorados);

        return nivelPai;
    }

    else {
        vector<int> explorados;
        vector<int> visitados(numVertices+1, 0);
        queue<int> Q;

        vector<vector<int>> nivelPai(numVertices+1, vector<int>(2));

        explorados.push_back(v);
        visitados[v] = 1; 
        Q.push(v);

        while (Q.size() != 0) {
    
            int a = Q.front();
            vector<int> vizinhos = listaAdj.at(a-1);
            Q.pop();

            //Organizando em ordem crescente
            sort(vizinhos.begin(), vizinhos.end());

            for (int i=0; i<vizinhos.size(); i++) {
                //Checa se já está em marcados]
                if (visitados[vizinhos[i]] == 0){
                    visitados[vizinhos[i]] = 1;
                    explorados.push_back(vizinhos.at(i));
                    Q.push(vizinhos.at(i));
                    nivelPai.at(vizinhos.at(i)).at(0) = a;
                    nivelPai.at(vizinhos.at(i)).at(1) = nivelPai.at(a).at(1) + 1;
                }
            }
        }

        nivelPai.push_back(explorados);
        return nivelPai;
    }

}

vector<vector<int>> Grafo::DFS(int v) {
    if (matriz) {
        vector<int> visitados(numVertices+1,0);
        vector<int> marcados; 
        stack<int> pilha;

        vector<vector<int>> nivelPai(numVertices+1, vector<int>(2));

        pilha.push(v);
        while (pilha.size() != 0) {
            int a = pilha.top();
            vector<bool> vizinhos = matrizAdj.at(a);
            pilha.pop();
            if (visitados[a] == 0) {
                visitados[a] = 1;
                marcados.push_back(a);
                for(int i= vizinhos.size()-1; i>=0; i--) {
                    if(vizinhos.at(i) == 1) {
                        pilha.push(i);
                        if (visitados[i] == 0) {
                            nivelPai.at(i).at(0) = a;
                            nivelPai.at(i).at(1) = nivelPai.at(a).at(1) + 1;  
                        }
                    }
                }

            }
        }

        nivelPai.push_back(marcados);
        return nivelPai;
    }

    else {
        vector<int> visitados(numVertices +1, 0);
        vector<int> marcados; 
        stack<int> pilha;

        vector<vector<int>> nivelPai(numVertices+1, vector<int>(2));

        pilha.push(v);
        while (pilha.size() != 0) {

            int a = pilha.top();
            vector<int> vizinhos = listaAdj.at(a-1);
            sort(vizinhos.begin(), vizinhos.end(), greater<int>());

            pilha.pop();
            if (visitados[a]== 0) {
                visitados[a] = 1;
                marcados.push_back(a);
                for(int i= 0; i< vizinhos.size(); i++) {
                    pilha.push(vizinhos.at(i));
                    if(visitados[vizinhos.at(i)] == 0) {
                        nivelPai.at(vizinhos.at(i)).at(0) = a;
                        nivelPai.at(vizinhos.at(i)).at(1) = nivelPai.at(a).at(1) + 1;
                    }
                }

            }
        }

        nivelPai.push_back(marcados);
        return nivelPai;
    }
}

void Grafo::setNumVertices(int v) {
    numVertices = v;
}

void Grafo::setNumArestas(int a) {
    numArestas = a;
}

vector<int> Grafo::getGraus() {
    if (matriz) {
        vector<int> graus;
        int cont = 0;

        for(int i=0; i<matrizAdj.size(); i++) {
            for(int j=0; j<matrizAdj.at(i).size(); j++) {
                if (matrizAdj.at(i).at(j) == true) {
                    cont++;
                }
            }
            graus.push_back(cont);
            cont = 0; 
        }

        grausVertices = graus;
        return graus;
    }

    else {
        vector<int> graus; 
        int cont = 0;

        for(int i=0; i<listaAdj.size(); i++) {
            for (int j=0; j<listaAdj.at(i).size(); j++) {
                cont++;
            }
            graus.push_back(cont);
            cont = 0;
        }

        grausVertices = graus;
        return graus;
    }
}

int Grafo::getGrauMin() {
    int minGrau = grausVertices.at(1);

    for (int i=1; i<grausVertices.size(); i++) {
        if (grausVertices.at(i)<minGrau) {
            minGrau = grausVertices.at(i);
        }
    }

    return minGrau;
}

int Grafo::getGrauMax() {
    int maxGrau = 0;

    for (int i=0; i<grausVertices.size(); i++) {
        if (grausVertices.at(i)>maxGrau) {
            maxGrau = grausVertices.at(i);
        }
    }

    return maxGrau;
}

int Grafo::getGrauMed() {
    int media;
    int soma = 0;

    for (int i=0; i<grausVertices.size(); i++) {
        soma += grausVertices.at(i);
    }
    media = static_cast<double>(soma)/numVertices;

    return media;
}

int Grafo::getMedianaGrau() {
    sort(grausVertices.begin(), grausVertices.end());
    int k = numVertices/2;

    return grausVertices.at(k);
}

int Grafo::getDistancia(int v1, int v2, vector<vector<int>> bfs) {

    return abs(bfs.at(v2).at(1)-bfs.at(v1).at(1));
}

int Grafo::getDiametro() {
    int diametro = 0;
    vector<vector<int>> g = getComponentesConexas(); 

    if (g.size() > 1) {
        return INT_MAX;
    }

    else{
          
            for (int j=0; j<g[0].size(); j++) {
                vector<vector<int>> a = BFS(g[0][j]);
                for (int k=0; k<g[0].size(); k++) {
                    if (k>j) {
                        int d = getDistancia(g[0][j], g[0][k], a);
                        if (d > diametro) {
                            diametro = d;
                        }
                    }
                }
            }
        }

    return diametro;
}

void Grafo::setMatrizAdj(vector<vector<bool>> matrizadj) {
    matrizAdj = matrizadj;
}

void Grafo::setListaAdj(vector<vector<int>> lista) {
    listaAdj = lista;
}

void Grafo::printVertices() {
    for (int i=0; i < vertices.size(); i++) {
        cout << vertices.at(i) << endl;
    }
}

void Grafo::printArestas() {
    for (int i=0; i < arestas.size(); i++) {
        arestas.at(i).printAresta();
    }
}

void Grafo::addAresta(Aresta a) {
    arestas.push_back(a);
}

int Grafo::getNumVertices() {
    return numVertices;
}

int Grafo::getNumArestas() {
    return numArestas;
}

vector<vector<int>> Grafo::getComponentesConexas() {

    vector<vector<int>> a;
    vector<vector<int>> compConexas;
    vector<int> visitados(numVertices+1, 0);

    a = BFS(1);
    
    vector<int> marcados = a.back();
    cout << marcados.size() << endl;

    int n = marcados.size();

    for (int i=0; i<n; i++) {
        visitados[marcados[i]] = 1;
    }
    
    compConexas.push_back(marcados);

    while (n != numVertices) {
        for (int i=1; i<numVertices+1; i++) {
            if(visitados[i] == 0) {
                a = BFS(i);
                marcados = a.back();
                for (int j=0; j<marcados.size(); j++) {
                    visitados[marcados[j]] = 1;
                }
                compConexas.push_back(marcados);
                
                n += marcados.size();
            }
        }

    }
    componentesconexas = compConexas;
    return compConexas;
    
}
