#include "header.hpp"
#define rozmiar 75
#include<iostream>

using namespace std;

void usun_pionka(Pionek ** &pawn,Pionek * tego)
{
    for(int i=0;i<24;i++)
        if(tego==pawn[i])
        {
            pawn[i]->Place->which_pawn=NULL;
            pawn[i]->Place=NULL;
            pawn[i]=NULL;
            //al_destroy_bitmap(pawn[i]->obrazek);
            delete pawn[i];
        }
}

bool czy_na_tym(int i,int mx,int my, Szachownica *** &pole, Pionek ** &pawn)
{
    float x=pawn[i]->Place->x;
    float y=pawn[i]->Place->y;
    if(mx>=x && mx<=x+rozmiar && my>=y && my<=y+rozmiar) return true;
    return false;
}

int bicie_zwyczajne(int pozX, int pozY, char kolej, int beatseries,Szachownica *** &pole,Pionek ** &pawn, Pionek * &trzymany, Pionek * &bijacy)
{
    if(trzymany->kolor==kolej)
    {
        if(trzymany->Place->pg && trzymany->Place->pg->which_pawn!=NULL && trzymany->Place->pg->which_pawn->kolor!=kolej &&trzymany->Place->pg->pg && trzymany->Place->pg->pg->which_pawn==NULL && pozX+10>=trzymany->Place->pg->pg->x && pozX-10<=trzymany->Place->pg->pg->x+rozmiar && pozY+10>=trzymany->Place->pg->pg->y && pozY+10<=trzymany->Place->pg->pg->y+rozmiar)
        {
            bijacy=trzymany;
            usun_pionka(pawn,trzymany->Place->pg->which_pawn);
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=trzymany->Place->pg->pg;
            trzymany->Place->which_pawn=trzymany;
            beatseries++;
        }
        else if(trzymany->Place->lg && trzymany->Place->lg->which_pawn!=NULL && trzymany->Place->lg->which_pawn->kolor!=kolej &&trzymany->Place->lg->lg && trzymany->Place->lg->lg->which_pawn==NULL && pozX+10>=trzymany->Place->lg->lg->x && pozX-10<=trzymany->Place->lg->lg->x+rozmiar && pozY+10>=trzymany->Place->lg->lg->y && pozY+10<=trzymany->Place->lg->lg->y+rozmiar)
        {
            bijacy=trzymany;
            usun_pionka(pawn,trzymany->Place->lg->which_pawn);
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=trzymany->Place->lg->lg;
            trzymany->Place->which_pawn=trzymany;
            beatseries++;
        }
        else if(trzymany->Place->pd && trzymany->Place->pd->which_pawn!=NULL && trzymany->Place->pd->which_pawn->kolor!=kolej &&trzymany->Place->pd->pd && trzymany->Place->pd->pd->which_pawn==NULL && pozX+10>=trzymany->Place->pd->pd->x && pozX-10<=trzymany->Place->pd->pd->x+rozmiar && pozY+10>=trzymany->Place->pd->pd->y && pozY+10<=trzymany->Place->pd->pd->y+rozmiar)
        {
            bijacy=trzymany;
            usun_pionka(pawn,trzymany->Place->pd->which_pawn);
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=trzymany->Place->pd->pd;
            trzymany->Place->which_pawn=trzymany;
            beatseries++;
        }
        else if(trzymany->Place->ld && trzymany->Place->ld->which_pawn!=NULL && trzymany->Place->ld->which_pawn->kolor!=kolej &&trzymany->Place->ld->ld && trzymany->Place->ld->ld->which_pawn==NULL && pozX+10>=trzymany->Place->ld->ld->x && pozX-10<=trzymany->Place->ld->ld->x+rozmiar && pozY+10>=trzymany->Place->ld->ld->y && pozY+10<=trzymany->Place->ld->ld->y+rozmiar)
        {
            bijacy=trzymany;
            usun_pionka(pawn,trzymany->Place->ld->which_pawn);
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=trzymany->Place->ld->ld;
            trzymany->Place->which_pawn=trzymany;
            beatseries++;
        }
    }
    return beatseries;
}

