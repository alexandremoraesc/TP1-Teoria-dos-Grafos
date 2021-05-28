#include "grafos.h"
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include <limits.h>
#include "BinHeap.h"

using namespace std;


vector<double> path; 

Grafo::Grafo() {};

//Realiza uma BFS para um vértice v passado como raiz
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

            vector<double> vizinhos = matrizAdj.at(a);

            for (int i=1; i<vizinhos.size(); i++) {
                if (vizinhos[i] != 0) {
                    if(visitados[i] == 0) {
                        visitados[i] = 1;
                        explorados.push_back(i);
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

//Realiza uma DFS para um vértice v passado como raiz

vector<vector<int>> Grafo::DFS(int v) {
    if (matriz) {
        vector<int> visitados(numVertices+1,0);
        vector<int> marcados; 
        stack<int> pilha;

        vector<vector<int>> nivelPai(numVertices+1, vector<int>(2, -1));

        pilha.push(v);
        while (pilha.size() != 0) {
            int a = pilha.top();
            vector<double> vizinhos = matrizAdj.at(a);
            pilha.pop();
            if (visitados[a] == 0) {
                visitados[a] = 1;
                marcados.push_back(a);
                for(int i= vizinhos.size()-1; i>=0; i--) {
                    if(vizinhos.at(i) != 0) {
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

        vector<vector<int>> nivelPai(numVertices+1, vector<int>(2, -1));

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

//Seta o número de vértices do grafo em um atributo
void Grafo::setNumVertices(int v) {
    numVertices = v;
}

//Seta o número de arestas do grafo em um atributo
void Grafo::setNumArestas(int a) {
    numArestas = a;
}

//Calcula o grau de todos os vértices do grafo
vector<int> Grafo::getGraus() {
    if (matriz) {
        vector<int> graus;
        int cont = 0;

        for(int i=0; i<matrizAdj.size(); i++) {
            for(int j=0; j<matrizAdj.at(i).size(); j++) {
                if (matrizAdj.at(i).at(j) != 0) {
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

//Calcula o grau mínimo do grafo
int Grafo::getGrauMin() {
    int minGrau = grausVertices.at(1);

    for (int i=1; i<grausVertices.size(); i++) {
        if (grausVertices.at(i)<minGrau) {
            minGrau = grausVertices.at(i);
        }
    }

    return minGrau;
}

//Calcula o grau máximo do grafo
int Grafo::getGrauMax() {
    int maxGrau = 0;

    for (int i=0; i<grausVertices.size(); i++) {
        if (grausVertices.at(i)>maxGrau) {
            maxGrau = grausVertices.at(i);
        }
    }

    return maxGrau;
}

//Calcula o grau médio do grafo
int Grafo::getGrauMed() {
    int media;
    int soma = 0;

    for (int i=0; i<grausVertices.size(); i++) {
        soma += grausVertices.at(i);
    }
    media = static_cast<double>(soma)/numVertices;

    return media;
}

//Calcula a mediana de grau do grafo
int Grafo::getMedianaGrau() {
    sort(grausVertices.begin(), grausVertices.end());
    int k = numVertices/2;

    return grausVertices.at(k);
}

//Calcula a distância entre dois vértices
vector<double> Grafo::getDistancia(int v1, int v2) {
    if (existePeso) { 
        return getDistanciaDijk(v1, v2);
    }
    
}

//Calcula o diâmetro do grafo
/*
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
*/

//Seta a matriz de adjacência em um atributo
void Grafo::setMatrizAdj(vector<vector<double>> matrizadj) {
    matrizAdj = matrizadj;
}

//Seta o vector de adjacência em um atributo
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
//Adiciona uma aresta ao grafo
void Grafo::addAresta(Aresta a) {
    arestas.push_back(a);
    if (matriz == false) {
        arestasPesos.insert(make_pair(make_pair(a.getVertices()[0], a.getVertices()[1]), a.getPeso()));
        arestasPesos.insert(make_pair(make_pair(a.getVertices()[1], a.getVertices()[0]), a.getPeso()));
    }
}

int Grafo::getNumVertices() {
    return numVertices;
}

int Grafo::getNumArestas() {
    return numArestas;
}

//Função que retorna um vector com as componentes conexas do grafo
//Ideia é fazer uma BFS (começando em 1) e caso um vértice do grafo não esteja no resultado
//Fazer a BFS nele e seguir nessa lógica até todos os vértices serem visitados
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

vector<double> Grafo::getDistanciaDijk(int v1, int v2) {
    path.clear();
    vector<vector<double>> a = Dijk(v1);
    vector<vector<double>> distDijk;

    double dist = a[0][v2];
    
    vector<double> caminho = getPath(a[1], v2); 

    caminho.push_back(dist);
    

    return caminho;
}

//Algoritmo de Dijkstra implementado com binary heap
vector<vector<double>> Grafo::Dijk(int s) {
    path.clear();

    if (arestaNeg) {
        cout << "O algoritmo de Dijsktra não funciona em grafos com arestas de pesos negativos" << endl; 
        return {};
    }

    else {

        //Caso a implementação seja por matriz de adjacência

        if (matriz) {
            vector<vector<double>> dijks; 
            vector<int> marcados (numVertices +1, 0);
            vector<double> real_dist (numVertices + 1, 0);
            vector<double> parent (numVertices + 1, 0);

            MinHeapNode a;
            a.v = 0;
            a.dist = 0;

            BinHeap dist({a}, numVertices);
            
            for (int i = 1; i<=numVertices; i++) {
                MinHeapNode *ptr = new MinHeapNode;
                ptr->v = i;
                ptr->dist = INT_MAX; 
                dist.insert(*ptr);
                real_dist[i] = INT_MAX;
            }

            dist.decreaseKey(s, 0); 
            real_dist[s] = 0;
            parent[s] = -1;

            vector<int> S = {};
            while (S.size() != numVertices) {
                MinHeapNode a = dist.delMin(); 
                double d = a.dist;

                marcados[a.v] = 1; 

                //cout << a.v << endl;
                S.push_back(a.v);

                vector<double> vizinhosPeso = matrizAdj[a.v];
                //cout << "u = " << a.v << endl; 
                for (int i=1; i<vizinhosPeso.size(); i++) {
                    if (marcados[i] == 0) {
                        if (vizinhosPeso[i] > 0) {
                            //cout << "v = " << i << endl; 
                            //cout << "w(u,v) =  " << vizinhosPeso[i] << endl;
                            
                            //cout << "d[v] " << dist.getDist(i) << endl;
                            //cout << "d[u] " << d << endl; 
                            
                            if (dist.getDist(i) > d + vizinhosPeso[i]) {
                                double new_dist = d + vizinhosPeso[i];
                                dist.decreaseKey(i, new_dist);
                                //cout << "new d[v] = " << dist.getDist(i) << endl;
                                parent[i] = a.v;
                                real_dist[i] = new_dist; 
                            }
                        }
                    }
                }
            }
            dijks.push_back(real_dist);
            dijks.push_back(parent);
            
            return dijks;
        }

        //Caso a implementação seja por lista de adjacência
        else {
            vector<vector<double>> dijks;
            vector<int> marcados (numVertices +1, 0);
            vector<double> parent (numVertices + 1, 0);
            vector<double> real_dist (numVertices + 1, 0);
            MinHeapNode a;
            a.v = 0;
            a.dist = 0;

            BinHeap dist({a}, numVertices);
            
            //Cria um min heap binário para armazenar as distâncias
            for (int i = 1; i<=numVertices; i++) {
                MinHeapNode *ptr = new MinHeapNode;
                ptr->v = i;
                ptr->dist = INT_MAX; 
                dist.insert(*ptr);
                real_dist[i] = INT_MAX;
            }

            dist.decreaseKey(s, 0); 
            real_dist[s] = 0;
            parent[s] = -1;

            vector<int> S = {};
            while (S.size() != numVertices) {
                MinHeapNode a = dist.delMin(); 
                double d = a.dist;

                marcados[a.v] = 1; 

                S.push_back(a.v);

                vector<int> vizinhos = listaAdj[a.v-1];

                //cout << "u = " << a.v << endl; 

                for (int i=0; i<vizinhos.size(); i++) {
                    if (vizinhos[i] > 0) {
                        if (marcados[vizinhos[i]] == 0) {
                                double wuv = arestasPesos[make_pair(a.v, vizinhos[i])];
                                //cout << "v = " << vizinhos[i] << endl; 
                                //cout << "w(u,v) =  " << wuv << endl;
                                
                                //cout << "d[v] " << dist.getDist(vizinhos[i]) << endl;
                                //cout << "d[u] " << d << endl; 
                                

                                if (dist.getDist(vizinhos[i]) > d + wuv) {
                                    double new_dist = d + wuv;
                                    dist.decreaseKey(vizinhos[i], new_dist);
                                    //cout << "new d[v] = " << dist.getDist(vizinhos[i]) << endl;
                                    parent[vizinhos[i]] = a.v;
                                    real_dist[vizinhos[i]] = new_dist; 
                                }
                            
                        }
                    }
                }
            }
            dijks.push_back(real_dist);
            dijks.push_back(parent);
            
            return dijks; 
        }
    }
}

vector<double> Grafo::getPath(vector<double> parent, int j) {

    if (!cleared) {
        path.clear(); 
        cleared = true;
    }

    if(parent[j] == -1) {
        path.push_back(j);
        return path; 
    }

    getPath(parent, parent[j]);

    path.push_back(j);
    return path;
}

vector<Aresta> Grafo::Kruskal() { 
    vector<Aresta> MST;
    vector<int> parents(numVertices + 1, 0);
    sort(arestas.begin(), arestas.end());
    double MSTtotal = 0;
    

    MST.push_back(arestas[0]);
    MSTtotal += arestas[0].getPeso();

    parents[arestas[0].getVertices()[1]] = arestas[0].getVertices()[0];


    for (int i=1; i< arestas.size(); i++) {
        int v1 = arestas[i].getVertices()[0];
        int v2 = arestas[i].getVertices()[1];
        if (MST.size() != numVertices - 1) {
            if (parents[v2] == 0) {
                MST.push_back(arestas[i]);
                parents[v2] = v1;
                MSTtotal += arestas[i].getPeso();
            }
        }
        else { 
            break;
        }
    }
    MSTSum = MSTtotal;
    return MST;
}

double Grafo::getExcent(int v, vector<double> dist) { 
    double excent = 0;

    for (int i=1; i<dist.size(); i++) {
        if (dist[i] > excent) {
            excent = dist[i];
        }
    }

    return excent;
}