#include <iostream>
#include "player.h"
#include "UI.h"
#include "Repository.h"
#include "Validare.h"

using namespace std;

Repository::Repository()
{
    this->nr = 0;
    this->HP = 10;
    this->score = 240000;
}

Repository::~Repository()
{

}

void Repository::adauga(Player &p)
{
    try
    {
        if (p.getHealth()<=0) throw Validare("Jucatorul nu poate fi mort!");
        this->lista[nr] = p;
        this->nr++;
    }
    catch (Validare &v)
    {
        cout<<v.getMessage()<<endl;
    }
}

void Repository::adaugaIn(Player &p, int n)
{
    try
    {
        //if (p.getHealth()<=0) throw Validare("Jucatorul nu poate fi mort!");
        for (int i=this->nr;i>=n-1;i--) this->lista[i+1] = this->lista[i];
        this->lista[n-1] = p;
        this->nr++;
    }
    catch (Validare &v)
    {
        cout<<v.getMessage()<<endl;
    }
}

void Repository::sterge(int n)
{
    try
    {
        if (n<0 || n>getSize()) throw Validare("Jucatorul nu exista!");
        for (int i=n-1;i<this->nr;i++)
            this->lista[i] = this->lista[i+1];
        this->nr--;
    }
    catch (Validare &v)
    {
        cout<<v.getMessage()<<endl;
    }
}

Player Repository::getByID(int n)
{
    try
    {
        if (n<1 || n>getSize()+1) throw Validare("Jucatorul nu exista!");
        return this->lista[n-1];
    }
    catch (Validare &v)
    {
        cout<<v.getMessage()<<endl;
    }
}

void Repository::getAll()
{
    for (int i=0;i<this->nr;i++)
        cout<<i+1<<") "<<this->lista[i];
}

int Repository::getSize()
{
    return this->nr;
}

int Repository::getScore()
{
    return this->score;
}

void Repository::addScore(int s)
{
    this->score = this->score+s;
}

int Repository::getHP()
{
    return this->HP;
}

void Repository::addHP(int hp)
{
    this->HP = this->HP+hp;
}

