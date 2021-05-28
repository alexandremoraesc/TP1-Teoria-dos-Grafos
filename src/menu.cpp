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
    grafo.arestaNeg = false;
            
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
            vector<vector<double>> matrizAdj(n+1, vector<double>(n+1, 0));

            //Le o arquivo e coloca os valores como true onde existe aresta, e soma uma aresta a contagem
            int nArestas = 0;
            string l;

            while(getline(arquivo, l)) {
                if (l.empty() == false) {
                    istringstream input(l);
                    int v1, v2;
                    double peso; 

                    input >> v1 >> v2 >> peso;
                    
                    if (peso < 0) {
                        grafo.arestaNeg = true;
                    }

                    if (peso > 1) {
                        grafo.existePeso = true;
                    }
                    
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
                    double peso; 

                    input >> v1 >> v2 >> peso;
                    
                    if (peso < 0) {
                        grafo.arestaNeg = true;
                    }

                    if (peso > 1) {
                        grafo.existePeso = true;
                    }
                    
                    grafo.addAresta(Aresta(v1, v2, peso));
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
          //return estudoDeCaso(grafo);
    }
}

//Função que escreve todas as informações necessárias em um arquivo .txt
void Menu::escreverSaida(Grafo g) { 
    ofstream arquivo;
    int opcao;
    string nome;
    vector<vector<int>> b;

    cout << "Digite o nome do arquivo de saída com as informações do grafo" << endl;
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
        arquivo << endl;
    }
    
    arquivo << endl; 

    mostrarMenu(g, nome);
}

void Menu::estudoDeCaso(Grafo g) { 
    vector<Aresta> a = g.Kruskal();

    for (int i = 0; i < a.size(); i++) {
        a[i].printAresta();
    }
}

void Menu::printBFS(Grafo g, string nome) {
    int vertice;
    ofstream arquivo;
    vector<vector<int>> a;
    vector<int> marcados;

    arquivo.open(nome);

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

void Menu::printDFS(Grafo g, string nome) {
    int vertice;
    vector<vector<int>> a;
    vector<int> marcados;
    ofstream arquivo;

    arquivo.open(nome);

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

void Menu::printDijk(Grafo g, string nome) {

}

void Menu::printMST(Grafo g, string nome) {
    vector<Aresta> MST = g.Kruskal();

    ofstream arquivo;
    arquivo.open(nome, std::ios_base::app);
    arquivo << endl; 

    arquivo << "MST - Soma total = "  << g.MSTSum << endl;

    for (int i=0; i<MST.size(); i++) {
        int v1 = MST[i].getVertices()[0];
        int v2 = MST[i].getVertices()[1];
        double peso = MST[i].getPeso();
        cout << peso << endl; 
        arquivo << v1 << " " << v2 << " " << peso << endl;
    }
}

void Menu::mostrarMenu(Grafo g, string nome) {
    continuar = true;
    while (continuar) {

        cout << "1. Calcular a distância e caminho entre dois vértices" << endl;
        cout << "2. Calcular uma MST (Minimum Spanning Tree) para o grafo" << endl;
        cout << "3. Calcular a excentricidade de um vértice" << endl;
        cout << "4. Calcular a distância de um vértice para todos os outros" << endl;
        cout << "5. Sair" << endl;

        char escolha;
	
	    cin >> escolha;

        switch (escolha) {
        
            case '1':
                printDistancia(g, nome);
                break;
            
            case '2':
                printMST(g, nome);
                break;
            
            case '3':
                printExcen(g, nome);
                break;
                
            case '4':
                printDistTodos(g, nome);
                break;
            
            case '5':
                continuar = false;
                break;
                
            default:
                cout << "Por favor, escolha um número dentre os mostrados" << std::endl;
	}


    }




}

void Menu::printDistancia(Grafo g, string nome) {
    int v1, v2;
    char opcao;
    bool cont = true;
    ofstream arquivo;

    while (cont) {
        cout << "Digite o número do primeiro vértice" << endl;
        cin >> v1;

        cout << "Digite o número do segundo vértice" << endl;
        cin >> v2;
    
        cout << "Os vértices escolhidos são " << v1 << " e " << v2 << ". Confirma? Digite s ou n. " << endl;
        cin >> opcao;

        if (opcao == 's') {

            vector<double> distCaminho = g.getDistancia(v1, v2);
        
            arquivo.open(nome, std::ios_base::app);
            
            arquivo << endl; 

            arquivo << "Distância " << v1 << "-" << v2 << endl;
            arquivo << distCaminho.back() << endl;
     
            arquivo << "Caminho: " << endl;
            for (int i=0; i < distCaminho.size()-1; i++) {
                arquivo << distCaminho[i] << " ";
            }

            arquivo << endl; 

            cont = false;
        }
    } 
}

void Menu::printDistTodos(Grafo g, string nome) {
    int v1; 
    char opcao; 
    bool cont; 
    ofstream arquivo; 


    arquivo.open(nome, std::ios_base::app);

    while (cont) { 
        cout << "Escolha o vértice raiz" << endl;
        cin >> v1;

        cout << "O vértice escolhido foi " << v1 << ". Confirma? Digite s ou n. " <<endl;
        cin >> opcao;

        arquivo << "Vértice " << v1 << endl; 
        if (opcao == 's') {
            vector<vector<double>> a = g.Dijk(v1); 

            for (int i = 1; i < a[0].size(); i++) {
                arquivo << "Distância " << v1 << "-" << i << endl;
                arquivo << a[0][i] << endl; 

                arquivo << "Caminho: " << endl;
                g.cleared = false;
                vector<double> caminho = g.getPath(a[1], i);
                for (int i=0; i < caminho.size(); i++) {
                    arquivo << caminho[i] << " ";
                }
                arquivo << endl; 
            }
            cont = false;
        }

    }
}

void Menu::printExcen(Grafo g, string nome) {
    int v1; 
    char opcao; 
    bool cont; 
    ofstream arquivo; 


    arquivo.open(nome, std::ios_base::app);

    while (cont) { 
        cout << "Escolha o vértice raiz" << endl;
        cin >> v1;

        cout << "O vértice escolhido foi " << v1 << ". Confirma? Digite s ou n. " <<endl;
        cin >> opcao;

        if (opcao == 's') {
            arquivo << "Excentricidade do vértice " << v1 << endl; 
            vector<vector<double>> a = g.Dijk(v1); 
            arquivo << g.getExcent(v1, a[0]) << endl; 
            arquivo << endl; 
            cont = false;
        }
    }
}