bool ruch_zwyczajny(int beatseries,char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany)
{
    if(kolej=='w')
    {
        if(trzymany->kolor==kolej && trzymany->Place->pg && trzymany->Place->pg->which_pawn==NULL && pozX+10>=trzymany->Place->pg->x && pozX-10<=trzymany->Place->pg->x+rozmiar && pozY+10>=trzymany->Place->pg->y && pozY+10<=trzymany->Place->pg->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=trzymany->Place->pg;
            trzymany->Place->which_pawn=trzymany;
            return true;
        }
        else if(trzymany->kolor==kolej && trzymany->Place->lg && trzymany->Place->lg->which_pawn == NULL && pozX+10>=trzymany->Place->lg->x && pozX-10<=trzymany->Place->lg->x+rozmiar && pozY+10>=trzymany->Place->lg->y && pozY+10<=trzymany->Place->lg->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=trzymany->Place->lg;
            trzymany->Place->which_pawn=trzymany;
            return true;
        }
        return false;
    }
    else if(kolej=='b')
    {
        if(trzymany->kolor==kolej && trzymany->Place->pd && trzymany->Place->pd->which_pawn == NULL && pozX+10>=trzymany->Place->pd->x && pozX-10<=trzymany->Place->pd->x+rozmiar && pozY+10>=trzymany->Place->pd->y && pozY+10<=trzymany->Place->pd->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=trzymany->Place->pd;
            trzymany->Place->which_pawn=trzymany;
            return true;
        }
        else if(trzymany->kolor==kolej && trzymany->Place->ld && trzymany->Place->ld->which_pawn == NULL && pozX+10>=trzymany->Place->ld->x && pozX-10<=trzymany->Place->ld->x+rozmiar && pozY+10>=trzymany->Place->ld->y && pozY+10<=trzymany->Place->ld->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=trzymany->Place->ld;
            trzymany->Place->which_pawn=trzymany;
            return true;
        }
        return false;
    }
}

int na_tym(char kolor,int mx,int my,Szachownica *** &pole, Pionek ** &pawn)
{
    if(kolor=='b')
    {
        for(int i=0;i<12;i++) if(pawn[i] && mx>=pawn[i]->Place->x && mx<=pawn[i]->Place->x+rozmiar && my>=pawn[i]->Place->y && my<=pawn[i]->Place->y+rozmiar) return i;
        return -1;
    }
    else if(kolor=='w')
    {
        for(int i=12;i<24;i++) if(pawn[i] && mx>=pawn[i]->Place->x && mx<=pawn[i]->Place->x+rozmiar && my>=pawn[i]->Place->y && my<=pawn[i]->Place->y+rozmiar) return i;
        return -1;
    }
}

bool zamiana_w_damke(Pionek * &trzymany)
{
    if(trzymany->kolor=='w' && trzymany->Place->y<75)
    {
        trzymany->obrazek=al_load_bitmap("media/bialyDamka.png");
        trzymany->type='l';
        return true;
    }
    else if(trzymany->kolor=='b' && trzymany->Place->y>=525)
    {
        trzymany->type='l';
        trzymany->obrazek=al_load_bitmap("media/czarnyDamka.png");
        return true;
    }
    return false;
}

bool ruch_damkowy_pg(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany, Szachownica * p)
{
    if(p && p->which_pawn==NULL)
    {
        if(pozX+10>=p->x && pozX-10<=p->x+rozmiar && pozY+10>=p->y && pozY+10<=p->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=p;
            trzymany->Place->which_pawn=trzymany;
            return true;
        }
        else if(p->pg)
        {
            p=p->pg;
            return ruch_damkowy_pg(kolej,pozX,pozY,pole,pawn,trzymany,p);
        }
    }
    else return false;
}

bool ruch_damkowy_lg(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany, Szachownica * p)
{
    if(p && p->which_pawn==NULL)
    {
        if(pozX+10>=p->x && pozX-10<=p->x+rozmiar && pozY+10>=p->y && pozY+10<=p->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=p;
            trzymany->Place->which_pawn=trzymany;
            return true;
        }
        else if(p->lg)
        {
            p=p->lg;
            return ruch_damkowy_lg(kolej,pozX,pozY,pole,pawn,trzymany,p);
        }
    }

    else return false;
}

