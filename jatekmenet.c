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

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

Mezo** palyamaker(Mezo **tabla, int y, int x, int aknadb){

    if(tabla == NULL){

        tabla = (Mezo **)malloc(y * sizeof(Mezo *));
        for (int i=0; i<x; i++){
            tabla[i] = (Mezo *)malloc(x * sizeof(Mezo));
        }

        for(int j = 0; j < y; j++){

            for(int i = 0; i < x; i++){

                tabla[j][i].korul = 0;
                tabla[j][i].akna = false;
                tabla[j][i].fedett = true;
                tabla[j][i].zaszlo = false;

            }
        }
    }

    for(int j = 0 ; j < aknadb; j++){
        int tomb[2];

        for (int i = 0; i < 2; ++i){

            tomb[i] = rand()%x;
        }

        if(tabla[tomb[0]][tomb[1]].akna == true){

            j--;
        }
        else{

            tabla[tomb[0]][tomb[1]].akna = true;
            if(tomb[0]>0){tabla[tomb[0]-1][tomb[1]].korul ++;}
            if(tomb[1]>0){tabla[tomb[0]][tomb[1]-1].korul ++;}

            if(tomb[0]<x-1){tabla[tomb[0]+1][tomb[1]].korul ++;}
            if(tomb[1]<x-1){tabla[tomb[0]][tomb[1]+1].korul ++;}

            if(tomb[1]>0 && tomb[0]>0){tabla[tomb[0]-1][tomb[1]-1].korul ++;}
            if(tomb[1]<x-1 && tomb[0]<x-1){tabla[tomb[0]+1][tomb[1]+1].korul ++;}

            if(tomb[1]>0 && tomb[0]<x-1){tabla[tomb[0]+1][tomb[1]-1].korul ++;}
            if(tomb[1]<x-1 && tomb[0]>0){tabla[tomb[0]-1][tomb[1]+1].korul ++;}

        }
    }

    return tabla;
}

void szabadit(Mezo **tabla, int y){

    if(tabla != NULL){

        for(int i = 0; i < y; i++){
            free(tabla[i]);
        }

        free(tabla);
    }
}

void ertekadas(int x, int y,int *meret,int *aknadb,int *mag, int *szel){
    if(x>0 && x<220 && y>0 && y<40){
        *meret = 100;
        *aknadb = 4;
    }
    else if(x>0 && x<220 && y>40 && y<80){
        *meret = 50;
        *aknadb = 10;
    }
    else if(x>0 && x<220 && y>80 && y<120){
        *meret = 25;
        *aknadb = 25;
    }

    *szel = 500/(*meret);
    *mag = *szel;



}

void balklikk(Mezo **tabla, int y, int x, int magassag){

        if (y < 0 || x < 0 || y > magassag-1 || x > magassag-1){
            return;  // a palya meretein belul marad a rekurzio
        }

        if(tabla[y][x].fedett == false){

            return;  // a felforditott mezoket kezeli le
        }

        if(tabla[y][x].zaszlo == true){

            return;  //a zaszlos mezoket nem fedi fel
        }


        tabla[y][x].fedett = false;  //felfedi az adott mezot


        if((tabla[y][x].korul != 0 || tabla[y][x].akna == true) || tabla[y][x].zaszlo == true){

            return;  // ha a mezo korul van akna,
        }

        else{
            balklikk(tabla, y - 1, x, magassag);      //é
            balklikk(tabla, y - 1, x - 1, magassag);  //ény
            balklikk(tabla, y, x - 1, magassag);      //ny
            balklikk(tabla, y + 1, x - 1, magassag);  //dny
            balklikk(tabla, y + 1, x, magassag);      //d
            balklikk(tabla, y + 1, x + 1, magassag);  //dk
            balklikk(tabla, y, x + 1, magassag);      //k
            balklikk(tabla, y - 1, x + 1, magassag);  //ék
        }
}

void jobbklikk(Mezo **tabla, int y, int x){

    if(tabla[y][x].zaszlo == true){

        tabla[y][x].zaszlo = false;  // ha a mezon eddig zaszlo volt, akkor leveszi rola
    }

    else if(tabla[y][x].zaszlo == false && tabla[y][x].fedett == true){

        tabla[y][x].zaszlo = true;  // lehelyez egy zaszlot, ha eredetileg nem volt rajta es fedett a mezo
    }

}

int ellenoriz(Mezo **tabla, int y, int x, int aknadb){

    int jo = 0;  // azokat a mezoket szamolja, amik aknak, de jol le van rajtuk helyezve a zaszlo
    int felfedett = 0;  // a jol felfedett mezoket szamolja

    for(int i = 0; i < y; i++){

        for(int j = 0; j < x; j++){

            if(tabla[i][j].zaszlo == true && tabla[i][j].akna == true){

                jo++;
            }

            else if(tabla[i][j].fedett == false){

                felfedett++;
            }

            if(tabla[i][j].akna == true && tabla[i][j].fedett == false){
                return 1;   //eggyel tér vissza, ha a játékos veszít
            }
        }
    }

    if(jo == aknadb && felfedett == (x*y)-aknadb){

        return 2; //2-vel tér vissza, ha a játékos nyer
    }

    return 0;  // ha ezzel tér vissza, folytatódik a játék

}
