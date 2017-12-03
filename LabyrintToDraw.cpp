#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Dijsktra.cpp"
#include <SDL2/SDL.h>


using namespace std;

class LabyrintToDraw
{

private:

    int size;
    LinkedList<SDL_Color>* ListColor;
    LinkedList<SDL_Rect>* ListShapes;

    /**
     * Agrega un color a la lista de colores
     * si el booleno es true agrega blanco, sino
     * agrega un anaranjado oscuro
     * @param white [description]
     */
    void addColor(bool white)
    {

        if(white)
        {
            ListColor->append({255,255,255,255});
        }
        else
        {
            ListColor->append({255,150,0,255});
        }
    }

    /**
     * Agrega un color  la lista de colores.
     * Lo agrega basado en los parametros recibidos.
     * @param r [description]
     * @param g [description]
     * @param b [description]
     * @param a [description]
     */
    void addColor(int r, int g, int b, int a)
    {

        ListColor->append({r,g,b,a});
    }

    /**
     * Agrega un cuadro al laberinto final. Dependiendo de los booleanos
     * agrega cuadros blancos para que se note el camino a seguir por el
     * laberinto o los pinta negros para marcar que es la solucion
     * @param up    [description]
     * @param down  [description]
     * @param left  [description]
     * @param right [description]
     */
    void addRectangle(bool up,bool down,bool left,bool right, bool solve = true)
    {

        // 24 es el tamanho de los cuadros
        // Tomando como base que los array empiezan en 0
        // Columna= num % CantColumnas
        // Fila=    num / CantColumnas

        //Mae solo asuma que esta vara esta bien

            if(solve){
            ListShapes->append({ (size % 30) * 24, (size / 30) * 24, 24, 24 });
            addColor(false);

            }

            if(up)
            {

                ListShapes->append({    ((size % 30) * 24) + 6, ((size / 30) * 24), 12, 6 });
                if(solve)
                    addColor(true);
                else
                    addColor(0,0,0,255);
            }
            if(down)
            {
                ListShapes->append({  ((size % 30) * 24) + 6, ((size / 30) * 24) + 18, 12, 6 });
                if(solve)
                    addColor(true);
                else
                    addColor(0,0,0,255);
            }
            if(left)
            {
                ListShapes->append({  ((size % 30) * 24), ((size / 30) * 24) + 6, 6, 12 });
                if(solve)
                    addColor(true);
                else
                    addColor(0,0,0,255);
            }
            if(right)
            {
                ListShapes->append({ ((size % 30) * 24) + 18, ((size / 30) * 24) + 6, 6, 12 });
                if(solve)
                    addColor(true);
                else
                    addColor(0,0,0,255);
            }

            ListShapes->append({ ((size % 30) * 24) + 6, ((size / 30) * 24) + 6, 12, 12 });
            if(solve)
                addColor(true);
            else
                    addColor(0,0,0,255);

    }

    /**
     * Devuelve un array de booleanos, para saber si tiene vecinos
     * en las posiciones correspondientes.
     * Arriba, abajo, izquierda, derecha
     * @param  node [description]
     * @return      [description]
     */
    bool* getVecinos(int node)
    {
        bool aristas [4];
        aristas[0] = true;
        aristas[1] = true;
        aristas[2] = true;
        aristas[3] = true;

        if(node < 30)
        {
            aristas[0] = false;
        }

        if(node > 569)
        {
            aristas[1] = false;
        }

        if(node == 29)
        {
            aristas[3] = false;
        }

        if(node == 0)
        {
            aristas[2] = false;
        }
    }


    /**
     * Busca en la linkedlist<int> el elemento buscado
     * @param  nodeList [description]
     * @param  node     [description]
     * @return          [description]
     */
    bool isOnLinkedList(LinkedList<int>* nodeList, int node)
    {
        if(nodeList->notEmpty())
        {

            for(nodeList->goToStart(); nodeList->getPos() < nodeList->getSize(); nodeList->next())
            {
                if(nodeList->getElement() == node)
                {
                    return true;
                }
            }

        }

        return false;

    }

    /**
     * Recibe la lista de adyacencia y agrega el nodo a la lista de
     * rectangulos.
     * @param adjacencyListToLab [description]
     * @param node               [description]
     */
    void addNodeToLabyrint(LinkedList<int>** adjacencyListToLab, int node)
    {
        addRectangle(
            isOnLinkedList( adjacencyListToLab[node] , (node - 30 )),
            isOnLinkedList( adjacencyListToLab[node] , (node + 30 )),
            isOnLinkedList( adjacencyListToLab[node] , (node - 1  )),
            isOnLinkedList( adjacencyListToLab[node] , (node + 1  ))

        );
    }

public:


    LabyrintToDraw()
    {
        ListColor = new LinkedList<SDL_Color>();
        ListShapes = new LinkedList<SDL_Rect>();
        size = 0;
    }

    /**
     * Recibe un grafo y a partir de el, genera las listas necesarias
     * Para que la DrawClass pinte el laberinto en pantalla
     * @param graphList [description]
     */
    void graphToList(Graph* graphList)
    {
        LinkedList<int>** AdjList = graphList->getAdjList()->getArray();
        int thisNum = 0;
        while(thisNum < 600)
        {
            addNodeToLabyrint(AdjList,thisNum);
            size++;
            thisNum++;
        }
    }

    /**
     * Recibe la lista de Marks y el grafo.
     * Para llamar esta funcion se tuvo que haber llamado antes
     * la funcion de Dijsktra para que las Mark esten actualizadas
     * y haber recorrido la lista que devuelve el Dijsktra para
     * marcar esos nodos en Mark
     * @param Mark  [description]
     * @param grafo [description]
     */
    void paintDijsktra(bool* Mark,Graph* grafo)
    {

        while(size--)
        {

            if(Mark[size])
            {

                addRectangle(
                    grafo->isEdge(size,size - 30),
                    grafo->isEdge(size,size + 30),
                    grafo->isEdge(size,size - 1),
                    grafo->isEdge(size,size + 1),
                    false);
            }
        }
        size = 599;

    }

    LinkedList<SDL_Color>* getListColor()
    {
        return ListColor;
    }

    LinkedList<SDL_Rect>* getListShapes()
    {
        return ListShapes;
    }

    void resetValues()
    {

        size = 0;
        ListColor->clear();
        ListShapes->clear();

    }
};