bool ruch_damkowy_pd(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany, Szachownica * p)
{
    if(p && p->which_pawn==NULL)
    {
        if(pozX+10>=p->x && pozX-10<=p->x+rozmiar && pozY+10>=p->y && pozY+10<=p->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=p;
            trzymany->Place->which_pawn=trzymany;
            return true;
        }
        else if(p->pd)
        {
            p=p->pd;
            return ruch_damkowy_pd(kolej,pozX,pozY,pole,pawn,trzymany,p);
        }
    }

    else return false;
}

bool ruch_damkowy_ld(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany, Szachownica * p)
{
    if(p && p->which_pawn==NULL)
    {
        if(pozX+10>=p->x && pozX-10<=p->x+rozmiar && pozY+10>=p->y && pozY+10<=p->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=p;
            trzymany->Place->which_pawn=trzymany;
            return true;
        }
        else if(p->ld)
        {
            p=p->ld;
            return ruch_damkowy_ld(kolej,pozX,pozY,pole,pawn,trzymany,p);
        }
    }

    else return false;
}

bool ruch_damkowy(int beatseries,char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany)
{
        if(trzymany->kolor==kolej)
        {
            if(pozX>trzymany->Place->x && pozY<trzymany->Place->y) return ruch_damkowy_pg(kolej,pozX,pozY,pole,pawn,trzymany,trzymany->Place->pg);
            else if(pozX<trzymany->Place->x && pozY<trzymany->Place->y) return ruch_damkowy_lg(kolej,pozX,pozY,pole,pawn,trzymany,trzymany->Place->lg);
            else if(pozX>trzymany->Place->x && pozY>trzymany->Place->y) return ruch_damkowy_pd(kolej,pozX,pozY,pole,pawn,trzymany,trzymany->Place->pd);
            else if(pozX<trzymany->Place->x && pozY>trzymany->Place->y) return ruch_damkowy_ld(kolej,pozX,pozY,pole,pawn,trzymany,trzymany->Place->ld);
        }
        return false;
}

bool bicie_damkowe_pg(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany,Szachownica * p,int number_of_enemy)
{
    if(p)
    {
        if(number_of_enemy == 1 && p->which_pawn==NULL && pozX+10>=p->x && pozX-10<=p->x+rozmiar && pozY+10>=p->y && pozY+10<=p->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=p;
            trzymany->Place->which_pawn=trzymany;
            Szachownica * e = trzymany->Place;
            e=e->ld;
            while(!e->which_pawn) e=e->ld;
            usun_pionka(pawn,e->which_pawn);
            e=NULL;
            delete e;
            return true;
        }
        else if(p->pg)
        {
            if(p->which_pawn)
            {
                if (p->which_pawn->kolor!=kolej)
                {
                    number_of_enemy++;
                    if(number_of_enemy>1) return false;
                }
                if(p->which_pawn->kolor==kolej) return false;
            }
            p=p->pg;
            return bicie_damkowe_pg(kolej,pozX,pozY,pole,pawn,trzymany,p,number_of_enemy);
        }
    }
    else return false;
}

bool bicie_damkowe_lg(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany,Szachownica * p,int number_of_enemy)
{
    if(p)
    {
        if(number_of_enemy == 1 && p->which_pawn==NULL && pozX+10>=p->x && pozX-10<=p->x+rozmiar && pozY+10>=p->y && pozY+10<=p->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=p;
            trzymany->Place->which_pawn=trzymany;
            Szachownica * e = trzymany->Place;
            e=e->pd;
            while(!e->which_pawn) e=e->pd;
            usun_pionka(pawn,e->which_pawn);
            e=NULL;
            delete e;
            return true;
        }
        else if(p->lg)
        {
            if(p->which_pawn)
            {
                if (p->which_pawn->kolor!=kolej)
                {
                    number_of_enemy++;
                    if(number_of_enemy>1) return false;
                }
                if(p->which_pawn->kolor==kolej) return false;
            }
            p=p->lg;
            return bicie_damkowe_lg(kolej,pozX,pozY,pole,pawn,trzymany,p,number_of_enemy);
        }//you
    }
    else return false;
}

