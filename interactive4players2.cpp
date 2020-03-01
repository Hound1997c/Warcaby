#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "header.hpp"
#include<iostream>
#define rozmiar 75
#include <stdio.h>
#include <stdlib.h>


using namespace std;





void Interactiverozgrywka2people(char what)
{
    cout<<"zaczelo sie\n";
    al_init_image_addon();
    al_init();
    al_install_keyboard();
    al_install_mouse();
    ALLEGRO_KEYBOARD_STATE klawiatura;
    ALLEGRO_MOUSE_STATE myszka;
    //ALLEGRO_TIMER * zegar;
    ALLEGRO_DISPLAY * okno = NULL;
    ALLEGRO_EVENT_QUEUE * kolejka;
    cout<<"zaczelo sie\n";
    Szachownica *** pole;
    Pionek ** pawn;
    okno = NULL;
    bool odswiez = true;
    bool postep=false;
    bool koniecbicia=false;
    bool abilityToSave=true;
    float pozX,pozY;
    int ktory;
    int beatseries=0;
    char kolej;
    Pionek * trzymany = NULL;
    Pionek * bijacy = NULL;
    Pionek * pretendent = NULL;
    cout<<"zaczelo sie\n";
    if(what=='n')
    {
        generuj_plansze(okno,pole,pawn);
        postep=false;
        koniecbicia=false;
        beatseries=0;
        kolej='w';
    }
    else if(what=='l')
    {
        Wczytaj_z_Pliku(okno,pole,pawn,trzymany,bijacy,pretendent,kolej);
    }
     //odswierz_plansze(okno,pole,pawn,NULL);
    cout<<"poustawialo\n";



    int klik=0;
    //zegar   = al_create_timer(1.0 / 60); //czy_wygrana
    kolejka = al_create_event_queue();

    al_register_event_source( kolejka, al_get_mouse_event_source());
    al_register_event_source( kolejka, al_get_keyboard_event_source());
    al_register_event_source( kolejka, al_get_display_event_source(okno));
    //al_register_event_source( kolejka, al_get_timer_event_source  (zegar));
    //al_start_timer(zegar);
    ALLEGRO_EVENT zdarzenie;

    //pawn[14]->type='l';
    //pawn[14]->obrazek=al_load_bitmap("media/bialyDamka.png");
    cout<<"kolej "<<kolej<<endl;
    while (1)
    {
        al_get_mouse_state(&myszka);
        al_wait_for_event(kolejka, &zdarzenie);

        if (zdarzenie.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;
        if (zdarzenie.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (zdarzenie.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;
            if(zdarzenie.keyboard.keycode == ALLEGRO_KEY_ENTER && (postep==true || beatseries>0))
            {
                bijacy=NULL;
                if(kolej=='w') kolej='b';
                else kolej='w';
                postep=false;
                koniecbicia=false;
                beatseries=0;
            }
        }
        if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) klik = zdarzenie.mouse.button;
        if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP  )
        {
            if(klik &2 && (postep==true || beatseries>0))
            {
                bijacy=NULL;
                if(kolej=='w') kolej='b';
                else kolej='w';
                postep=false;
                koniecbicia=false;
                beatseries=0;
            }
            klik = 0;
        }

        if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_AXES       )
        {


            if(!trzymany) ktory=na_tym(kolej,myszka.x,myszka.y,pole,pawn);
            if(ktory!=-1 && klik &1 && !trzymany && !postep)
            {
                if(!bijacy || pawn[ktory]==bijacy)
                {
                    trzymany = pawn[ktory];
                    cout<<trzymany->type<<" "<<trzymany->kolor<<endl;
                    if(trzymany->type=='c' && czy_bicie_common(pole,trzymany,kolej)) {pretendent = trzymany;cout<<"bij\n";}
                    else if(trzymany->type=='l' && czy_bicie_lady(pole,trzymany->Place,kolej)) {pretendent=trzymany;cout<<"bij\n";}
                    pozX=trzymany->Place->x;
                    pozY=trzymany->Place->y;
                }
            }
            if(klik &1 && trzymany && myszka.x>=pozX && myszka.x<=pozX+rozmiar && myszka.y>=pozY && myszka.y<=pozY+rozmiar)
            {
                    pozX+=zdarzenie.mouse.dx;
                    pozY+=zdarzenie.mouse.dy;
            }
            if(klik==0 && trzymany)
            {
                Pionek * t = you_l1_dead_4_not_beat(pole,pawn,kolej);
                if(trzymany->type=='c') //is a common pawn
                {
                    if(!beatseries) postep=ruch_zwyczajny(beatseries,kolej,pozX,pozY,pole,pawn,trzymany);
                    if(!postep) beatseries=bicie_zwyczajne(pozX,pozY,kolej,beatseries,pole,pawn,trzymany,bijacy);
                    if(zamiana_w_damke(trzymany)) koniecbicia=true;
                }
                else if(trzymany->type=='l')
                {
                    if(!beatseries) postep=ruch_damkowy(beatseries,kolej,pozX,pozY,pole,pawn,trzymany);
                    if(!postep && !koniecbicia) beatseries=bicie_damkowe(pozX,pozY,kolej,beatseries,pole,pawn,trzymany,bijacy);
                }
                pozX=trzymany->Place->x; //cout<<"ok\n";
                pozY=trzymany->Place->y; //cout<<"ok\n";
                trzymany=NULL; //cout<<"trzymany=NULL;\n";

                if(postep && pretendent && !beatseries) usun_pionka(pawn,pretendent);
                else
                {
                    if(t && postep) usun_pionka(pawn,t);
                    t=NULL;
                    delete t;
                }
                pretendent=NULL;
            }
        }
        if (odswiez)
        {
            if(trzymany)
            {
                odswierz_plansze(okno,pole,pawn,trzymany);
                al_draw_bitmap (trzymany->obrazek, pozX, pozY, 0);
            }
            if(!trzymany) odswierz_plansze(okno,pole,pawn,NULL);
            if(abilityToSave=czy_wygrana(pawn,kolej)) break;
            al_flip_display();
        }
    }


    if(abilityToSave)
    {


        int button;
        if (kolej=='b') button=al_show_native_message_box(okno,"koniec gry","czarne wygraly","czy zaczac od nowa",NULL,ALLEGRO_MESSAGEBOX_YES_NO);
        else if(kolej=='w') button=al_show_native_message_box(okno,"koniec gry","biale wygraly","czy zaczac od nowa",NULL,ALLEGRO_MESSAGEBOX_YES_NO);
        clear_all(pole,pawn,okno,kolejka);
        if(button==1) Interactiverozgrywka2people('n');
    }
    else
    {

        if(postep || beatseries)
        {
            if(kolej=='b') kolej='w';
            else if(kolej=='w') kolej='b';
        }

        int button=al_show_native_message_box(okno,"Save","Zatrzymano","czy zapisac",NULL,ALLEGRO_MESSAGEBOX_YES_NO);
        if(button==1)
        {
            FILE * Zapis;
            Zapis=fopen("zapis2Players.txt","wt");
            fprintf(Zapis,"%c\n",kolej);
            for(int i=0; i<24; i++) if(pawn[i]) fprintf(Zapis,"%c %c %i %i\n",pawn[i]->kolor,pawn[i]->type,pawn[i]->Place->x/75,pawn[i]->Place->y/75);
                else fprintf(Zapis,"%c\n",'n');
            fclose(Zapis);
            clear_all(pole,pawn,okno,kolejka);
        }
        else clear_all(pole,pawn,okno,kolejka);
    }
    //printf("%c\n",kolej);



    //clear_all(pole,pawn,okno,kolejka);
}
