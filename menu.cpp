#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "header.hpp"
#include<iostream>
#define rozmiar 75

void menu_odswierz(ALLEGRO_DISPLAY * okno, ALLEGRO_BITMAP * SinglePlayer,ALLEGRO_BITMAP * DoublePlayer,ALLEGRO_BITMAP * Exit)
{
    al_clear_to_color(al_map_rgb(0,150,0));
    al_set_target_bitmap(al_get_backbuffer(okno));
    al_draw_bitmap(SinglePlayer,150,100,0);
    al_draw_bitmap(DoublePlayer,150,190,0);
    al_draw_bitmap(Exit,150,275,0);
    al_flip_display();
}
void menu()
{
    al_init();
    al_install_mouse();
    al_install_keyboard();
    al_init_image_addon();
    ALLEGRO_MOUSE_STATE myszka;
    ALLEGRO_KEYBOARD_STATE klawiatura;
    //ALLEGRO_TIMER       *zegar;   // ( timer )
    ALLEGRO_EVENT_QUEUE *kolejka; // ( queue )
    bool odswiez = true;
    int klik=0;
    int poziom=1;
    bool out=false;
    //zegar   = al_create_timer(1.0 / 60);
    kolejka = al_create_event_queue();
    ALLEGRO_DISPLAY * okno = al_create_display(600,600);
    al_set_window_title(okno,"Warcaby");

    //ALLEGRO_BITMAP * Button1,* Button2,* Button3,* Button4, *Button5,* Button6;
    ALLEGRO_BITMAP * Button1 = al_load_bitmap("media/JedenGracz.png");
    ALLEGRO_BITMAP * Button2 = al_load_bitmap("media/2Graczy.png");
    ALLEGRO_BITMAP * Button3 = al_load_bitmap("media/exit.png");
    ALLEGRO_BITMAP * Button4 = al_load_bitmap("media/Nowa.png");
    ALLEGRO_BITMAP * Button5 = al_load_bitmap("media/Wczytaj.png");
    ALLEGRO_BITMAP * Button6 = al_load_bitmap("media/Back.png");

    menu_odswierz(okno,Button1,Button2,Button3);


    al_register_event_source( kolejka, al_get_mouse_event_source());
    al_register_event_source( kolejka, al_get_keyboard_event_source());
    //al_register_event_source( kolejka, al_get_display_event_source(okno));
    //al_register_event_source( kolejka, al_get_timer_event_source  (zegar));

    //al_start_timer(zegar);
    ALLEGRO_EVENT zdarzenie;
    while (1)
    {
        //cout<<"hh\n";
        if(out) break;
        al_get_mouse_state(&myszka);
        al_wait_for_event(kolejka, &zdarzenie);

        if (zdarzenie.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;
        if (zdarzenie.type == ALLEGRO_EVENT_KEY_UP) if (zdarzenie.keyboard.keycode == ALLEGRO_KEY_ESCAPE) break;
        if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) klik = zdarzenie.mouse.button;
        if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP  )
        {
            //if(myszka.x>=150 && myszka.x<=450 && myszka.y>=275 && myszka.y<=275+75) break;
            //klik = 0;
            switch(poziom)
            {
            case 1:
                if(myszka.x>=150 && myszka.x<=450 && myszka.y>=100 && myszka.y<=100+75) poziom=2;
                else if(myszka.x>=150 && myszka.x<=450 && myszka.y>=190 && myszka.y<=190+75) poziom=3;
                else if(myszka.x>=150 && myszka.x<=450 && myszka.y>=275 && myszka.y<=275+75) out=true;
                break;
            case 2:
                     if(myszka.x>=150 && myszka.x<=450 && myszka.y>=100 && myszka.y<=100+75)
                     {
                         okno=NULL;
                         rozgrywkaSinglePlayer('w','n');
                         odswiez=false;
                     }
                else if(myszka.x>=150 && myszka.x<=450 && myszka.y>=190 && myszka.y<=190+75)
                {
                    okno=NULL;
                    rozgrywkaSinglePlayer('w','l');
                    odswiez=false;
                }
                else if(myszka.x>=150 && myszka.x<=450 && myszka.y>=275 && myszka.y<=275+75) poziom=1;
                break;
            case 3:
                if(myszka.x>=150 && myszka.x<=450 && myszka.y>=100 && myszka.y<=100+75)
                {
                    okno=NULL;
                    /*al_destroy_bitmap(Button1);
                    al_destroy_bitmap(Button2);
                    al_destroy_bitmap(Button3);
                    al_destroy_bitmap(Button4);
                    al_destroy_bitmap(Button5);
                    al_destroy_bitmap(Button6);
                    al_destroy_event_queue(kolejka);
                    al_destroy_display(okno);*/
                    Interactiverozgrywka2people('n');
                    //rozgrywka2people(okno);
                    odswiez=false;
                }
                else if(myszka.x>=150 && myszka.x<=450 && myszka.y>=190 && myszka.y<=190+75)
                {
                    okno=NULL;
                    /*al_destroy_bitmap(Button1);
                    al_destroy_bitmap(Button2);
                    al_destroy_bitmap(Button3);
                    al_destroy_bitmap(Button4);
                    al_destroy_bitmap(Button5);
                    al_destroy_bitmap(Button6);
                    al_destroy_event_queue(kolejka);
                    al_destroy_display(okno);*/
                    Interactiverozgrywka2people('l');
                    //rozgrywka2people(okno);
                    odswiez=false;
                }
                else if(myszka.x>=150 && myszka.x<=450 && myszka.y>=275 && myszka.y<=275+75) poziom=1;
                break;
            default:
                break;

            }
        }
        if (odswiez)
        {
            switch(poziom)
            {
            case 1:
                menu_odswierz(okno,Button1,Button2,Button3);
                break;
            case 2:
                menu_odswierz(okno,Button4,Button5,Button6);
                break;
            case 3:
                menu_odswierz(okno,Button4,Button5,Button6);
                break;
            default:
                break;
            }
        }

    }

}
