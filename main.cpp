#include <iostream>
#include "stdio.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Controller.cpp"


using namespace std;

// Driver program to test above functions
int main(int argc, char* argv[])
{

    srand (time(NULL));


    bool play = true;
    int laberintoSeleccionado = 0;
    Controller* Controlador = new Controller();
    string comando = "";



    while(play)
    {
        play  = false;
        comando = "";
        laberintoSeleccionado = 0;


        cout << "\t\t#########################################\n";
        cout << "\t\t#########################################\n";
        cout << "\t\t##                                     ##\n";
        cout << "\t\t##             Laberintos              ##\n";
        cout << "\t\t##                                     ##\n";
        cout << "\t\t##   Este es un programa que genera    ##\n";
        cout << "\t\t##   laberintos. Ingrese \"Gen\"         ##\n";
        cout << "\t\t##   para generar su laberinto. Luego  ##\n";
        cout << "\t\t##   \"Sol\" para solucionarlo o \"Gen\"   ##\n";
        cout << "\t\t##   para generar uno nuevo. Ademas    ##\n";
        cout << "\t\t##   ingrese \"Again\" para mostrar      ##\n";
        cout << "\t\t##   el laberinto anterior mostrado    ##\n";
        cout << "\t\t##                                     ##\n";
        cout << "\t\t#########################################\n";
        cout << "\t\t#########################################\n";

        comando = "";
        cin >> comando ;

        play = Controlador->ejecutar(comando);

    }

    cout << "Programa Finalizado";

    return 0;

}

