#include <vector>
#include <string>

using namespace std;

#ifndef ARESTA_H
#define ARESTA_H

class Aresta { 
    public:
        Aresta(int, int, int = 1);
        void printAresta();
        vector<int> getVertices();
        int getPeso();

        bool operator <(const Aresta &);
        bool operator >(const Aresta &);
    private:
        vector<int> vertices;  
        int peso;
};

#endif