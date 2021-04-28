#include "aresta.h"
#include <iostream>

using namespace std; 

Aresta::Aresta(int v1, int v2) {
    vertices.push_back(v1);
    vertices.push_back(v2);
}

void Aresta::printAresta() {
        cout << "Aresta " << vertices.at(0)
        << '-' << vertices.at(1) << endl; 
}

vector<int> Aresta::getVertices() {
    return vertices;
}