bool bicie_damkowe_pd(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany,Szachownica * p,int number_of_enemy)
{
    if(p)
    {
        if(number_of_enemy == 1 && p->which_pawn==NULL && pozX+10>=p->x && pozX-10<=p->x+rozmiar && pozY+10>=p->y && pozY+10<=p->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=p;
            trzymany->Place->which_pawn=trzymany;
            Szachownica * e = trzymany->Place;
            e=e->lg;
            while(!e->which_pawn) e=e->lg;
            usun_pionka(pawn,e->which_pawn);
            e=NULL;
            delete e;
            return true;
        }
        else if(p->pd)
        {
            if(p->which_pawn)
            {
                if (p->which_pawn->kolor!=kolej)
                {
                    number_of_enemy++;
                    if(number_of_enemy>1) return false;
                }
                if(p->which_pawn->kolor==kolej) return false;
            }
            p=p->pd;
            return bicie_damkowe_pd(kolej,pozX,pozY,pole,pawn,trzymany,p,number_of_enemy);
        }
    }
    else return false;
}

bool bicie_damkowe_ld(char kolej,int pozX, int pozY, Szachownica *** &pole, Pionek ** &pawn, Pionek * &trzymany,Szachownica * p,int number_of_enemy)
{
    if(p)
    {
        if(number_of_enemy == 1 && p->which_pawn==NULL && pozX+10>=p->x && pozX-10<=p->x+rozmiar && pozY+10>=p->y && pozY+10<=p->y+rozmiar)
        {
            trzymany->Place->which_pawn=NULL;
            trzymany->Place=p;
            trzymany->Place->which_pawn=trzymany;
            Szachownica * e = trzymany->Place;
            e=e->pg;
            while(!e->which_pawn) e=e->pg;
            usun_pionka(pawn,e->which_pawn);
            e=NULL;
            delete e;
            return true;
        }
        else if(p->ld)
        {
            if(p->which_pawn)
            {
                if (p->which_pawn->kolor!=kolej)
                {
                    number_of_enemy++;
                    if(number_of_enemy>1) return false;
                }
                if(p->which_pawn->kolor==kolej) return false;
            }
            p=p->ld;
            return bicie_damkowe_ld(kolej,pozX,pozY,pole,pawn,trzymany,p,number_of_enemy);
        }
    }
    else return false;
}

int bicie_damkowe(int pozX, int pozY, char kolej, int beatseries,Szachownica *** &pole,Pionek ** &pawn, Pionek * &trzymany, Pionek * &bijacy)
{
    if(trzymany->kolor==kolej)
    {
        if(pozX>trzymany->Place->x && pozY<trzymany->Place->y && bicie_damkowe_pg(kolej,pozX,pozY,pole,pawn,trzymany,trzymany->Place->pg,0))
        {
            bijacy=trzymany;
            beatseries++;
        }
        else if(pozX<trzymany->Place->x && pozY<trzymany->Place->y && bicie_damkowe_lg(kolej,pozX,pozY,pole,pawn,trzymany,trzymany->Place->lg,0))
        {
            bijacy=trzymany;
            beatseries++;
        }
        else if(pozX>trzymany->Place->x && pozY>trzymany->Place->y && bicie_damkowe_pd(kolej,pozX,pozY,pole,pawn,trzymany,trzymany->Place->pd,0))
        {
            bijacy=trzymany;
            beatseries++;
        }
        else if(pozX<trzymany->Place->x && pozY>trzymany->Place->y && bicie_damkowe_ld(kolej,pozX,pozY,pole,pawn,trzymany,trzymany->Place->ld,0))
        {
            bijacy=trzymany;
            beatseries++;
        }
    }
    return beatseries;
}

bool czy_wygrana(Pionek ** &pawn,char kolej)
{
    if(kolej=='w')
    {
        for(int i=0;i<12;i++) if(pawn[i]) return false;
        cout<<"Whites Win!\n";
        return true;
    }
    else if(kolej=='b')
    {
        for(int i=12;i<24;i++) if(pawn[i]) return false;
        cout<<"Blackes Win!\n";
        return true;
    }
}



