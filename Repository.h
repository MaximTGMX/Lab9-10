#ifndef REPOSITORY_H_INCLUDED
#define REPOSITORY_H_INCLUDED
#include "player.h"
#pragma once
using namespace std;

#endif

class Repository
{
    private:
        Player lista[100];
        int nr,score,HP;
    public:
        Repository();
        ~Repository();
        int getScore();
        void addScore(int s);
        int getHP();
        void addHP(int hp);
        void adauga(Player &p);
        void adaugaIn(Player &p, int n);
        void sterge(int n);
        void getAll();
        Player getByID(int n);
        int getSize();
};
