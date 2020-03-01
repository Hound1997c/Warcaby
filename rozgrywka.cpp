#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "header.hpp"
#include<iostream>
#define rozmiar 75


using namespace std;

bool czy_wygrana(Pionek ** &pawn,string kolej)
{
    if(kolej=="white")
    {
        for(int i=0;i<12;i++) if(pawn[i]) return false;
        cout<<"Whites Win!\n";
        return true;
    }
    else if(kolej=="black")
    {
        for(int i=12;i<24;i++) if(pawn[i]) return false;
        cout<<"Blackes Win!\n";
        return true;
    }
}
bool czy_bicie_lady(Szachownica *** &pole, Pionek * sprawdzany,string kolej)
{
    Szachownica * p;
    for(p=sprawdzany->Place;p->pg;p=p->pg)
    {
            if(p->pg->which_pawn && p->pg->which_pawn->kolor==kolej)
            {
                p=sprawdzany->Place;
                break;
            }
            else if(p->pg->which_pawn && p->pg->which_pawn->kolor!=kolej && p->pg->pg && !p->pg->pg->which_pawn) return true;
    }
    for(p=sprawdzany->Place;p->lg;p=p->lg)
    {
            if(p->which_pawn && p->which_pawn->kolor==kolej)
            {
                p=sprawdzany->Place;
                break;
            }
            else if(p->which_pawn && p->which_pawn->kolor!=kolej && p->lg && !p->lg->which_pawn) return true;
    }
    for(p=sprawdzany->Place;p->pd;p=p->pd)
    {
            if(p->which_pawn && p->which_pawn->kolor==kolej)
            {
                p=sprawdzany->Place;
                break;
            }
            else if(p->which_pawn && p->which_pawn->kolor!=kolej && p->pd && !p->pd->which_pawn) return true;
    }
    for(p=sprawdzany->Place;p->ld;p=p->ld)
    {
            if(p->which_pawn && p->which_pawn->kolor==kolej)
            {
                p=sprawdzany->Place;
                break;
            }
            else if(p->which_pawn && p->which_pawn->kolor!=kolej && p->ld && !p->ld->which_pawn) return true;
    }
    return false;
}
bool czy_bicie_common(Szachownica *** &pole,Pionek * sprawdzany,string kolej)
{
    if(sprawdzany->Place->pg && sprawdzany->Place->pg->pg && sprawdzany->Place->pg->which_pawn && sprawdzany->Place->pg->which_pawn->kolor!=kolej && !sprawdzany->Place->pg->pg->which_pawn) return true;
    else if(sprawdzany->Place->lg && sprawdzany->Place->lg->lg && sprawdzany->Place->lg->which_pawn && sprawdzany->Place->lg->which_pawn->kolor!=kolej && !sprawdzany->Place->lg->lg->which_pawn) return true;
    else if(sprawdzany->Place->pd && sprawdzany->Place->pd->pd && sprawdzany->Place->pd->which_pawn && sprawdzany->Place->pd->which_pawn->kolor!=kolej && !sprawdzany->Place->pd->pd->which_pawn) return true;
    else if(sprawdzany->Place->ld && sprawdzany->Place->ld->ld && sprawdzany->Place->ld->which_pawn && sprawdzany->Place->ld->which_pawn->kolor!=kolej && !sprawdzany->Place->ld->ld->which_pawn) return true;
    return false;
}
Pionek * you_l1_dead_4_not_beat(Szachownica *** &pole, Pionek ** &pawn,string kolej)
{
    int bicia=0;
    if(kolej=="black")
    {
        for(int i=0;i<12;i++)
            if(pawn[i] && pawn[i]->type=="common" && czy_bicie_common(pole,pawn[i],kolej)) return pawn[i];
            else if(pawn[i] && pawn[i]->type=="lady" && czy_bicie_lady(pole,pawn[i],kolej)) return pawn[i];
        return NULL;
    }
    else if(kolej=="white")
    {
        for(int i=12;i<24;i++)
            if(pawn[i] && pawn[i]->type=="common" && czy_bicie_common(pole,pawn[i],kolej)) return pawn[i];
            else if(pawn[i] && pawn[i]->type=="lady" && czy_bicie_lady(pole,pawn[i],kolej)) return pawn[i];
        return NULL;
    }
}


