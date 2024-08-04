#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <iostream>
#include "player.h"
#include "Repository.h"
#include "Service.h"
using namespace std;

class UI
{
    private:
        Service ser;
        bool True;
        char* optiune;
    public:
        UI(const Service& s);
        ~UI();
        void Hardcode();
};

#endif
