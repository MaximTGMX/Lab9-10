#ifndef REPOFILE_H_INCLUDED
#define REPOFILE_H_INCLUDED
#include "player.h"
#include "Repository.h"
#pragma once
using namespace std;

#endif

class RepoFile: public Repository
{
    private:
        string filename;
    public:
        RepoFile():Repository(){filename = '\n';};
        RepoFile(string t):Repository(){filename = t;};
        ~RepoFile();
        Repository read(Repository &r);
};
