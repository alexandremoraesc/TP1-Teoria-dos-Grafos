#include <vector>
#include <string>

using namespace std;

#ifndef ARESTA_H
#define ARESTA_H

class Aresta { 
    public:
        Aresta(int, int, double = 1);
        void printAresta();
        vector<int> getVertices();
        double getPeso();

        bool operator <(const Aresta &);
        bool operator >(const Aresta &);
    private:
        vector<int> vertices;  
        double peso;
};

#endif