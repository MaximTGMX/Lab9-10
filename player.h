#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
using namespace std;

class Player
{
    private:
        int health,attack,defense;
        char* nume;
    public:
        Player();
        Player(char* n, int health, int attack, int defense);
        ~Player();
        void setHealth(int health);
        void setAttack(int attack);
        void setDefense(int defense);
        void setNume(char* n);
        int getHealth();
        int getAttack();
        int getDefense();
        char* getNume();
        void Copy(Player &p);
        bool operator<(Player const& p) const;
        bool operator==(Player const& p) const;
        friend ostream& operator<<(ostream& os, const Player& p)
        {
            os<<"Jucatorul "<<p.nume<<" are "<<p.health<<" viata, "<<p.attack<<" atac si "<<p.defense<<" armura."<<endl;
            return os;
        }
};

#endif
