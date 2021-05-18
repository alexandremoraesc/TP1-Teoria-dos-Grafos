#include "menu.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

Menu::Menu() {
    continuar = true;
};

//Função que recebe o arquivo de texto com as informações do grafo
void Menu::receberArquivo() {
    
    string nome;
    char confirma;

    while (continuar) {

        cout << "Bem vindo ao meu programa de Grafos" << endl;
        cout << "Digite o nome do arquivo que deseja analisar: " << endl;
        cin >> nome;

        cout << "O arquivo é: " << nome << ". Confirma? Digite s ou n" << endl;
        cin >> confirma;

        if (confirma == 's') {
            break;
        }

    }

    lerArquivo(nome);
}

//Função que lê o arquivo e cria uma matriz ou um vector de adjacência para representar o grafo
void Menu::lerArquivo(string path) {
    ifstream arquivo; 
    Grafo grafo; 
            
    arquivo.open(path);
    if(!arquivo) {
        cout << "Arquivo não encontrado" << endl;
        return receberArquivo();
    }

    else{
        int opcao = 0;

            while (opcao != 2 && opcao != 1) {

            cout << "Você deseja usar 1.Matriz de Adjacência ou 2.Vetor de adjacência ? Digite o número. " << endl;
            cin >> opcao;

            }
        //Caso seja o tratamento de dados seja por matriz de adjacência
        if (opcao == 1) {
            grafo.matriz = true;

            int n;
    
            arquivo >> n;
            grafo.setNumVertices(n);

            //Cria a matriz de adjacencia, e seta todos os valores como false
            vector<vector<int>> matrizAdj(n+1, vector<int>(n+1, 0));

            //Le o arquivo e coloca os valores como true onde existe aresta, e soma uma aresta a contagem
            int nArestas = 0;
            string l;

            while(getline(arquivo, l)) {
                if (l.empty() == false) {
                    istringstream input(l);
                    int v1, v2, peso;
                    input >> v1 >> v2 >> peso;

                    grafo.addAresta(Aresta(v1, v2, peso));

                    matrizAdj.at(v1).at(v2) = peso;
                    matrizAdj.at(v2).at(v1) = peso;
                    nArestas++;
                }
            }
            grafo.setNumArestas(nArestas);
            grafo.setMatrizAdj(matrizAdj);
            cout << "Lido" << endl;
        }

        else {
            grafo.matriz = false;
            int n;

            arquivo >> n;
            grafo.setNumVertices(n);

            //Inicializando um vetor de vertice com n espaços
            vector<vector<int>> listaAdj(n); 

            //Inicializando um contador de arestas 
            int numArestas = 0;
            
            string l;

            while (getline(arquivo, l)) { 
                if (l.empty() == false) {

                    istringstream input(l);
                    int v1, v2;
                    input >> v1 >> v2;

                    grafo.addAresta(Aresta(v1, v2));
                    numArestas++;

                    listaAdj.at(v1-1).push_back(v2);
                    listaAdj.at(v2-1).push_back(v1);
                }
            }
            grafo.setNumArestas(numArestas);
            grafo.setListaAdj(listaAdj);
            cout << "Lido" << endl;
        }
        return escreverSaida(grafo);
    }
}

//Função que escreve todas as informações necessárias em um arquivo .txt
void Menu::escreverSaida(Grafo g) { 
    ofstream arquivo;
    int opcao;
    string nome;
    vector<vector<int>> b;

    cout << "Digite o nome do arquivo de saída" << endl;
    cin >> nome;

    arquivo.open(nome);
    arquivo << "Número de vértices: " << g.getNumVertices() << endl;
    arquivo << "Número de arestas: " << g.getNumArestas() << endl;
    g.getGraus();
    arquivo << "Grau mínimo: " << g.getGrauMin() << endl;
    arquivo << "Grau máximo: " << g.getGrauMax() << endl;
    arquivo << "Mediana de grau: " << g.getMedianaGrau() << endl;
    arquivo << "Grau médio: " << g.getGrauMed() << endl;
    //arquivo << "Diâmetro do grafo: " << g.getDiametro() << endl;
    arquivo << "\n";

    b = g.getComponentesConexas();

    for (int k = 0; k< b.size(); k++) {
        arquivo << "Componente " << k+1 << " ";
        arquivo << "Tamanho: " << b[k].size() << endl; 
        for (int l = 0; l<b.at(k).size(); l++) {
            arquivo << b.at(k).at(l) << " ";
        }
        arquivo << '\n';
    }


    cout << "Você deseja realizar uma 1.BFS ou 2.DFS? Digite qualquer outra tecla se não desejar. " << endl;
    cin >> opcao;

    if (opcao == 1) {
        int vertice;
        vector<vector<int>> a;
        vector<int> marcados;

        cout << "Digite o vértice que deseja começar a busca" << endl;
        cin >> vertice;

        a = g.BFS(vertice);

        marcados = a.back();

        arquivo << '\n';
        arquivo << "BFS vértice " << vertice << endl;
        arquivo << "Ordem de vértice marcados: " << endl;

        for (int i = 0; i<marcados.size(); i++) {
            arquivo << marcados.at(i) << " "; 
        }

        arquivo << '\n';

        for (int j = 0; j<a.back().size(); j++) {
            int v = a.back().at(j);
            arquivo << "Vértice " << v << endl;
            arquivo << "Pai: " << a.at(v).at(0) << endl;
            arquivo << "Nível: " << a.at(v).at(1) << endl;
            arquivo << '\n';
        }
    }

    else if (opcao == 2){
        int vertice;
        vector<vector<int>> a;
        vector<int> marcados;

        cout << "Digite o vértice que deseja começar a busca" << endl;
        cin >> vertice;

        a = g.DFS(vertice);

        marcados = a.back();

        arquivo << '\n';
        arquivo << "DFS vértice " << vertice << endl;
        arquivo << "Ordem de vértice marcados: " << endl;

        for (int i = 0; i<marcados.size(); i++) {
            arquivo << marcados.at(i) << " "; 
        }

        arquivo << '\n';
        arquivo << '\n';

        for (int j = 0; j<a.back().size(); j++) {
            int v = a.back().at(j);
            arquivo << "Vértice " << v << endl;
            arquivo << "Pai: " << a.at(v).at(0) << endl;
            arquivo << "Nível: " << a.at(v).at(1) << endl;
            arquivo << '\n';
        }

    }
}

