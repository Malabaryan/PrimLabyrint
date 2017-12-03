#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Graph.cpp"

using namespace std;

class Dijsktra
{

private:

/**
 * No usado, codigo del dijsktra base para el codigo que si se usa
 * @param Grafo      [description]
 * @param posInicial [description]
 */
static void DijkstraDraft(Graph* Grafo, int posInicial){

    Grafo->clearMark();
    LinkedList<int>* ColaQ = new LinkedList<int>();
    ColaQ->append(posInicial);
    Grafo->clearMark();
    Grafo->setMark(posInicial,true);
    int v = 0;
    int w = 0;
    LinkedList<int>* lista;
    while(ColaQ->getSize() != 0){
        v = ColaQ->pop();
        lista = Grafo->getAdjList()->getArray()[v];

        if(v == 599){
           //return ListaPrev;
        }

        for(lista->goToStart();lista->getPos() < lista->getSize();lista->next()){
            w = lista->getElement();
            if(Grafo->getMark(w) == false){
                Grafo->setMark(w,true);
                ColaQ->append(w);
                cout << "Elementos en cola " << ColaQ->getSize() << endl;
            }

        }

    }

    }

public:

/**
 * Algoritmo de dijsktra que toma como inicio el punto 0
 * y genera una lista de nodos a seguir desde ese nodo 0
 * hasta el nodo en posFinal.
 *
 */
static LinkedList<int>* DijkstraLabyrint(Graph* Grafo, int posFinal){
    Grafo->clearMark();
    LinkedList<int>* ListaPrev = new LinkedList<int>();
    LinkedList<int>* ColaQ = new LinkedList<int>();
    LinkedList<int>* lista;
    int w, v;

    ColaQ->append(0);

    while(v != posFinal){
        v = ColaQ->getLast();
        lista = Grafo->getAdjList()->getArray()[v];
        for(lista->goToStart();lista->getPos() < lista->getSize();lista->next()){
            w = lista->getElement();
            if(Grafo->getMark(w) == false){
                ColaQ->append(w);
                Grafo->setMark(w,true);
            }
        }
        if(ColaQ->getLast() == v){
            ColaQ->pop();
        }
    }
    Grafo->clearMark();
    return ColaQ;

}


};
