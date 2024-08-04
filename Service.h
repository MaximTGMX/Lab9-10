#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED

#include <iostream>
#include "player.h"
#include "Repository.h"
#include "RepoFile.h"
using namespace std;

class Service
{
    private:
        Repository rep;
        RepoFile frep;
    public:
        Service();
        Service(Repository &r, RepoFile &f);
        ~Service();
        void adauga(Player &p);
        void inventar();
        void sterge(int n);
        int Shop(int test=0);
        void clearPlayer();
        int afiseazaHarta();
        int lupta(int nr=0);
        void getAll();
        Player getByID(int n);
        int getSize();
};

#endif