bool czy_bicie_common(Szachownica *** &pole,Pionek * sprawdzany,char kolej)
{
    if(sprawdzany->Place->pg && sprawdzany->Place->pg->pg && sprawdzany->Place->pg->which_pawn && sprawdzany->Place->pg->which_pawn->kolor!=kolej && !sprawdzany->Place->pg->pg->which_pawn) return true;
    else if(sprawdzany->Place->lg && sprawdzany->Place->lg->lg && sprawdzany->Place->lg->which_pawn && sprawdzany->Place->lg->which_pawn->kolor!=kolej && !sprawdzany->Place->lg->lg->which_pawn) return true;
    else if(sprawdzany->Place->pd && sprawdzany->Place->pd->pd && sprawdzany->Place->pd->which_pawn && sprawdzany->Place->pd->which_pawn->kolor!=kolej && !sprawdzany->Place->pd->pd->which_pawn) return true;
    else if(sprawdzany->Place->ld && sprawdzany->Place->ld->ld && sprawdzany->Place->ld->which_pawn && sprawdzany->Place->ld->which_pawn->kolor!=kolej && !sprawdzany->Place->ld->ld->which_pawn) return true;
    return false;
}

Pionek * you_l1_dead_4_not_beat(Szachownica *** &pole, Pionek ** &pawn,char kolej)
{
    int bicia=0;
    if(kolej=='b')
    {
        for(int i=0;i<12;i++)
            if(pawn[i] && pawn[i]->type=='c' && czy_bicie_common(pole,pawn[i],kolej)) return pawn[i];
            else if(pawn[i] && pawn[i]->type=='l' && czy_bicie_lady(pole,pawn[i]->Place,kolej)) return pawn[i];
        return NULL;
    }
    else if(kolej=='w')
    {
        for(int i=12;i<24;i++)
            if(pawn[i] && pawn[i]->type=='c' && czy_bicie_common(pole,pawn[i],kolej)) return pawn[i];
            else if(pawn[i] && pawn[i]->type=='l' && czy_bicie_lady(pole,pawn[i]->Place,kolej)) return pawn[i];
        return NULL;
    }
}

void Wczytaj_z_Pliku(ALLEGRO_DISPLAY *&okno, Szachownica *** &pole, Pionek ** &pawn,Pionek * &trzymany, Pionek * &bijacy, Pionek * &pretendent, char &kolej)
{
    generuj_szachownice(okno,pole,pawn);
        cout<<"wygenerowalo\n";
        FILE * Wczyt;
        Wczyt=fopen("zapis2Players.txt","rt"); cout<<"otwarlo\n";

        char c1,c2;
        int liczba1,liczba2;

        fscanf(Wczyt,"%c\n",&kolej);
        cout<<"we wczycie "<<kolej<<"tyle"<<endl;
        for(int i=0;i<24;i++)
        {
            //cout<<i<<" ";
            fscanf(Wczyt,"%c\n",&c1);
            if(c1=='n')
            {
                //cout<<c1<<endl;
                pawn[i]=NULL;
            }
            else
            {
                pawn[i]=new Pionek;
                pawn[i]->kolor=c1; //;
                fscanf(Wczyt,"%c\n",&c2);
                pawn[i]->type=c2; //cout<<c2<<" ";
                fscanf(Wczyt,"%i\n",&liczba1); //cout<<liczba1<<" ";
                fscanf(Wczyt,"%i\n",&liczba2); //cout<<liczba2<<endl;
                pawn[i]->Place=pole[liczba2][liczba1];
                pawn[i]->Place->which_pawn=pawn[i];
                if(pawn[i]->kolor=='b' && pawn[i]->type=='c') pawn[i]->obrazek=al_load_bitmap("media/czarny.png");
                else if(pawn[i]->kolor=='b' && pawn[i]->type=='l') pawn[i]->obrazek=al_load_bitmap("media/czarnyDamka.png");
                else if(pawn[i]->kolor=='w' && pawn[i]->type=='c') pawn[i]->obrazek=al_load_bitmap("media/bialy.png");
                else if(pawn[i]->kolor=='w' && pawn[i]->type=='l') pawn[i]->obrazek=al_load_bitmap("media/bialyDamka.png");
                cout<<c1<<" "<<c2<<" "<<liczba2<<" "<<liczba1<<endl;
                cout<<pawn[i]->Place->x<<" "<<pawn[i]->Place->y<<endl;
            }
        }
        cout<<"\nzaforowalo\n";
        fclose(Wczyt);
}

