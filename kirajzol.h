#ifndef kirajzol.h
#define kirajzol.h
#include "jatekmenet.h"

void menurajzol(SDL_Renderer *renderer);  // az elso elougro ablaknal kirajzolja a lehetosegeket, vagyis a harom modot
void kep_rajzol(SDL_Renderer *renderer, SDL_Texture *kepek, Kep melyik, int x, int y,int meret);  // a mezokhoz tartozo enumok kirajzolasahoz egy seged fuggveny, ami a palyarajzol() fuggveny mukodeset konnyiti meg
void palyarajzol(Mezo **tabla, SDL_Renderer *renderer, SDL_Texture *kepek, int x, int y, int meret);  //a masodik ablak kinezeteert felel, minden kattintasnal jkirajzolja az aktualis palyat
void nyertel(SDL_Renderer *renderer, int x, int ido);  // ha a jatekos nyer, a harmadik ablakon ezek a kiirasok jelennek meg. Itt torenik a filekezeles is
void vesztettel(SDL_Renderer *renderer, int x);  //ha a jatekos veszit, akkor ez jelenik meg a harmadik elougro ablakon ablakon

#endif // kirajzol
