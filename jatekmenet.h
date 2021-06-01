#ifndef jatekmenet.h
#define jatekmenet.h

// ebben a modulban talalhatoak a jatek allasahoz kotheto fuggvenyek

typedef struct Mezo{
    int korul;
    bool akna;
    bool fedett;
    bool zaszlo;
}Mezo;

typedef enum Kep{
    Zaszlo, Fedett, Akna,
    Egy, Ketto, Harom,
    Negy, Ot, Hat,
    Het, Nyolc, Ures
}Kep;

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);  // az ablakok megnyitásáért felel és a lehetseges SDL hibaüzenetek találhatoak benne
Mezo** palyamaker(Mezo **tabla, int y, int x, int aknadb);  // ezzel a függvennyel és a hozzatartozo megkapott magassag szelesseg es akna darab szamokkal lefoglal dinamikusan egy ket dimenziós tombot és veletlenszeruen aknakat helyez ra
void szabadit(Mezo **tabla, int y);  // felszabaditja a palyamaker altal lefoglalt ket dimenzios tombot
void ertekadas(int x, int y,int *meret,int *aknadb,int *mag, int *szel);  //  adott koordinatakkal a menuben megadhatoak a palya meretei es az aknak szama
void balklikk(Mezo **tabla, int y, int x, int magassag);  // ebben a fuggvenyben vannak a lepesek, a bal kattintassal fedhetoek fel az egyes mezok és ebben van a rekurzió, ha ures mezot szeretnenk felfedni
void jobbklikk(Mezo **tabla, int y, int x);  // a jobb kattintassal helyezhetok fel es vonhatak vissza a zaszlok
int ellenoriz(Mezo **tabla, int y, int x, int aknadb);  // ez a fuggveny vizsgalja meg minden mezo felfedes utan, hogy a jatekos nyert vagy vesztett-e

#endif // jatekmenet
