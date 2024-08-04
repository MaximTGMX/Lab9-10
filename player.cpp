#include <iostream>
#include <cmath>
#include <cstring>
#include "player.h"
using namespace std;

Player::Player()
{
    this->health = 0;
    this->attack = 0;
    this->defense = 0;
    this->nume = new char[1];
    strcpy(this->nume, "\n");
}

Player::Player(char* n, int health, int attack, int defense)
{
    this->health = health;
    this->attack = attack;
    this->defense = defense;
    this->nume = new char[strlen(n)+1];
    strcpy(this->nume,n);
}

Player::~Player()
{

}

//Getteri

int Player::getHealth()
{
    return this->health;
}

int Player::getAttack()
{
    return this->attack;
}

int Player::getDefense()
{
    return this->defense;
}

char* Player::getNume()
{
    return this->nume;
}

//Setteri

void Player::setHealth(int h)
{
    this->health = h;
}

void Player::setAttack(int a)
{
    this->attack = a;
}

void Player::setDefense(int d)
{
    this->defense = d;
}

void Player::setNume(char* n)
{
    this->nume = new char[strlen(n)+1];
    strcpy(this->nume,n);
}

void Player::Copy(Player &p)
{
    this->health = p.getHealth();
    this->attack = p.getAttack();
    this->defense = p.getDefense();
    this->nume = new char[strlen(p.getNume())+1];
    strcpy(this->nume,p.getNume());
}
