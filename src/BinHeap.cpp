#include "BinHeap.h"
#include <stdlib.h>

BinHeap::BinHeap(vector<MinHeapNode> heapvector_, int capacity_){
            heapvector = heapvector_;
            capacity = capacity_;
            currentSize = 0;
            vector<int> a (capacity, 0);
            pos = a;
        }

void BinHeap::percUp(int i) {
    while ((i / 2) > 0){
        if (heapvector[i].dist < heapvector[i/2].dist){
            MinHeapNode tmp = heapvector[i/2];
            heapvector[i/2] = heapvector[i];
            heapvector[i] = tmp;

            //Mudando as posições dos nós
            pos[heapvector[i/2].v] = i;
            pos[heapvector[i].v] = i/2;

        }

        else {
            pos[heapvector[i/2].v] = i/2;
            pos[heapvector[i].v] = i;
        }
        i = i/2;
    }
}

void BinHeap::insert(MinHeapNode k){
    heapvector.push_back(k);
    currentSize = currentSize + 1;
    percUp(currentSize);
}


void BinHeap::percDown(int i){
        while ((i*2) <= currentSize){
            int mc = minChild(i);
            if (heapvector[i].dist > heapvector[mc].dist){
                MinHeapNode tmp = heapvector[i];
                heapvector[i] = heapvector[mc];
                heapvector[mc] = tmp;

                //Mudando as posições dos nós
                pos[heapvector[i].v] = mc;
                pos[heapvector[mc].v] = i;
            }
            else {
                pos[heapvector[i].v] = i;
                pos[heapvector[mc].v] = mc;
            }
            i = mc;
        }
    }

int BinHeap::minChild(int i){
    if (((i*2)+1) > currentSize){
        return i * 2;
    }
    else{
        if (heapvector[i*2].dist < heapvector[(i*2)+1].dist){
            return i * 2;
        }
        else{
            return (i * 2) + 1;
        }
    }
}

MinHeapNode BinHeap::delMin(){
    if (currentSize > 1){
        MinHeapNode retval = heapvector[1];
        heapvector[1] = heapvector[currentSize];
        currentSize = currentSize - 1;
        heapvector.pop_back();
        percDown(1);
        return retval;
    }
    else{
        MinHeapNode retval = heapvector[0];
        heapvector[1] = heapvector[currentSize];
        currentSize = currentSize - 1;
        heapvector.pop_back();
        percDown(1);
        return retval;
    }
}

/*
void BinHeap::buildheap(vector<int> avector){
    int i = avector.size() / 2;
    currentSize = avector.size();
    heapvector.insert(heapvector.end(), avector.begin(), avector.end());
    while (i > 0){
        percDown(i);
        i = i - 1;
    }
}
*/

bool BinHeap::isEmpty(){
    if (heapvector.size()>0){
        return false;
    }
    return true;
}

int BinHeap::findMin(){
    return heapvector[1].dist;
}

void BinHeap::decreaseKey(int v, int distan) {
    int ind = pos[v];
    heapvector[ind].dist = distan;
    percUp(ind);
}

int BinHeap::getDist(int vertice) {
    int ind = pos[vertice];
    return heapvector[ind].dist;
}

