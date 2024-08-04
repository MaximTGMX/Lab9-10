#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <cstdlib>
#include <stdlib.h>
#include "player.h"
#include "Repository.h"
#include "Service.h"
#include "UI.h"

void Menu()
{
    cout<<"adauga. Adauga un jucator\n";
    cout<<"sterge. Sterge jucatorii morti\n";
    cout<<"exploreaza. Exploreaza harta\n";
    cout<<"inventar. Afiseaza inventarul\n";
    cout<<"listeaza. Afiseaza toti jucatorii\n";
    cout<<"lupta. Elimina un jucator\n";
    cout<<"shop. Cumpara iteme din shop.\n";
    cout<<"exit. Iesire\n";
    cout<<endl;
}

void citesteOptiune(char* &n)
{
    cout<<"Dati optiunea: ";
    cin>>n;
}

int CheckDigit(char *n)
{
    bool hasDigit=false, hasChar = false;
    for (int i=0;i<strlen(n);i++)
        if ((n[i]<'0' || n[i]>'9') && n[i]!=' ') hasChar = true;
        else hasDigit = true;
    if (hasDigit && hasChar) return -1;
    if (!hasDigit && hasChar) return 0;
    if (hasDigit && !hasChar) return 1;
}

void CopyText(char* &s, string t, bool b=true)
{
    if (b)
        for (int i=1;i<t.size();i++)
            s[i-1] = t[i];
    else
        for (int i=0;i<t.size();i++)
            s[i] = t[i];
}

void UI::Hardcode()
{
    Player p("Barosu", 400, 15, 28);
    this->ser.adauga(p);
    Player p2("Caine", 90, 8, 0);
    this->ser.adauga(p2);
    Player p3("Musculosu", 240, 40, 16);
    this->ser.adauga(p3);
}

UI::UI(const Service& s)
{
    Repository rezerva;

    this->ser = s;
    this->True = true;
    this->optiune = new char[25];

    //Hardcode();
    int lupta=0;
    //strcpy(this->optiune,"lupta");

    while (this->True)
    {
        if (lupta<1) {Menu(); citesteOptiune(this->optiune);}
        if (strcmp(this->optiune,"listeaza")==0)
        {
            this->ser.getAll();
        }
        else if (strcmp(this->optiune,"inventar")==0)
        {
            this->ser.inventar();
        }
        else if (strcmp(this->optiune,"sterge")==0)
        {
            this->ser.clearPlayer();
        }
        else if (strcmp(this->optiune,"shop")==0)
        {
            this->ser.Shop();
        }
        else if(strcmp(this->optiune,"adauga")==0)
        {
            string n;
            int health,attack,defense;
            cout<<"Dati numele jucatorului (adaugati ; la sfarsitul numelui): ";
            getline(cin,n,';');
            cout<<"Dati atributele jucatorului (viata, atac, armura): ";
            cin>>health>>attack>>defense;
            char* text = new char[n.size()];
            CopyText(text,n);
            Player p(text, health, attack, defense);
            this->ser.adauga(p);
        }
        else if (strcmp(this->optiune,"exploreaza")==0)
        {
            lupta = this->ser.afiseazaHarta();
            if (lupta>0) strcpy(this->optiune,"lupta");
            else Menu();
        }
        else if (strcmp(this->optiune,"lupta")==0)
        {
            this->ser.lupta(lupta);
            lupta=0;
            //system("cls");
        }
        else if(strcmp(this->optiune,"exit")==0)
            {this->True = false; break;}
        else cout<<"Optiune invalida!"<<endl;
        cout<<endl;
    }
}

UI::~UI()
{
    delete[] this->optiune;
    this->optiune = NULL;
}
