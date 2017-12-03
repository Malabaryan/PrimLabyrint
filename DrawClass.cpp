#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "PrimAlgorithm.cpp"
#include <SDL2/SDL.h>

using namespace std;

class DrawClass{

private:

  /**
    * Convert double Degrees to double Radians
    * @param degrees
    * @return double
    */
    static double toRadians(double degrees)
    {

        return (degrees * 3.141592 ) / 180;
    }

    /**
     * Draw a background
     * @param renderer
     */
    static void drawBackground(SDL_Renderer* renderer)
    {

        // Fondo: (renderizador, RED, GREEN , BLUE, ALPHA)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

    }



    /**
    * Recibe una lista de SDL_Rect y los pinta todos en pantalla
    * @param ListaInstrucciones List of instructions
    */
    static void drawAux(LinkedList<SDL_Rect>* ListShapes,LinkedList<SDL_Color>* ListColor)
    {

        if (SDL_Init(SDL_INIT_VIDEO) == 0)
        {
            SDL_Window* window = NULL;
            SDL_Renderer* renderer = NULL;

            if (SDL_CreateWindowAndRenderer(1000, 600, 0, &window, &renderer) == 0)
            {
                SDL_bool done = SDL_FALSE;

                while (!done)
                {
                    SDL_Event event;

                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);

                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                    ListColor -> goToStart();
                    SDL_Rect rect;
                    for(ListShapes->goToStart(); ListShapes->getPos() < ListShapes->getSize(); ListShapes->next())
                    {
                        SDL_SetRenderDrawColor( renderer,
                                                ListColor->getElement().r,
                                                ListColor->getElement().g,
                                                ListColor->getElement().b,
                                                SDL_ALPHA_OPAQUE);

                        rect = ListShapes->getElement();
                        SDL_RenderFillRect(renderer, &rect);
                        SDL_RenderDrawRect(renderer,&rect);
                        ListColor->next();

                    }

                    SDL_RenderPresent(renderer);

                    while (SDL_PollEvent(&event))
                    {
                        if (event.type == SDL_QUIT)
                        {
                            done = SDL_TRUE;
                        }
                        else if(event.type == SDL_KEYDOWN)
                        {

                            switch(event.type == SDL_KEYDOWN)
                            {

                            case SDLK_0:
                                done = SDL_TRUE;
                            default:
                                done = SDL_TRUE;

                            }
                        }
                    }
                }

            }

            if (renderer)
            {
                SDL_DestroyRenderer(renderer);
            }
            if (window)
            {
                SDL_DestroyWindow(window);
            }

        }

        SDL_Quit();


    }

public:


    static void draw(LinkedList<SDL_Rect>* ListShapes,LinkedList<SDL_Color>* ListColor){

        drawAux( ListShapes, ListColor);


    }

};
