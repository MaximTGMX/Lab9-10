#include <iostream>
#include "tests.h"
#include "player.h"
#include "Repository.h"
#include "RepoFile.h"
#include "UI.h"
#include "Service.h"
using namespace std;
//player vs enemy

int main()
{
    tests();
    Repository rep;
    RepoFile frep("Players.txt");
    Service ser(rep,frep);
    UI ui(ser);
}
