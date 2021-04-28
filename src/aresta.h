#include <vector>
#include <string>

using namespace std;

#ifndef ARESTA_H
#define ARESTA_H

class Aresta { 
    public:
        Aresta(int, int);
        void printAresta();
        vector<int> getVertices();
    private:
        vector<int> vertices;  
};

#endif