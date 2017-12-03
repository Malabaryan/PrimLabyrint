
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "DrawClass.cpp"

using namespace std;

class Controller
{

private:

    Graph*              GrafoLaberinto;
    PrimAlgorithm*      Prim;
    LabyrintToDraw*     LabyirintTemplate;
    LinkedList<int>*    DijsktraList;


    bool solved;
    bool graphB;
public:
    /**
     * Constructor
     */
    Controller(){

        Prim = new PrimAlgorithm();
        LabyirintTemplate = new LabyrintToDraw();
        DijsktraList = new LinkedList<int>();
        solved = false;
        graphB = false;

    }

    void resetValues(){

        Prim->resetValues();
        Prim = new PrimAlgorithm();
        LabyirintTemplate->resetValues();
        LabyirintTemplate = new LabyrintToDraw();

    }

    /**
     * Recibe un comando de la interfaz y lo ejecuta
     * @param  comando [description]
     * @param  num     [description]
     * @return         [description]
     */
    bool ejecutar(string comando){

        if(comando != "Gen" && comando != "Sol" && comando != "Again" && comando != "Cargar" && comando != "Save"){

            return false;
        }
        if(comando == "Gen"){

            resetValues();
            solved = false;
            GrafoLaberinto = Prim->primLabyrint();
            LabyirintTemplate->graphToList(GrafoLaberinto);
            graphB = true;
            DrawClass::draw(LabyirintTemplate->getListShapes(),LabyirintTemplate->getListColor());
            DijsktraList->clear();
        }
        if(comando == "Sol"){
            if(!solved && graphB){

                DijsktraList = Dijsktra::DijkstraLabyrint(GrafoLaberinto,599);
                for(DijsktraList->goToStart();DijsktraList->getPos() < DijsktraList->getSize(); DijsktraList->next()){
                    GrafoLaberinto->setMark(DijsktraList->getElement(),true);
                }

                LabyirintTemplate->paintDijsktra(GrafoLaberinto->getMarkList(),GrafoLaberinto);
                DrawClass::draw(LabyirintTemplate->getListShapes(),LabyirintTemplate->getListColor());
                solved = true;
            }
            else{
                DrawClass::draw(LabyirintTemplate->getListShapes(),LabyirintTemplate->getListColor());
            }


        }
        if(comando == "Again"){

                DrawClass::draw(LabyirintTemplate->getListShapes(),LabyirintTemplate->getListColor());
        }

        return true;
    }

};