void clear_all(Szachownica *** &pole, Pionek ** pawn, ALLEGRO_DISPLAY * &okno, ALLEGRO_EVENT_QUEUE * &kolejka)
{
    al_destroy_display(okno);
    al_destroy_event_queue(kolejka);

    for(int i=0;i<24;i++) if(pawn[i]) usun_pionka(pawn,pawn[i]);
    delete [] pawn;

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            pole[i][j]->which_pawn=NULL;
            al_destroy_bitmap(pole[i][j]->kwadrat);
            pole[i][j]->pg=NULL;
            pole[i][j]->lg=NULL;
            pole[i][j]->pd=NULL;
            pole[i][j]->ld=NULL;
            pole[i][j]=NULL;
            delete pole[i][j];
        }
        delete [] pawn[i];
    }
    delete [] pawn;
}

bool czy_bicie_damkowe_ld(Szachownica *** pole,Szachownica * to,char kolej)
{
    if(!to->ld || !to->ld->ld) return false;
    if(to->ld->which_pawn)
    {
        if(to->ld->which_pawn->kolor==kolej) return false;
        else if(to->ld->which_pawn->kolor!=kolej)
        {
            if(!to->ld->ld->which_pawn) return true;
            else return false;
        }
    }
    return czy_bicie_damkowe_ld(pole,to->ld,kolej);
}
bool czy_bicie_damkowe_pg(Szachownica *** pole,Szachownica * to,char kolej)
{
    cout<<"czy damkowe pg\n";
    if(!to->pg || !to->pg->pg) return false;
    if(to->pg->which_pawn)
    {
        if(to->pg->which_pawn->kolor==kolej) return false;
        else if(to->pg->which_pawn->kolor!=kolej)
        {
            if(!to->pg->pg->which_pawn) return true;
            else return false;
        }
    }
    return czy_bicie_damkowe_pg(pole,to->pg,kolej);
}
bool czy_bicie_damkowe_lg(Szachownica *** pole,Szachownica * to,char kolej)
{
    cout<<"czy damkowe lg\n";
    if(!to->lg || !to->lg->lg) return false;
    if(to->lg->which_pawn)
    {
        if(to->lg->which_pawn->kolor==kolej) return false;
        else if(to->lg->which_pawn->kolor!=kolej)
        {
            if(!to->lg->lg->which_pawn) return true;
            else return false;
        }
    }
    return czy_bicie_damkowe_lg(pole,to->lg,kolej);
}
bool czy_bicie_damkowe_pd(Szachownica *** pole,Szachownica * to,char kolej)
{
    if(!to->pd || !to->pd->pd) return false;
    if(to->pd->which_pawn)
    {
        if(to->pd->which_pawn->kolor==kolej) return false;
        else if(to->pd->which_pawn->kolor!=kolej)
        {
            if(!to->pd->pd->which_pawn) return true;
            else return false;
        }
    }
    return czy_bicie_damkowe_pd(pole,to->pd,kolej);
}
bool czy_bicie_lady(Szachownica *** &pole, Szachownica * to,char kolej)
{
    if(czy_bicie_damkowe_ld(pole,to,kolej)) return true;
    else if(czy_bicie_damkowe_pg(pole,to,kolej)) return true;
    else if(czy_bicie_damkowe_lg(pole,to,kolej)) return true;
    else if(czy_bicie_damkowe_pd(pole,to,kolej)) return true;
    return false;
}





