#ifndef funkcja_include
#define funkcja_include
#include <allegro5/allegro.h>
#include <stdio.h>
#include <stdlib.h>

//#include <char>
using namespace std;

struct Szachownica;
struct Pionek;

struct Szachownica
{
    char przez;
    int x,y;
    ALLEGRO_BITMAP * kwadrat;
    Pionek * which_pawn;
    Szachownica * pg,* pd,* lg, *ld;
};
struct Pionek
{
    char kolor,type;
    bool available;
    Szachownica * Place;
    ALLEGRO_BITMAP * obrazek;
};
//float pozX,pozY;
void generuj_plansze(ALLEGRO_DISPLAY * &okno,Szachownica *** &a, Pionek ** &b);
void odswierz_plansze(ALLEGRO_DISPLAY * &okno,Szachownica *** &pole, Pionek ** &pawn, Pionek * );
void pozycjonuj(Szachownica *** &a);
void generuj_czarne_pionki(int,int,int);
void generuj_biale_pionki(int,int,int);
void usun_pionka(Pionek ** &,Pionek * );
bool ruch_zwyczajny(int beatseries,char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany);
int bicie_zwyczajne(int pozX, int pozY, char kolej, int beatseries,Szachownica *** &pole,Pionek ** &pawn, Pionek * &trzymany, Pionek * &bijacy);
bool czy_na_tym(int,int,int,Szachownica *** &pole, Pionek ** &pawn);
int na_tym(char,int,int,Szachownica *** &pole, Pionek ** &pawn);
bool ruch_damkowy(int beatseries,char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany);
bool ruch_damkowy_pg(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany, Szachownica * p);
bool ruch_damkowy_lg(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany, Szachownica * p);
bool ruch_damkowy_pd(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany, Szachownica * p);
bool ruch_damkowy_ld(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany, Szachownica * p);
int bicie_damkowe(int pozX, int pozY, char kolej, int beatseries,Szachownica *** &pole,Pionek ** &pawn, Pionek * &trzymany, Pionek * &bijacy);
bool bicie_damkowe_pg(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany,Szachownica * p,int number_of_enemy);
bool bicie_damkowe_lg(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany,Szachownica * p,int number_of_enemy);
bool bicie_damkowe_pd(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany,Szachownica * p,int number_of_enemy);
bool bicie_damkowe_ld(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany,Szachownica * p,int number_of_enemy);
Pionek * you_l1_dead_4_not_beat(Szachownica *** &pole, Pionek ** &pawn,char kolej);
bool czy_bicie_common(Szachownica *** &pole,Pionek * sprawdzany,char kolej);
bool czy_bicie_lady(Szachownica *** &pole, Szachownica  * to,char kolej);
void Interactiverozgrywka2people(char what);
void generuj_szachownice(ALLEGRO_DISPLAY * &okno,Szachownica *** &pole, Pionek ** &pawn);
bool czy_wygrana(Pionek ** &pawn,char kolej);
bool zamiana_w_damke(Pionek * &trzymany);
bool czy_bicie_damkowe_pd(Szachownica *** pole,Szachownica * to,char kolej);
bool czy_bicie_damkowe_pg(Szachownica *** pole,Szachownica * to,char kolej);
bool czy_bicie_damkowe_lg(Szachownica *** pole,Szachownica * to,char kolej);
bool czy_bicie_damkowe_ld(Szachownica *** pole,Szachownica * to,char kolej);
void clear_all(Szachownica *** &pole, Pionek ** pawn, ALLEGRO_DISPLAY * &okno, ALLEGRO_EVENT_QUEUE * &kolejka);
//void rozgrywka2people(ALLEGRO_DISPLAY * &okno);
void menu();
void Wczytaj_z_Pliku(ALLEGRO_DISPLAY *&okno, Szachownica *** &pole, Pionek ** &pawn,Pionek * &trzymany, Pionek * &bijacy, Pionek * &pretendent, char &kolej);


void rozgrywkaSinglePlayer(char who, char what);
void trzasnij(Pionek ** &pawn, Szachownica *** &pole,char kolej);
bool Computer_make_move(Szachownica *** &pole, Pionek ** &pawn, Pionek * &ruchliwy);
bool Komputerowe_bicie_lady(Szachownica *** &pole, Pionek ** &pawn, Szachownica * to,Pionek *&sprawdzany, char kolej);
bool Komputerowe_bicie_damkowe_pd(Szachownica *** &pole, Pionek ** &pawn,Szachownica * to,Pionek * &sprawdzany, char kolej);
bool Komputerowe_bicie_damkowe_lg(Szachownica *** &pole, Pionek ** &pawn,Szachownica * to,Pionek * &sprawdzany, char kolej);
bool Komputerowe_bicie_damkowe_pg(Szachownica *** &pole, Pionek ** &pawn,Szachownica * to,Pionek * &sprawdzany, char kolej);
bool Komputerowe_bicie_damkowe_ld(Szachownica *** &pole, Pionek ** &pawn, Szachownica * to, Pionek * &sprawdzany, char kolej);
bool Komputer_bicie_common(Szachownica *** &pole,Pionek ** &pawn,Pionek * &sprawdzany,char kolej);
#endif // funkcja_include
