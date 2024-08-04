#include "tests.h"
#include "player.h"
#include "UI.h"
#include "Repository.h"
#include "RepoFile.h"
#include "Service.h"
#include <iostream>
#include <cstring>
#include <assert.h>
using namespace std;

void tests()
{
    cout<<"---first tests---"<<endl<<endl;
    Player p;
    assert(p.getHealth()==0);
    assert(p.getAttack()==0);
    assert(p.getDefense()==0);
    assert(*p.getNume()=='\n');
    p.setHealth(100);
    p.setAttack(11);
    p.setDefense(11);
    p.setNume("Larry");
    assert(p.getHealth()==100);
    assert(p.getAttack()==11);
    assert(p.getDefense()==11);
    assert(strcmp(p.getNume(),"Larry")==0);

    Repository rep;
    rep.adauga(p);
    assert(rep.getSize()==1);
    rep.sterge(0);
    assert(rep.getSize()==0);

    Service ser;
    Player p1("Barosu", 400, 15, 28);
    ser.adauga(p1);
    Player p2("Caine", -2, 8, 10);
    ser.adauga(p2);
    Player p3("Musculosu", 240, 40, 16);
    ser.adauga(p3);
    assert(ser.getSize()==2);
    ser.sterge(2);
    assert(ser.getSize()==1);
    ser.adauga(p3);
    ser.clearPlayer();
    assert(ser.getSize()==2);

    //assert(ser.Shop(1)==1);
    //assert(ser.Shop(2)==0);
    assert(ser.lupta(4)==-1);

    RepoFile frep("Players.txt");
    frep.read(rep);
    assert(rep.getSize()==5);
    assert(rep.getByID(1).getAttack()==15);

    cout<<"--all tests are good"<<endl<<endl;
}
