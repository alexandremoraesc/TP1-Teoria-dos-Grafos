#include <vector>

using namespace std;

struct MinHeapNode {
    public:
        int v;
        double dist;
};

class BinHeap{
    private:
        vector<MinHeapNode> heapvector;
        int currentSize;
        int capacity;
        vector<int> pos;

    public:
        BinHeap(vector<MinHeapNode>, int);
        void percUp(int);
        void insert(MinHeapNode);
        void percDown(int);
        int minChild(int);
        MinHeapNode delMin();
        void buildheap(vector<MinHeapNode>);
        bool isEmpty();
        int findMin();
        void decreaseKey(int, double);
        double getDist(int);
};

