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


void menurajzol(SDL_Renderer *renderer){

    boxRGBA(renderer, 0, 0, 220, 120, 96, 96, 96, 255);
    rectangleRGBA(renderer, 0, 0, 220, 120, 41, 41, 41, 255);

    rectangleRGBA(renderer, 0, 0, 220, 40, 41, 41, 41, 255);
    stringRGBA(renderer, 90, 15, "Easy", 255, 255, 255, 255);

    rectangleRGBA(renderer, 0, 40, 220, 80, 41, 41, 41, 255);
    stringRGBA(renderer, 85, 55, "Middle", 255, 255, 255, 255);

    rectangleRGBA(renderer, 0, 80, 220, 120, 41, 41, 41, 255);
    stringRGBA(renderer, 90, 95, "Hard", 255, 255, 255, 255);

    SDL_RenderPresent(renderer);

}

void kep_rajzol(SDL_Renderer *renderer, SDL_Texture *kepek, Kep melyik, int x, int y,int meret) {

    SDL_Rect src = { (melyik % 3) * 100, (melyik / 3) * 100, 100, 100};
    SDL_Rect dest = { x, y, meret, meret };
    SDL_RenderCopy(renderer, kepek, &src, &dest);
}

void palyarajzol(Mezo **tabla, SDL_Renderer *renderer, SDL_Texture *kepek, int x, int y, int meret){

    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){

            Kep melyik;
            if(tabla[i][j].fedett == true && tabla[i][j].zaszlo == false){

                melyik = Fedett;
            }

            else if(tabla[i][j].zaszlo == true){

                melyik = Zaszlo;
            }
            else{

                if(tabla[i][j].akna == false){

                    if(tabla[i][j].korul == 0){

                        melyik = Ures;
                    }
                    else if(tabla[i][j].korul == 1){

                        melyik = Egy;
                    }
                    else if(tabla[i][j].korul == 2){

                        melyik = Ketto;
                    }
                    else if(tabla[i][j].korul == 3){

                        melyik = Harom;
                    }
                    else if(tabla[i][j].korul == 4){

                        melyik = Negy;
                    }
                    else if(tabla[i][j].korul == 5){

                        melyik = Ot;
                    }
                    else if(tabla[i][j].korul == 6){

                        melyik = Hat;
                    }
                    else if(tabla[i][j].korul == 7){

                        melyik = Het;
                    }
                    else if(tabla[i][j].korul == 8){

                        melyik = Nyolc;
                    }
                }
                else if(tabla[i][j].akna == true){

                    melyik = Akna;
                }
            }
            kep_rajzol(renderer, kepek, melyik, j*meret + 10, i*meret + 10, meret);
            SDL_RenderPresent(renderer);
        }
    }
}

void nyertel(SDL_Renderer *renderer, int x, int ido){

    boxRGBA(renderer, 10, 10, 210, 110, 96, 96, 96, 255);
    rectangleRGBA(renderer, 10, 10, 220, 110, 41, 41, 41, 255);
    stringRGBA(renderer, 85, 20, "YOU WON", 255, 255, 255, 255);

    FILE *rekord;
    int tomb[3]={0};

    if(x == 5){
        rekord = fopen("easyrekord.txt", "r");
    }

    else if(x == 10){
        rekord = fopen("middlerekord.txt", "r");
    }

    else if(x == 20){
        rekord = fopen("hardrekord.txt", "r");
    }


    for (int i=0; i<3; i++){
        fscanf(rekord, "%d\n", &tomb[i]);
        }

    fclose(rekord);

     if(x == 5){
        rekord = fopen("easyrekord.txt", "w");
    }

    else if(x == 10){
        rekord = fopen("middlerekord.txt", "w");
    }

    else if(x == 20){
        rekord = fopen("hardrekord.txt", "w");
    }

    for (int i=0; i<3; i++){
        if(tomb[i] == 0){
                tomb[i] = ido;
                break;
        }

        if (tomb[i]>ido){

            for(int j = 2; j > i; j--){
                tomb[j]=tomb[j-1];
            }
            tomb[i]=ido;
            break;
        }
    }

    for (int i=0; i<3; i++){
        fprintf(rekord, "%d\n",tomb[i]);
    }

    fclose(rekord);

    char sajat[10];
    itoa(ido, sajat, 10);

    char top1[10];
    itoa(tomb[0], top1, 10);

    char top2[10];
    itoa(tomb[1], top2, 10);

    char top3[10];
    itoa(tomb[2], top3, 10);

    stringRGBA(renderer, 40, 40, "YOURS:", 255, 255, 255, 255);
    stringRGBA(renderer, 100, 40, sajat, 255, 255, 255, 255);

    stringRGBA(renderer, 40, 60, "TOP1:", 255, 255, 255, 255);
    stringRGBA(renderer, 80, 60, top1, 255, 255, 255, 255);

    stringRGBA(renderer, 40, 70, "TOP2:", 255, 255, 255, 255);
    stringRGBA(renderer, 80, 70, top2, 255, 255, 255, 255);

    stringRGBA(renderer, 40, 80, "TOP3:", 255, 255, 255, 255);
    stringRGBA(renderer, 80, 80, top3, 255, 255, 255, 255);

    SDL_RenderPresent(renderer);

    fclose(rekord);
}

void vesztettel(SDL_Renderer *renderer, int x){

    boxRGBA(renderer, 10, 10, 210, 110, 96, 96, 96, 255);
    rectangleRGBA(renderer, 10, 10, 220, 110, 41, 41, 41, 255);
    stringRGBA(renderer, 95, 40, "DURR", 255, 255, 255, 255);

    SDL_RenderPresent(renderer);

    FILE *rekord;
    int tomb[3]={0};

    if(x == 5){
        rekord = fopen("easyrekord.txt", "r");
    }

    else if(x == 10){
        rekord = fopen("middlerekord.txt", "r");
    }

    else if(x == 20){
        rekord = fopen("hardrekord.txt", "r");
    }


    for (int i=0; i<3; i++){
        fscanf(rekord, "%d\n", &tomb[i]);
        }

    fclose(rekord);


    char top1[10];
    itoa(tomb[0], top1, 10);

    char top2[10];
    itoa(tomb[1], top2, 10);

    char top3[10];
    itoa(tomb[2], top3, 10);


    stringRGBA(renderer, 40, 60, "TOP1:", 255, 255, 255, 255);
    stringRGBA(renderer, 80, 60, top1, 255, 255, 255, 255);

    stringRGBA(renderer, 40, 70, "TOP2:", 255, 255, 255, 255);
    stringRGBA(renderer, 80, 70, top2, 255, 255, 255, 255);

    stringRGBA(renderer, 40, 80, "TOP3:", 255, 255, 255, 255);
    stringRGBA(renderer, 80, 80, top3, 255, 255, 255, 255);

    SDL_RenderPresent(renderer);
}

