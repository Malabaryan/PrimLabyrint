    #include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "LabyrintToDraw.cpp"

using namespace std;

class PrimAlgorithm
{
private:

    Graph* graphFin;
    int camino [600];       // Lista de nodos que vamos recorriendo
    int actualCamino;       // Nodo actual en el que estamos
    int actual;             // Copia del nodo actual donde estamos
    int nodosEnCamino;      // size de el array de caminos
    int nodosEnCaminoCopia;

    int sinMarcar;          // Cantidad de nodos  por recorrer
    bool Mark[600];         // Si ya son parte del grafo final

    bool aristas [4];       // caminos arriba, abajo, izquierda, derecha


    /**
     * Reinicia aristas.
     *
     * Cambia en aristas los booleanos de los vecinos basado
     * en si supera los limites del rectangulo del laberinto
     * @param node : numero de nodo al que se le saca los vecinos
     */
    void getVecinosFirst(int node)
    {

        //bool aristas [4];
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

        if((node % 30) == 29)
        {

            aristas[3] = false;
        }

        if((node % 30) == 0)
        {
            aristas[2] = false;
        }
    }

    /**
     * Cambia en aristas los vecinos basado en si
     * los vecinos estan marcados o no.
     * @param node [description]
     */
    void getVecinosSecond(int node)
    {

        if(aristas[0])
        {
            if(Mark[node - 30] == true)
                aristas[0] = false;
        }
        if(aristas[1])
        {
            if(Mark[node + 30] == true)
                aristas[1] = false;
        }
        if(aristas[2])
        {
            if(Mark[node - 1] == true)
                aristas[2] = false;
        }
        if(aristas[3])
        {
            if(Mark[node + 1] == true)
                aristas[3] = false;
        }

    }

    /**
     * Genera un numero random entre 0, 1, 2 o 3
     * @return [description]
     */
    int genRandom()
    {

        int randonNumber;
        while(true)
        {
            randonNumber = rand() % 4 + 0;
            if(aristas[randonNumber])
            {
                return randonNumber;
            }
        }
    }

    /**
     * Basado en un random, devuelve uno de los vecinos
     *
     * @param  node [description]
     * @return      [description]
     */
    int getDestinoAleatorio( int node )
    {
        int randonNumber = genRandom();
        if(randonNumber == 0)
        {
            return (node - 30);
        }
        if(randonNumber == 1)
        {
            return (node + 30);
        }
        if(randonNumber == 2)
        {
            return (node - 1);
        }
        if(randonNumber == 3)
        {
            return (node + 1);
        }
        else
        {
            return (node + 1);
        }


    }

    /**
     * Revisa si quedan nodos sin marcar.
     * @return [description]
     */
    bool falseInMark()
    {
        int i = 600;
        while(i--)
        {
            if(Mark[i] == false)
            {
                return true;
            }

        }
        return false;
    }

    /**
     * Usa los dos metodos anteriores para determinar los vecinos.
     * Ademas, si no tiene vecinos disponibles, devuelve false.
     * @param  node [description]
     * @return      [description]
     */
    bool getVecinos(int node)
    {

        getVecinosFirst(actualCamino);
        getVecinosSecond(actualCamino);

        if(aristas[0] == false && aristas[1] == false && aristas[2] == false && aristas[3] == false)
        {
            return false;
        }
        return true;

    }
public:

    /**
     * Constructor
     */
    PrimAlgorithm()
    {
        graphFin = new Graph(600);
        camino[0] = 0;
        actualCamino = 0;
        actual = 0;
        nodosEnCamino = 1;
        sinMarcar = 600;

        while(sinMarcar--)
        {
            Mark[sinMarcar] = false;    // Ninguno ha sido marcado
        }
        Mark[0] = true;
        sinMarcar = 599;

        nodosEnCaminoCopia = nodosEnCamino;
    }

    void resetValues()
    {
        try{
            graphFin->getAdjList()->clear();
        }
        catch(exception e){
        }
        graphFin->clearMark();
        camino[0] = 0;
        actualCamino = 0;
        actual = 0;
        nodosEnCamino = 1;
        sinMarcar = 600;

        while(sinMarcar--)
        {
            Mark[sinMarcar] = false;    // Ninguno ha sido marcado
        }
        Mark[0] = true;
        sinMarcar = 599;

        nodosEnCaminoCopia = nodosEnCamino;

    }

    /**
     * Genera un grafo con nodos interconectados haciendo parecer
     * un laberinto y lo devuelve, usando el algoritmo de Prim
     * @return [description]
     */
    Graph* primLabyrint()
    {
        while(falseInMark())           // Mientras queden nodos sin marcar
        {
            if(getVecinos(actualCamino))    // Si tiene vecinos disponibles para tirar un Edge
            {
                Mark[actualCamino] = true;
                actualCamino = getDestinoAleatorio(actual );

                camino[nodosEnCamino] = actualCamino;
                nodosEnCamino++;
                nodosEnCaminoCopia = nodosEnCamino;

                graphFin->addEdge(actual,actualCamino);
                actual = actualCamino;
            }
            else                            // Nos devolvemos en los marcados
            {
                Mark[actualCamino] = true;
                nodosEnCaminoCopia--;
                actualCamino = camino[nodosEnCaminoCopia];
                actual = actualCamino;
            }
        }
        return graphFin;
    }
};
