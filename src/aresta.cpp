#include "aresta.h"
#include <iostream>

using namespace std; 

Aresta::Aresta(int v1, int v2, double peso_) {
    vertices.push_back(v1);
    vertices.push_back(v2);
    peso = peso_;
}

void Aresta::printAresta() {
        cout << "Aresta " << vertices.at(0)
        << '-' << vertices.at(1) << endl; 
}

vector<int> Aresta::getVertices() {
    return vertices;
}

double Aresta::getPeso() {
    return peso;
}

bool Aresta::operator<(const Aresta &a) {
    if (a.peso > peso) {
        return true;
    }
    else {
        return false;
    }
}

bool Aresta::operator>(const Aresta &a) {
    if (a.peso < peso) {
        return true;
    }
    else {
        return false;
    }
}