void rozgrywka()
{
    al_init_image_addon();
    al_init();
    al_install_keyboard();
    al_install_mouse();

    Szachownica *** pole;
    Pionek ** pawn;
    ALLEGRO_DISPLAY * okno = NULL;
    generuj_plansze(okno,pole,pawn);

    ALLEGRO_KEYBOARD_STATE klawiatura;
    ALLEGRO_MOUSE_STATE myszka;
    ALLEGRO_TIMER * zegar;
    ALLEGRO_EVENT_QUEUE * kolejka;
    bool odswiez = true;
    bool postep=false;
    bool koniecbicia=false;
    float pozX,pozY;
    int ktory;
    int beatseries=0;
    string kolej="white";
    Pionek * trzymany = NULL;
    Pionek * bijacy = NULL;
    Pionek * pretendent = NULL;
    int klik=0;
    zegar   = al_create_timer(1.0 / 60);
    kolejka = al_create_event_queue();

    al_register_event_source( kolejka, al_get_mouse_event_source());
    al_register_event_source( kolejka, al_get_keyboard_event_source());
    al_register_event_source( kolejka, al_get_display_event_source(okno));
    al_register_event_source( kolejka, al_get_timer_event_source  (zegar));
    al_start_timer(zegar);
    ALLEGRO_EVENT zdarzenie;

    pawn[14]->type="lady";
    pawn[14]->obrazek=al_load_bitmap("media/bialyDamka.png");

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
                if(kolej=="white") kolej="black";
                else kolej="white";
                postep=false;
                koniecbicia=false;
                beatseries=0;
            }
        }
        if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) klik = zdarzenie.mouse.button;
        if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP  ) klik = 0;
        if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_AXES       )
        {

            if(!trzymany) ktory=na_tym(kolej,myszka.x,myszka.y,pole,pawn);
            if(ktory!=-1 && klik &1 && !trzymany && !postep)
            {
                if(!bijacy || pawn[ktory]==bijacy)
                {
                    trzymany = pawn[ktory];
                    cout<<trzymany->type<<endl;
                    if(trzymany->type=="common" && czy_bicie_common(pole,trzymany,kolej)) {pretendent = trzymany;cout<<"bij\n";}
                    else if(trzymany->type=="lady" && czy_bicie_lady(pole,trzymany,kolej)) {pretendent=trzymany;cout<<"bij\n";}
                    pozX=trzymany->Place->x;
                    pozY=trzymany->Place->y;
                }

            }
            if(klik &1 && trzymany && myszka.x>=pozX && myszka.x<=pozX+rozmiar && myszka.y>=pozY && myszka.y<=pozY+rozmiar)
            {
                    pozX+=zdarzenie.mouse.dx;
                    pozY+=zdarzenie.mouse.dy;
                    //cout<<zdarzenie.mouse.dx<<" "<<zdarzenie.mouse.dy<<endl;
            }
            if(klik==0 && trzymany)
            {

                Pionek * t = you_l1_dead_4_not_beat(pole,pawn,kolej);
                if(trzymany->type=="common") //is a common pawn
                {
                    if(!beatseries) postep=ruch_zwyczajny(beatseries,kolej,pozX,pozY,pole,pawn,trzymany);
                    if(!postep) beatseries=bicie_zwyczajne(pozX,pozY,kolej,beatseries,pole,pawn,trzymany,bijacy);
                    if(zamiana_w_damke(trzymany)) koniecbicia=true;
                }
                else if(trzymany->type=="lady")
                {
                    if(!beatseries) postep=ruch_damkowy(beatseries,kolej,pozX,pozY,pole,pawn,trzymany);
                    if(!postep && !koniecbicia) beatseries=bicie_damkowe(pozX,pozY,kolej,beatseries,pole,pawn,trzymany,bijacy);
                        //bicie_zwyczajne(pozX,pozY,kolej,beatseries,pole,pawn,trzymany,bijacy);
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

            if(!trzymany)
            {
                //cout<<"ni trzymam\n";
                //if(bijacy) zamiana_w_damke(bijacy);
                odswierz_plansze(okno,pole,pawn,NULL);
                //cout<<"odswierzylem\n";
            }
            czy_wygrana(pawn,kolej);
            al_flip_display();
        }

        //if (zdarzenie.type == ALLEGRO_EVENT_TIMER) odswiez = true;
        //else odswiez = false;
    }



    //while(!al_key_down(&klawiatura,ALLEGRO_KEY_ESCAPE)) al_get_keyboard_state(&klawiatura);

}
/**/


                /*else if(trzymany->type=="lady")
                {
                    ;
                }*/
