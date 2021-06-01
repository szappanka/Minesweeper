#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include "kirajzol.h"
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "ablakok.h"

void harmadik(SDL_Renderer *renderer, SDL_Window *window, bool *quit3, bool *quit2, int *mag, bool *jatszik,time_t *kezd, time_t *vegez, int *allas){
    if(*quit2 == true && *jatszik == true){
        sdl_init("Aknakereső", 220, 120, &window, &renderer);

        if(*allas == 1){

            vesztettel(renderer, *mag);
        }

        if(*allas == 2){

            nyertel(renderer, *mag, *vegez - *kezd);
        }

        while (!*quit3) {
        SDL_Event event;
        SDL_WaitEvent(&event);

            switch (event.type) {

                case SDL_QUIT:

                    *quit3 = true;
                    break;
            }
        }
    }

    SDL_Quit();


}



