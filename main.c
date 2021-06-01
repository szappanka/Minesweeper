#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "kirajzol.h"
#include "jatekmenet.h"
#include "debugmalloc.h"
#include "ablakok.h"

int main(int argc, char *argv[]) {

    int szel, mag, meret, aknadb = 0;  // a palya adatai lesznek, egy fuggvenyben veszik fel az értékeit
    int allas = 0;  // a jatek allasat jelzi,
    Mezo **palya = NULL;  // ez lesz a ket dimenzios tomb, amiben az adott palya adatai vannak
    time_t kezd, vegez;  // ez a jatekido szamitasahoz kell
    bool jatszik = true; // false lesz, ha bezarjak az adott ablakot, ilyenkor nem nyilik meg tobb ablak
    bool quit1 = false;  // az egyes ablakok bezarasat jelzi
    bool quit2 = false;
    bool quit3 = false;

    srand(time(0));

    SDL_Window *window;
    SDL_Renderer *renderer;

    //elsö ablak

    sdl_init("Menü", 220, 120, &window, &renderer);
    SDL_RenderPresent(renderer);

    menurajzol(renderer);

    while (!quit1) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type) {

            case SDL_MOUSEBUTTONUP:

                if(event.button.button == SDL_BUTTON_LEFT){

                    ertekadas(event.button.x, event.button.y, &meret, &aknadb, &mag, &szel);  //a palya meretei megkapjak az ertekeiket attol fuggoen, hogy melyik modot valastottak
                    palya = palyamaker(palya, mag, szel, aknadb);  // generalja a palyat, veletlenszeuen aknakat helyez ra

                    for(int i = 0; i < szel; i++){
                        for(int j = 0; j < mag; j++){
                            if(palya[i][j].akna == true){
                                printf("*");
                            }
                            else{
                                printf("o");
                            }
                        }
                        printf("\n");
                    }


                    quit1 = true;

                    break;
                }

            case SDL_QUIT:

                szabadit(palya, mag);
                jatszik = false;
                quit1 = true;

                break;
        }
    }

    SDL_Quit();

    if(quit1 == true && jatszik == true){

        sdl_init("Aknakereső", 520, 520, &window, &renderer);

        SDL_Texture *kepek = IMG_LoadTexture(renderer, "kepek.png");

        palyarajzol(palya, renderer, kepek, szel, mag, meret);

        SDL_RenderPresent(renderer);

        kezd = time(NULL);

        while (!quit2) {
            SDL_Event event;
            SDL_WaitEvent(&event);

            switch (event.type) {

                case SDL_MOUSEBUTTONDOWN:

                    if(event.button.button == SDL_BUTTON_LEFT){

                    int x, y;

                       if(event.button.x>10 && event.button.y>10){
                            x = (event.button.x-10)/meret;
                            y = (event.button.y-10)/meret;
                       }

                        balklikk(palya, y, x, mag);
                        palyarajzol(palya, renderer, kepek, szel, mag, meret);

                        allas = ellenoriz(palya, mag, szel, aknadb);

                        if(allas == 1 || allas == 2){  // ha a jatekos nyer vagy veszit felszabaditja a palyat a kepek texturet es bezarja az ablakot
                            szabadit(palya, mag);
                            quit2 = true;
                            vegez = time(NULL);
                            SDL_DestroyTexture(kepek);
                        }

                        break;
                    }

                    if (event.button.button == SDL_BUTTON_RIGHT){

                        int x = (event.button.x-10)/meret;
                        int y = (event.button.y-10)/meret;

                        jobbklikk(palya, y, x);
                        palyarajzol(palya, renderer, kepek, szel, mag, meret);

                        allas = ellenoriz(palya, mag, szel, aknadb);

                        if(allas == 1 || allas == 2){  // ha a jatekos nyer vagy veszit felszabaditja a palyat a kepek texturet es bezarja az ablakot
                            szabadit(palya, mag);
                            quit2 = true;
                            vegez = time(NULL);
                            SDL_DestroyTexture(kepek);
                        }

                        break;
                    }

                case SDL_QUIT:

                    szabadit(palya, mag);
                    SDL_DestroyTexture(kepek);
                    jatszik = false;
                    quit2 = true;

                    break;
            }
        }
    }

    SDL_RenderPresent(renderer);
    SDL_Quit();

    harmadik(renderer, window, &quit3, &quit2, &mag, &jatszik, &kezd, &vegez, &allas);

    return 0;

}