bool Komputer_bicie_common(Szachownica *** &pole,Pionek ** &pawn,Pionek * &sprawdzany,char kolej)
{
    if(sprawdzany->Place->pg && sprawdzany->Place->pg->pg && sprawdzany->Place->pg->which_pawn && sprawdzany->Place->pg->which_pawn->kolor!=kolej && !sprawdzany->Place->pg->pg->which_pawn)
    {
        usun_pionka(pawn,sprawdzany->Place->pg->which_pawn);
        sprawdzany->Place->which_pawn=NULL;
        sprawdzany->Place=sprawdzany->Place->pg->pg;
        sprawdzany->Place->which_pawn=sprawdzany;
        return true;
    }
    else if(sprawdzany->Place->lg && sprawdzany->Place->lg->lg && sprawdzany->Place->lg->which_pawn && sprawdzany->Place->lg->which_pawn->kolor!=kolej && !sprawdzany->Place->lg->lg->which_pawn)
    {
        usun_pionka(pawn,sprawdzany->Place->lg->which_pawn);
        sprawdzany->Place->which_pawn=NULL;
        sprawdzany->Place=sprawdzany->Place->lg->lg;
        sprawdzany->Place->which_pawn=sprawdzany;
        return true;
    }
    else if(sprawdzany->Place->pd && sprawdzany->Place->pd->pd && sprawdzany->Place->pd->which_pawn && sprawdzany->Place->pd->which_pawn->kolor!=kolej && !sprawdzany->Place->pd->pd->which_pawn)
    {
        usun_pionka(pawn,sprawdzany->Place->pd->which_pawn);
        sprawdzany->Place->which_pawn=NULL;
        sprawdzany->Place=sprawdzany->Place->pd->pd;
        sprawdzany->Place->which_pawn=sprawdzany;
        return true;
    }
    else if(sprawdzany->Place->ld && sprawdzany->Place->ld->ld && sprawdzany->Place->ld->which_pawn && sprawdzany->Place->ld->which_pawn->kolor!=kolej && !sprawdzany->Place->ld->ld->which_pawn)
    {
        usun_pionka(pawn,sprawdzany->Place->ld->which_pawn);
        sprawdzany->Place->which_pawn=NULL;
        sprawdzany->Place=sprawdzany->Place->ld->ld;
        sprawdzany->Place->which_pawn=sprawdzany;
        return true;
    }
    return false;
}

bool Komputerowe_bicie_damkowe_ld(Szachownica *** &pole, Pionek ** &pawn, Szachownica * to, Pionek * &sprawdzany, char kolej)
{
    if(!to->ld || !to->ld->ld) return false;
    if(to->ld->which_pawn)
    {
        if(to->ld->which_pawn->kolor==kolej) return false;
        else if(to->ld->which_pawn->kolor!=kolej)
        {
            if(!to->ld->ld->which_pawn)
            {
                usun_pionka(pawn,to->ld->which_pawn);
                sprawdzany->Place->which_pawn=NULL;
                sprawdzany->Place=to->ld->ld;
                sprawdzany->Place->which_pawn=sprawdzany;
                return true;
            }
            else return false;
        }
    }
    return Komputerowe_bicie_damkowe_ld(pole,pawn,to->ld,sprawdzany,kolej);
}
bool Komputerowe_bicie_damkowe_pg(Szachownica *** &pole, Pionek ** &pawn,Szachownica * to,Pionek * &sprawdzany, char kolej)
{
    if(!to->pg || !to->pg->pg) return false;
    if(to->pg->which_pawn)
    {
        if(to->pg->which_pawn->kolor==kolej) return false;
        else if(to->pg->which_pawn->kolor!=kolej)
        {
            if(!to->pg->pg->which_pawn)
            {
                usun_pionka(pawn,to->pg->which_pawn);
                sprawdzany->Place->which_pawn=NULL;
                sprawdzany->Place=to->pg->pg;
                sprawdzany->Place->which_pawn=sprawdzany;
                return true;
            }
            else return false;
        }
    }
    return Komputerowe_bicie_damkowe_pg(pole,pawn,to->pg,sprawdzany,kolej);
}
bool Komputerowe_bicie_damkowe_lg(Szachownica *** &pole, Pionek ** &pawn,Szachownica * to,Pionek * &sprawdzany, char kolej)
{
    if(!to->lg || !to->lg->lg) return false;
    if(to->lg->which_pawn)
    {
        if(to->lg->which_pawn->kolor==kolej) return false;
        else if(to->lg->which_pawn->kolor!=kolej)
        {
            if(!to->lg->lg->which_pawn)
            {
                usun_pionka(pawn,to->lg->which_pawn);
                sprawdzany->Place->which_pawn=NULL;
                sprawdzany->Place=to->lg->lg;
                sprawdzany->Place->which_pawn=sprawdzany;
                return true;
            }
            else return false;
        }
    }//you_
    return Komputerowe_bicie_damkowe_lg(pole,pawn,to->lg,sprawdzany,kolej);
}
bool Komputerowe_bicie_damkowe_pd(Szachownica *** &pole, Pionek ** &pawn,Szachownica * to,Pionek * &sprawdzany, char kolej)
{

    if(!to->pd || !to->pd->pd) return false;
    if(to->pd->which_pawn)
    {
        if(to->pd->which_pawn->kolor==kolej) return false;
        else if(to->pd->which_pawn->kolor!=kolej)
        {

            if(!to->pd->pd->which_pawn)
            {
                usun_pionka(pawn,to->pd->which_pawn);
                sprawdzany->Place->which_pawn=NULL;
                sprawdzany->Place=to->pd->pd;
                sprawdzany->Place->which_pawn=sprawdzany;
                return true;
            }
            else return false;
        }
    }
    return Komputerowe_bicie_damkowe_pd(pole,pawn,to->pd,sprawdzany,kolej);
}
bool Komputerowe_bicie_lady(Szachownica *** &pole, Pionek ** &pawn, Szachownica * to,Pionek *&sprawdzany, char kolej)
{
         if(Komputerowe_bicie_damkowe_ld(pole,pawn,to,sprawdzany,kolej)) return true;
    else if(Komputerowe_bicie_damkowe_pg(pole,pawn,to,sprawdzany,kolej)) return true;
    else if(Komputerowe_bicie_damkowe_lg(pole,pawn,to,sprawdzany,kolej)) return true;
    else if(Komputerowe_bicie_damkowe_pd(pole,pawn,to,sprawdzany,kolej)) return true;
    return false;
}

