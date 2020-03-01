#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include<iostream>
#define rozmiar 75
#include "header.hpp"

//okno = NULL;


//struct Pionek;
//struct Szachownica;



using namespace std;





void odswierz_plansze(ALLEGRO_DISPLAY * &okno,Szachownica *** &pole, Pionek ** &pawn,Pionek * overed)
{
    //al_set_target_bitmap(al_get_backbuffer(okno));
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            al_set_target_bitmap(pole[i][j]->kwadrat);
            if((i+j)%2) al_clear_to_color(al_map_rgb(0,0,0));
            else al_clear_to_color(al_map_rgb(255,255,255));
        }

    al_set_target_bitmap(al_get_backbuffer(okno));
    for(int i=0;i<8;i++) for(int j=0;j<8;j++) if(pole[i][j]) al_draw_bitmap(pole[i][j]->kwadrat,pole[i][j]->x,pole[i][j]->y,0);
    for(int l=0;l<24;l++) if (pawn[l] && pawn[l] != overed) al_draw_bitmap(pawn[l]->obrazek,pawn[l]->Place->x,pawn[l]->Place->y,0);
    al_set_target_bitmap(al_get_backbuffer(okno));
}

void pozycjonuj(Szachownica *** &pole)
{
    //cout<<"pozycjonowanie!\n";
    for(int i=0;i<8;i++)
        for(int j=!(i%2);j<8;j+=2)
        {
            //cout<<i<<" "<<j<<endl;
            Szachownica * p;
            p=pole[i][j];
            if(p->x<525 && p->y>0)   p->pg=pole[i-1][j+1]; else p->pg=NULL;
            if(p->x<525 && p->y<525) p->pd=pole[i+1][j+1]; else p->pd=NULL;
            if(p->x>0   && p->y>0)   p->lg=pole[i-1][j-1]; else p->lg=NULL;
            if(p->x>0   && p->y<525) p->ld=pole[i+1][j-1]; else p->ld=NULL;
            pole[i][j]=p;
            p=NULL;
            delete p;
        }
}
void generuj_czarne_pionki(Szachownica *** &pole, Pionek ** &pawn,int l ,int i,int j)
{
            //cout<<"generowanie czarnych\n";
            //cout<<i<<" "<<j<<" ";
            pawn[l] = new Pionek;
            pawn[l]->type='c';
            pawn[l]->kolor='b';
            pawn[l]->available=true;
            pawn[l]->Place=pole[i][j];
            pawn[l]->obrazek=al_load_bitmap("media/czarny.png");
            pole[i][j]->which_pawn=pawn[l]; //cout<<"wspolrzedne "<<pawn[l]->Place->x<<" "<<pawn[l]->Place->y<<endl;
}
void generuj_biale_pionki(Szachownica *** &pole, Pionek ** &pawn,int l ,int i,int j)
{
            //cout<<"generowanie bialych\n";
            //cout<<i<<" "<<j<<" ";
            pawn[l] = new Pionek;
            pawn[l]->type='c';
            pawn[l]->kolor='w';
            pawn[l]->available=true;
            pawn[l]->Place=pole[i][j];
            pawn[l]->obrazek=al_load_bitmap("media/bialy.png");
            pole[i][j]->which_pawn=pawn[l]; //cout<<"wspolrzedne "<<pawn[l]->Place->x<<" "<<pawn[l]->Place->y<<endl;
}

void generuj_plansze(ALLEGRO_DISPLAY * &okno,Szachownica *** &pole, Pionek ** &pawn)
{

    al_set_new_display_flags(ALLEGRO_WINDOWED);
    okno=al_create_display(600,600);
    al_set_window_title(okno,"Warcaby");
    //al_clear_to_color(al_map_rgb(128,128,128));
    //ALLEGRO_BITMAP * button = al_load_bitmap("media/button.png");
    //al_draw_bitmap(button,625,230,0);



    //al_set_new_display_flags(ALLEGRO_WINDOWED|ALLEGRO_RESIZABLE);
    //al_set_target_bitmap(al_get_backbuffer(okno));

    pole = new Szachownica ** [8];
    for(int i=0;i<8;i++) pole[i] = new Szachownica * [8];
    for(int i=0;i<8;i++) for(int j=0;j<8;j++) pole[i][j]=NULL;

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            pole[i][j] = new Szachownica;
            Szachownica * p;
            p=pole[i][j];
            p->kwadrat=al_create_bitmap(rozmiar,rozmiar);
            p->x=j*75;
            p->y=i*75;
            p->pg=NULL;
            p->pd=NULL;
            p->lg=NULL;
            p->ld=NULL;
            p->which_pawn=NULL;
            pole[i][j]=p;
            p=NULL;
            delete p;
        }
    //for(int i=0;i<8;i++) for(int j=0;j<8;j++) cout<<pole[i][j]->x<<" "<<pole[i][j]->y<<endl;

    pawn = new Pionek * [24];
    for(int l=0;l<24;l++) pawn[l] = NULL;

    pozycjonuj(pole);

    //generuj_czarne_pionki(pole,pawn,0,0,1);
    //generuj_czarne_pionki(pole,pawn,1,1,0);
    for(int l=0,i=0;i<3;i++)  for(int j=!(i%2); j<8; j+=2,l++) generuj_czarne_pionki(pole,pawn,l,i,j);
    for(int l=12,i=5;i<8;i++) for(int j=!(i%2); j<8; j+=2,l++) generuj_biale_pionki(pole,pawn,l,i,j);

    //usun_czarne();
    odswierz_plansze(okno,pole,pawn,NULL);


    al_flip_display();
}


void generuj_szachownice(ALLEGRO_DISPLAY * &okno, Szachownica *** &pole, Pionek ** &pawn)
{
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    okno=al_create_display(600,600);
    al_set_window_title(okno,"Warcaby");


    pole = new Szachownica ** [8];
    for(int i=0;i<8;i++) pole[i] = new Szachownica * [8];
    for(int i=0;i<8;i++) for(int j=0;j<8;j++) pole[i][j]=NULL;

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            pole[i][j] = new Szachownica;
            Szachownica * p;
            p=pole[i][j];
            p->kwadrat=al_create_bitmap(rozmiar,rozmiar);
            p->x=j*75;
            p->y=i*75;
            p->pg=NULL;
            p->pd=NULL;
            p->lg=NULL;
            p->ld=NULL;
            p->which_pawn=NULL;
            pole[i][j]=p;
            p=NULL;
            delete p;
        }

    pawn = new Pionek * [24];
    for(int l=0;l<24;l++)
    {
        //pawn[l]=new Pionek;
        pawn[l] = NULL;
    }

    pozycjonuj(pole);
}
