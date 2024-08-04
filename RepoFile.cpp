#include <iostream>
#include <fstream>
#include <cstring>
#include "player.h"
#include "UI.h"
#include "Repository.h"
#include "RepoFile.h"

using namespace std;
/*
RepoFile::RepoFile()
{
    this->filename = '\n';
}

RepoFile::RepoFile(string t)
{
    this->filename = t;
}
*/
RepoFile::~RepoFile()
{

}

void stoc(string t, char* &s)
{
    for (int i=0;i<t.size();i++)
        s[i] = t[i];
}

Repository RepoFile::read(Repository &r)
{
    int Health=0,Attack=0,Defense=0;
    string text;
    ifstream f(this->filename);
    while(getline(f,text))
    {
        char* stats = new char[text.size()];
        char* nume = new char[text.size()];
        Health=0;Attack=0;Defense=0;
        stoc(text,stats);
        char* a = strtok(stats," ");
        strcpy(nume,a);
        a = strtok(NULL," ");
        Health = atoi(a);
        a = strtok(NULL," ");
        Attack=atoi(a);
        a = strtok(NULL," ");
        Defense=atoi(a);
        Player p(nume,Health,Attack,Defense);
        r.adauga(p);
    }
    return r;
}
