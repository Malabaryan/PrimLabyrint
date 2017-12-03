
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "LinkedList.cpp"

using namespace std;

class AdjacencyList
{
private:
    int verticesCount;
    LinkedList<int>** array;

public:
    AdjacencyList(int pverticesCount) {

        verticesCount = pverticesCount;
        array = new LinkedList<int>* [pverticesCount];
        while(pverticesCount--){
            array[pverticesCount] = new LinkedList<int>();
        }

    }

    LinkedList<int>** getArray() {
        return array;
    }

    LinkedList<int>* getArrayOn(int index) {
        return array[index];
    }


    void clear() {
        int i = verticesCount;
        while (i--) {
            array[i]->clear();
        }
    }
};



class Graph
{
private:

    int V;
    bool directed;
    AdjacencyList* AdjList;
    bool* Mark;

public:

    Graph(int pV) {
        V = pV;
        AdjList = new AdjacencyList(pV);
        directed = false;
        Mark = new bool [pV];
    }

    Graph(int pV, bool pDirected) {
        V = pV;
        AdjList = new AdjacencyList(pV);
        directed = pDirected;
    }

    Graph(int pV, bool pDirected, AdjacencyList* pAdjList ) {
        V = pV;
        AdjList = pAdjList;
        directed = pDirected;
    }



    int getVerticesCount() {
        return V;
    }
    AdjacencyList* getAdjList() {
        return AdjList;
    }

// Adds an edge to an undirected graph
    void addEdge(int src, int dest)
    {
        AdjList->getArrayOn(src)->append(dest);
        if (!directed) {
            AdjList->getArrayOn(dest)->append(src);
        }

    }


    int getRowOf(int verticeNum) {
        if (verticeNum >= 30) {
            return (verticeNum / 30);
        }
        else
            return 0;
    }

    int getColumnOf(int verticeNum) {
        if (verticeNum >= 30) {
            return (verticeNum % 30);
        }
        else
            return verticeNum ;
    }

    /*
     * Para obtener los nodos "vecinos" en la "matriz" de nodos
     * que ocupamos para el laberinto, se saca el num de columna
     * del nodo actual y el num de fila del nodo actual.
     * Luego:
     *
     *
     * if(rowNum == 0){
     *     No tiene vecino arriba
     * }
     *
     * if(rowNum == 19){
     *     No tiene vecino abajo
     * }
     *
     * if(columnNum == 29){
     *     No tiene vecino derecho
     * }
     *
     * if(columnNum == 0){
     *     No tiene vecino izq
     * }
     *
     * VecinoIzq = numActualVertice - 1;
     * VecinoDer = numActualVertice + 1;
     * VecinoArriba = numActualVertice - 30;
     * VecinoAbajo  = numActualVertice + 30;
     *
     */

    bool* getMarkList(){

        return Mark;
    }

    bool getMark(int numVertice) {
        return Mark[numVertice];
    }

    void clearMark() {
        int cant = V;
        while (cant--) {
            Mark[cant] = false;
        }
    }

    void setMark(int numVertice, bool state) {
        Mark[numVertice] = state;
    }


    bool isEdge(int ini, int fin) {



        for (AdjList->getArrayOn(ini)->goToStart(); AdjList->getArrayOn(ini)->getPos() < AdjList->getArrayOn(ini)->getSize(); AdjList->getArrayOn(ini)->next())
        {
            if (AdjList->getArrayOn(ini)->getElement() == fin) {
                return true;
            }
        }
        return false;



    }

    void delEdge(){

    }

    void resetValues(){

        V = 0;
        directed = false;
        AdjList->clear();
        clearMark();


    }
};