bool Computer_make_move(Szachownica *** &pole, Pionek ** &pawn, Pionek * &ruchliwy)
{
    if(ruchliwy->type=='c')
    {
        if(ruchliwy->Place->pd && !ruchliwy->Place->pd->which_pawn)
        {
            ruchliwy->Place->which_pawn=NULL;
            ruchliwy->Place=ruchliwy->Place->pd;
            ruchliwy->Place->which_pawn=ruchliwy;
            return true;
        }
        else if(ruchliwy->Place->ld && !ruchliwy->Place->ld->which_pawn)
        {
            ruchliwy->Place->which_pawn=NULL;
            ruchliwy->Place=ruchliwy->Place->ld;
            ruchliwy->Place->which_pawn=ruchliwy;
            return true;
        }
        else return false;
    }
    else if(ruchliwy->type=='l')
    {
        if(ruchliwy->Place->pd && !ruchliwy->Place->pd->which_pawn)
        {
            ruchliwy->Place->which_pawn=NULL;
            ruchliwy->Place=ruchliwy->Place->pd;
            ruchliwy->Place->which_pawn=ruchliwy;
            return true;
        }
        else if(ruchliwy->Place->ld && !ruchliwy->Place->ld->which_pawn)
        {
            ruchliwy->Place->which_pawn=NULL;
            ruchliwy->Place=ruchliwy->Place->ld;
            ruchliwy->Place->which_pawn=ruchliwy;
            return true;
        }
        else if(ruchliwy->Place->pg && !ruchliwy->Place->pg->which_pawn)
        {
            ruchliwy->Place->which_pawn=NULL;
            ruchliwy->Place=ruchliwy->Place->pg;
            ruchliwy->Place->which_pawn=ruchliwy;
            return true;
        }
        else if(ruchliwy->Place->lg && !ruchliwy->Place->lg->which_pawn)
        {
            ruchliwy->Place->which_pawn=NULL;
            ruchliwy->Place=ruchliwy->Place->lg; //czy_wygrana
            ruchliwy->Place->which_pawn=ruchliwy;
            return true;
        }
        else return false;
    }
    return false;
}

void trzasnij(Pionek ** &pawn, Szachownica *** &pole,char kolej)
{
    bool zbicie=false;
    for(int i=0;i<12;i++)
    {
        if(pawn[i] && pawn[i]->type=='c' && Komputer_bicie_common(pole,pawn,pawn[i],kolej))
        {
            zbicie=true;
            zamiana_w_damke(pawn[i]);
            break;
        }
        else if(pawn[i] && pawn[i]->type=='l' && Komputerowe_bicie_lady(pole,pawn,pawn[i]->Place,pawn[i],kolej))
        {
            zbicie=true;
            zamiana_w_damke(pawn[i]);
            break;
        }
    }

    if(!zbicie)
    {
        for(int i=0;i<12;i++)
        {
            if(pawn[i] && Computer_make_move(pole,pawn,pawn[i]))
            {
                zamiana_w_damke(pawn[i]);
                return;
            }
        }
    }
}

