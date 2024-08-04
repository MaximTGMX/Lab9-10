#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <mmsystem.h>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include "player.h"
#include "Repository.h"
#include "Service.h"
#include <random>

#pragma comment(lib, "winmm.lib")

int randomnumber(int a, int b)
{
    static std::default_random_engine rng;

    std::uniform_int_distribution<int> dist(a, b);
    return dist(rng);
}

Service::Service()
{

}

Service::Service(Repository &r, RepoFile &f)
{
    this->rep = r;
    this->frep = f;
    this->frep.read(this->rep);
}

Service::~Service()
{

}

int Service::Shop(int test)
{
    if (test>0)
    {
        if (test==1) return (this->rep.getScore()>200);
        if (test==2) return (this->rep.getScore()>240000);
        if (test==3) return (this->rep.getScore()>40000);
        if (test==4) return (this->rep.getScore()>200000);
        return (this->rep.getScore()>25000);
    }
    else
    {
        PlaySound(TEXT("SHOP.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        int optiune=0,pret=0,size=this->rep.getSize();
        bool t=true,sold1=false,sold2=false,sold3=false,sold4=false;
        while(t)
        {
            if (GetAsyncKeyState(VK_DOWN)) optiune++;
            if (GetAsyncKeyState(VK_UP)) {optiune--; if (optiune<0) optiune=4;}
            Sleep(200);
            system("cls");
            cout<<"$------Shop------$"<<endl<<endl<<endl;
            if (optiune%5==0) cout<<">  Potiuni de viata: Adauga 10 potiuni de viata in inventar."<<endl<<"  Armura din Auric Tesla"<<endl<<"  Armura hidrotermica"<<endl<<"  Murasama"<<endl<<"  Marginea noptii"<<endl;
            else if (optiune%5==1) cout<<"  Potiuni de viata"<<endl<<">  Armura din Auric Tesla: Echipeaza toti jucatorii cu armura (+1400 viata, +260 atac, +140 armura)."<<endl<<"  Armura hidrotermica"<<endl<<"  Murasama"<<endl<<"  Marginea noptii"<<endl;
            else if (optiune%5==2) cout<<"  Potiuni de viata"<<endl<<"  Armura din Auric Tesla"<<endl<<">  Armura hidrotermica: Echipeaza toti jucatorii cu armura (+600 viata, +145 atac, +80 armura)."<<endl<<"  Murasama"<<endl<<"  Marginea noptii"<<endl;
            else if (optiune%5==3) cout<<"  Potiuni de viata"<<endl<<"  Armura din Auric Tesla"<<endl<<"  Armura hidrotermica"<<endl<<">  Murasama: Echipeaza toti jucatorii cu sabia (+1460 atac)."<<endl<<"  Marginea noptii"<<endl;
            else if (optiune%5==4) cout<<"  Potiuni de viata"<<endl<<"  Armura din Auric Tesla"<<endl<<"  Armura hidrotermica"<<endl<<"  Murasama"<<endl<<">  Marginea noptii: Echipeaza toti jucatorii cu sabia (+380 atac)."<<endl;
            cout<<endl<<endl<<"Apasa Esc pentru a iesi."<<endl<<"Apasa Shift pentru a continua."<<endl<<endl;

            cout<<"Pret: ";
            if (optiune%5==0) {pret=200; cout<<"200 BP"<<endl;}
            else if (optiune%5==1) {pret=240000; cout<<"240k BP"; if(sold1) cout<<" (Vandut)"; cout<<endl;}
            else if (optiune%5==2) {pret=40000; cout<<"40k BP"; if(sold2) cout<<" (Vandut)"; cout<<endl;}
            else if (optiune%5==3) {pret=200000; cout<<"200k BP"; if(sold3) cout<<" (Vandut)"; cout<<endl;}
            else if (optiune%5==4) {pret=25000; cout<<"25k BP"; if(sold4) cout<<" (Vandut)"; cout<<endl;}
            cout<<"BP-ul tau: "<<this->rep.getScore()<<endl;

            if (GetAsyncKeyState(VK_ESCAPE)) {PlaySound(0,0,0); return 0;}
            if (GetAsyncKeyState(VK_SHIFT))
            {
                if (this->rep.getScore()<pret) {cout<<endl<<"BP insuficiente!"; Sleep(1500);}
                else if ((optiune%5==1 && sold1)||(optiune%5==2 && sold2)||(optiune%5==3 && sold3)||(optiune%5==4 && sold4)) {cout<<endl<<"Ramas fara stoc!"; Sleep(1500);}
                else if ((optiune%5==2 && sold1)||(optiune%5==4 && sold3)) {cout<<endl<<"Nu se poate achizitiona!"; Sleep(1500);}
                else
                {
                    this->rep.addScore(-pret);
                    if (optiune%5==0) this->rep.addHP(10);
                    else if (optiune%5==1)
                        for (int i=0;i<size;i++)
                        {
                            if (this->rep.getByID(i+1).getHealth() > 0)
                                if(sold2)
                                {
                                    Player p(this->rep.getByID(i+1).getNume(),this->rep.getByID(i+1).getHealth()+800,this->rep.getByID(i+1).getAttack()+155,this->rep.getByID(i+1).getDefense()+60);
                                    this->rep.sterge(i+1);
                                    this->rep.adaugaIn(p,i+1);
                                    sold1=true;
                                }
                                else
                                {
                                    Player p(this->rep.getByID(i+1).getNume(),this->rep.getByID(i+1).getHealth()+1400,this->rep.getByID(i+1).getAttack()+260,this->rep.getByID(i+1).getDefense()+140);
                                    this->rep.sterge(i+1);
                                    this->rep.adaugaIn(p,i+1);
                                    sold1=true;
                                }
                        }
                    else if (optiune%5==2)
                        for (int i=0;i<size;i++) {Player p(this->rep.getByID(i+1).getNume(),this->rep.getByID(i+1).getHealth()+600,this->rep.getByID(i+1).getAttack()+145,this->rep.getByID(i+1).getDefense()+80); this->rep.sterge(i+1); this->rep.adaugaIn(p,i+1); sold2=true;}
                    else if (optiune%5==3)
                        for (int i=0;i<size;i++)
                        {
                            if (sold4)
                            {
                                Player p(this->rep.getByID(i+1).getNume(),this->rep.getByID(i+1).getHealth(),this->rep.getByID(i+1).getAttack()+1080,this->rep.getByID(i+1).getDefense());
                                this->rep.sterge(i+1);
                                this->rep.adaugaIn(p,i+1);
                                sold3=true;
                            }
                            else
                            {
                                Player p(this->rep.getByID(i+1).getNume(),this->rep.getByID(i+1).getHealth(),this->rep.getByID(i+1).getAttack()+1460,this->rep.getByID(i+1).getDefense());
                                this->rep.sterge(i+1);
                                this->rep.adaugaIn(p,i+1);
                                sold3=true;
                            }
                        }
                    else if (optiune%5==4)
                        for (int i=0;i<size;i++) {Player p(this->rep.getByID(i+1).getNume(),this->rep.getByID(i+1).getHealth(),this->rep.getByID(i+1).getAttack()+380,this->rep.getByID(i+1).getDefense()); this->rep.sterge(i+1); this->rep.adaugaIn(p,i+1); sold4=true;}
                    cout<<endl<<"Cumparat!";
                    Sleep(1500);
                }
            }
        }
    }
}

int Service::afiseazaHarta()
{
    int nivel=0,size=0;
    string n[20];
    bool t = true;
    while (t)
    {
        if (GetAsyncKeyState(VK_DOWN)) {nivel++; PlaySound(TEXT("CLICK.wav"), NULL, SND_FILENAME | SND_ASYNC);}
        if (GetAsyncKeyState(VK_UP)) {nivel--; if (nivel<0) nivel=2; PlaySound(TEXT("CLICK.wav"), NULL, SND_FILENAME | SND_ASYNC);}
        Sleep(200);
        system("cls");
        cout<<"Selecteaza nivelul:"<<endl;
        if (nivel%3==0) cout<<">  Rebeliunea"<<endl<<"  Preluare ostila"<<endl<<"  Centru de cercetare"<<endl;
        else if (nivel%3==1) cout<<"  Rebeliunea"<<endl<<">  Preluare ostila"<<endl<<"  Centru de cercetare"<<endl;
        else if (nivel%3==2) cout<<"  Rebeliunea"<<endl<<"  Preluare ostila"<<endl<<">  Centru de cercetare"<<endl;
        cout<<endl<<endl<<"Apasa Esc pentru a iesi."<<endl<<"Apasa Shift pentru a continua."<<endl<<endl;

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            PlaySound(TEXT("SELECT.wav"), NULL, SND_FILENAME | SND_ASYNC);
            return 0;
        }

        if (GetAsyncKeyState(VK_SHIFT))
        {
            nivel = nivel%3+1;
            PlaySound(TEXT("SELECT.wav"), NULL, SND_FILENAME | SND_ASYNC);
            string filename = "Harta"+to_string(nivel)+".txt";
            ifstream f(filename);
            while(getline(f,n[size])) size++;
            t = false;
            break;
        }
    }

    Sleep(1000);

    bool canJump=true;
    int onElevator=0;
    char s=n[9][1];
    int x=1,y=9,SPX=1,SPY=9;
    int c=1;
    struct elevator{int x,y,ymin,ymax; bool moveDown=false;}e[10];

    if (nivel==1)
    {
        PlaySound(TEXT("RECON.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        t=true;
        for (int i=0;i<size;i++)
            for (int j=0;j<n[i].size();j++)
                if (n[i][j]=='-') {e[c].x=j; e[c].y=i; e[c].ymin = e[c].y-3; e[c].ymax=i+1; c++;}
        e[1].ymin = e[1].y-3;//randomnumber(1,3);
        e[2].ymin = e[2].y-3;//randomnumber(1,3);
        n[y][x]='0';
    }
    else if (nivel==2)
    {
        PlaySound(TEXT("STEEL BEACH.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        t=true;
        for (int i=0;i<size;i++)
            for (int j=0;j<n[i].size();j++)
                if (n[i][j]=='-') {e[c].x=j; e[c].y=i; e[c].ymin = e[c].y-3; e[c].ymax=i+1; c++;}
        e[1].ymin = e[1].y-3;//randomnumber(1,3);
        e[2].ymin = e[2].y-3;//randomnumber(1,3);
        n[y][x]='0';
    }
    else if (nivel==3)
    {
        PlaySound(TEXT("TOXIC.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        t=true;
        for (int i=0;i<size;i++)
            for (int j=0;j<n[i].size();j++)
                if (n[i][j]=='-') {e[c].x=j; e[c].y=i; e[c].ymin = e[c].y-3; e[c].ymax=i+1; c++;}
        e[1].ymin = e[1].y-3;//randomnumber(1,3);
        e[2].ymin = e[2].y-3;//randomnumber(1,3);
        n[y][x]='0';
    }

        while (t)
        {
            cout<<"Esc. Exit\n";
            cout<<"<- ->. Move\n";
            cout<<"Space. Jump\n";

            for (int j=1;j<c;j++)
            {
                if (e[j].moveDown)
                {
                    if (e[j].y+1>e[j].ymax) e[j].moveDown = false;
                    else
                    {
                        if (y==e[j].y && x==e[j].x) {e[j].y++; n[e[j].y][e[j].x]='0'; y=e[j].y; onElevator=j;}
                        else {if (j==onElevator) onElevator=0; e[j].y++; n[e[j].y][e[j].x]='-';}
                        n[e[j].y-1][e[j].x]=' ';
                    }
                }
                else
                {
                    if (e[j].y-1<e[j].ymin) e[j].moveDown = true;
                    else
                    {
                        if (y==e[j].y && x==e[j].x) {e[j].y--; n[e[j].y][e[j].x]='0'; y=e[j].y; onElevator=j;}
                        else {if (j==onElevator) onElevator=0; e[j].y--; n[e[j].y][e[j].x]='-';}
                        n[e[j].y+1][e[j].x]=' ';
                    }
                }
            }

            if (n[y+1][x]=='^') {n[y][x]=s; x=SPX; y=SPY; n[y][x]='0'; Sleep(200);}
            if (n[y+1][x]!='@' && n[y+1][x]!='|' && !onElevator) {n[y][x]=s; y++; s=n[y][x]; n[y][x]='0'; Sleep(200); canJump=false;}
            else
            {
                SPX=x;
                SPY=y-1;
                Sleep(200);
                canJump=true;
            }
            if (s=='x')
            {
                t=false; PlaySound(0,0,0);
                this->rep.addScore(nivel*10000);
                cout<<"Scor nou: "<<this->rep.getScore()<<endl<<endl;
                return nivel;
            }
            if (s=='U')
            {
                s='_';
                this->rep.addScore(15000);
            }
            if (GetAsyncKeyState(VK_ESCAPE)) {t=false; PlaySound(0,0,0); return 0;}
            if (GetAsyncKeyState(VK_RIGHT) && n[y][x+1]!='|') {n[y][x]=s; x++; s=n[y][x]; n[y][x]='0';}
            if (GetAsyncKeyState(VK_LEFT) && n[y][x-1]!='|') {n[y][x]=s; x--; s=n[y][x]; n[y][x]='0';}
            if (GetAsyncKeyState(VK_SPACE) && n[y-1][x]!='@' && n[y-1][x]!='|' && canJump)
            {
                int d=3;
                while (d)
                {
                    if (y-1<=0 || n[y-1][x]=='@' || n[y-1][x]=='|') break;
                    n[y][x]=s;
                    y--;
                    s=n[y][x];
                    n[y][x]='0';
                    d--;
                    canJump=false;
                }
            }

            system("cls");

            cout<<endl<<endl;
            for (int i=0;i<size;i++) cout<<n[i]<<endl;
            cout<<endl<<endl;
            //Sleep(500);
        }
        n[y][x]=s;
}

int Service::lupta(int nr)
{
    bool QTE=false;
    int qte=20,state=0;
    if (nr>3) return -1;
    if (!nr)
    {
        bool t = true;
        while (t)
        {
            if (GetAsyncKeyState(VK_DOWN)) {nr++; PlaySound(TEXT("CLICK.wav"), NULL, SND_FILENAME | SND_ASYNC);}
            if (GetAsyncKeyState(VK_UP)) {nr--; if (nr<0) nr=2; PlaySound(TEXT("CLICK.wav"), NULL, SND_FILENAME | SND_ASYNC);}
            Sleep(200);
            system("cls");
            cout<<"Selecteaza seful:"<<endl;
            if (nr%3==0) cout<<">  LQ-84I"<<endl<<"  Sundowner"<<endl<<"  Metal Gear Ray"<<endl;
            else if (nr%3==1) cout<<"  LQ-84I"<<endl<<">  Sundowner"<<endl<<"  Metal Gear Ray"<<endl;
            else if (nr%3==2) cout<<"  LQ-84I"<<endl<<"  Sundowner"<<endl<<">  Metal Gear Ray"<<endl;
            cout<<endl<<endl<<"Apasa Esc pentru a iesi."<<endl<<"Apasa Shift pentru a continua."<<endl<<endl;

            if (GetAsyncKeyState(VK_ESCAPE))
            {
                PlaySound(TEXT("SELECT.wav"), NULL, SND_FILENAME | SND_ASYNC);
                return -1;
            }

            if (GetAsyncKeyState(VK_SHIFT))
            {
                PlaySound(TEXT("SELECT.wav"), NULL, SND_FILENAME | SND_ASYNC);
                nr = nr%3+1;
                t = false;
                break;
            }
        }
    }

    this->rep.getAll();
    cout<<endl;
    char optiune[10];
    cout<<"Alegeti jucatorul: ";
    cin>>optiune;
    while(atoi(optiune)<=0 || atoi(optiune)>this->rep.getSize() || this->rep.getByID(atoi(optiune)).getHealth()<=0) {cout<<"Optiune invalida!\nAlegeti jucatorul: "; cin>>optiune;}
    cout<<"Jucator ales: "<<this->rep.getByID(atoi(optiune)).getNume()<<". Sa inceapa lupta!\n";
    system("pause");

    bool t=true,yourTurn=true, playerDefend=false, enemyDefend=false;
    int MaxHealth = this->rep.getByID(atoi(optiune)).getHealth();
    int Health=500,Attack=10,AltAttack=7,Defense=5;
    string Name="LQ-84I";
    string attacks[10]={"Atac","Atac cu proiectile","Apara"};
    string knight[40], dawg[40], battle[40];
    string enemyfile[3];
    int atacInamic = randomnumber(0,2);

    if (nr==1)
    {
        MaxHealth = this->rep.getByID(atoi(optiune)).getHealth();
        int atacInamic = randomnumber(0,2);
        Health=500;Attack=10;AltAttack=7;Defense=5;
        Name="LQ-84I";
        PlaySound(TEXT("DAWG.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        attacks[0]="Atac";
        attacks[1]="Atac cu proiectile";
        attacks[2]="Apara";
        enemyfile[0]="Dawg1.txt";
        enemyfile[1]="Dawg2.txt";
        enemyfile[2]="Dawg3.txt";
    }
    else if (nr==2)
    {
        MaxHealth = this->rep.getByID(atoi(optiune)).getHealth();
        int atacInamic = randomnumber(0,2);
        Health=1000;Attack=30;AltAttack=18;Defense=12;
        Name="Sundowner";
        PlaySound(TEXT("REDSUN.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        attacks[0]="Atac";
        attacks[1]="Atac cu avant";
        attacks[2]="Apara";
        enemyfile[0]="Sundowner1.txt";
        enemyfile[1]="Sundowner2.txt";
        enemyfile[2]="Sundowner3.txt";
    }
    else if (nr==3)
    {
        MaxHealth = this->rep.getByID(atoi(optiune)).getHealth();
        int atacInamic = randomnumber(0,2);
        Health=5000;Attack=60;AltAttack=100;Defense=250;
        Name="Metal Gear Ray";
        PlaySound(TEXT("RULESOFNATURE.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        attacks[0]="Atac";
        attacks[1]="Laser";
        attacks[2]="Apara";
        enemyfile[0]="MGR1.txt";
        enemyfile[1]="MGR2.txt";
        enemyfile[2]="MGR3.txt";

    }

    int i=0;
    ifstream f("Knight1.txt");
    ifstream g(enemyfile[0]);
    if (nr!=3) while(getline(f,knight[i]) && getline(g,dawg[i])) i++;
    else
        while(getline(g,dawg[i]))
        {
            if (i<19) knight[i]="      ";
            else getline(f,knight[i]);
            i++;
        }

    int size=i;
    for (int i=0;i<size;i++) battle[i] = battle[i]+knight[i]+"          "+dawg[i];

    size++;
    size++;
    battle[size] = battle[size]+"Nume: "+this->rep.getByID(atoi(optiune)).getNume()+"          Nume: "+Name;
    size++;
    battle[size] = battle[size]+"Viata: "+to_string(this->rep.getByID(atoi(optiune)).getHealth())+"          Viata: "+to_string(Health);
    size++;
    battle[size] = battle[size]+"Atac: "+to_string(this->rep.getByID(atoi(optiune)).getAttack())+"          Atac: "+to_string(Attack)+"("+to_string(AltAttack)+')';
    size++;
    battle[size] = battle[size]+"Armura: "+to_string(this->rep.getByID(atoi(optiune)).getDefense())+"          Armura: "+to_string(Defense);
    size++;
    size++;
    battle[size] = battle[size]+"Atacul urmator al inamicului: "+attacks[atacInamic];
    size++;
    battle[size] = battle[size]+"Tura ta";
    size++;

    while (t)
    {
        if (Health>0 && this->rep.getByID(atoi(optiune)).getHealth()>0)
        {
            cout<<"Esc. Surrender\n";
            cout<<"CTRL. Attack\n";
            cout<<"Shift. Defend\n";
            cout<<"Space. Heal (Potiuni de viata ramase: "<<this->rep.getHP()<<")\n";

            if (GetAsyncKeyState(VK_ESCAPE)) {t=false; PlaySound(0,0,0); return -1;}
            if (GetAsyncKeyState(VK_CONTROL) && yourTurn)
            {
                ifstream f("Knight3.txt");
                int i=0;
                if (nr==3) i=19;
                while(getline(f,knight[i])) i++;
                for (int i=0;i<size;i++)
                    for (int j=0;j<knight[i].size();j++) if (knight[i][j]=='1') knight[i][j]=' ';
                for (int i=0;i<size-9;i++)
                if (nr==3)
                    if (i<19)battle[i] = "          "+knight[i]+dawg[i];
                    else  battle[i] = "    "+knight[i]+dawg[i];
                else
                    battle[i] = "    "+knight[i]+dawg[i];
                system("cls");
                if (enemyDefend && nr!=2) {Health = Health - (this->rep.getByID(atoi(optiune)).getAttack() - Defense); enemyDefend=false;}
                else if (enemyDefend && nr==2)
                {
                    Player p(this->rep.getByID(atoi(optiune)).getNume(),this->rep.getByID(atoi(optiune)).getHealth()-50,this->rep.getByID(atoi(optiune)).getAttack(),this->rep.getByID(atoi(optiune)).getDefense());
                    this->rep.sterge(atoi(optiune));
                    this->rep.adaugaIn(p,atoi(optiune));
                    battle[size-6] = "Viata: "+to_string(this->rep.getByID(atoi(optiune)).getHealth())+"          Viata: "+to_string(Health);
                    enemyDefend=false;
                }
                else Health = Health - (this->rep.getByID(atoi(optiune)).getAttack() - Defense/2);
                battle[size-6] = "Viata: "+to_string(this->rep.getByID(atoi(optiune)).getHealth())+"          Viata: "+to_string(Health);
                for (int i=0;i<size;i++) cout<<battle[i]<<endl;
                cout<<endl<<endl;
                Sleep(1000);
                ifstream g("Knight1.txt");
                i=0;
                if (nr==3) i=19;
                while(getline(g,knight[i])) i++;
                for (int i=0;i<size-9;i++) battle[i] = knight[i]+"          "+dawg[i];
                yourTurn = false;
                battle[size-1] = "Tura inamicului";
            }
            if (GetAsyncKeyState(VK_SHIFT) && yourTurn)
            {
                playerDefend = true;
                ifstream f("Knight2.txt");
                int i=0;
                if (nr==3) i=19;
                while(getline(f,knight[i])) i++;
                for (int i=0;i<size;i++)
                    for (int j=0;j<knight[i].size();j++) if (knight[i][j]=='1') knight[i][j]=' ';
                for (int i=0;i<size-9;i++)
                if (nr==3)
                    if (i<19)
                        battle[i] = knight[i]+"          "+dawg[i];
                    else
                        battle[i] = knight[i]+"        "+dawg[i];
                else
                    battle[i] = knight[i]+"        "+dawg[i];
                system("cls");
                for (int i=0;i<size;i++) cout<<battle[i]<<endl;
                cout<<endl<<endl;
                Sleep(1000);
                yourTurn = false;
                battle[size-1] = "Tura inamicului";
            }
            if (GetAsyncKeyState(VK_SPACE) && yourTurn && this->rep.getHP()>0)
            {
                this->rep.addHP(-1);
                int h=this->rep.getByID(atoi(optiune)).getHealth();
                if (h+50 > MaxHealth) h=MaxHealth;
                else h+=50;
                Player p(this->rep.getByID(atoi(optiune)).getNume(),h,this->rep.getByID(atoi(optiune)).getAttack(),this->rep.getByID(atoi(optiune)).getDefense());
                this->rep.sterge(atoi(optiune));
                this->rep.adaugaIn(p,atoi(optiune));
                system("cls");
                battle[size-6] = "Viata: "+to_string(this->rep.getByID(atoi(optiune)).getHealth())+"          Viata: "+to_string(Health);
                for (int i=0;i<size;i++) cout<<battle[i]<<endl;
                cout<<endl<<endl;
                Sleep(1000);
                yourTurn = false;
                battle[size-1] = "Tura inamicului";
            }

            Sleep(200);
            system("cls");
            for (int i=0;i<size;i++) cout<<battle[i]<<endl;
            cout<<endl<<endl;

            if (!yourTurn && Health>0)
            {
                Sleep(1000);
                if (atacInamic==0)
                {
                    for (int i=0;i<size-9;i++) battle[i] = knight[i]+dawg[i];
                    system("cls");
                    int h;
                    if (playerDefend) {h = this->rep.getByID(atoi(optiune)).getHealth() - max(0,Attack-this->rep.getByID(atoi(optiune)).getDefense()); playerDefend=false;}
                    else h = this->rep.getByID(atoi(optiune)).getHealth() - max(0,Attack-(this->rep.getByID(atoi(optiune)).getDefense()/2));
                    Player p(this->rep.getByID(atoi(optiune)).getNume(),h,this->rep.getByID(atoi(optiune)).getAttack(),this->rep.getByID(atoi(optiune)).getDefense());
                    this->rep.sterge(atoi(optiune));
                    this->rep.adaugaIn(p,atoi(optiune));
                    battle[size-6] = "Viata: "+to_string(this->rep.getByID(atoi(optiune)).getHealth())+"          Viata: "+to_string(Health);
                    for (int i=0;i<size;i++) cout<<battle[i]<<endl;
                    cout<<endl<<endl;
                    Sleep(1000);
                    ifstream g("Knight1.txt");
                    i=0;
                    if (nr==3) i=19;
                    while(getline(g,knight[i])) i++;
                    for (int i=0;i<size-9;i++) battle[i] = knight[i]+"          "+dawg[i];
                    yourTurn = true;
                    atacInamic = randomnumber(0,8)%3;
                    battle[size-2] = "Atacul urmator al inamicului: "+attacks[atacInamic];
                    battle[size-1] = "Tura ta";
                }
                else if (atacInamic==1)
                {
                    ifstream f(enemyfile[1]);
                    int i=0;
                    while(getline(f,dawg[i])) i++;
                    for (int i=0;i<size-9;i++) battle[i] = knight[i]+"        "+dawg[i];
                    system("cls");
                    int h;
                    if (playerDefend) h = this->rep.getByID(atoi(optiune)).getHealth() - max(0,AltAttack-this->rep.getByID(atoi(optiune)).getDefense());
                    else h = this->rep.getByID(atoi(optiune)).getHealth() - max(0,AltAttack-this->rep.getByID(atoi(optiune)).getDefense()/2);
                    Player p(this->rep.getByID(atoi(optiune)).getNume(),h,this->rep.getByID(atoi(optiune)).getAttack(),this->rep.getByID(atoi(optiune)).getDefense());
                    this->rep.sterge(atoi(optiune));
                    this->rep.adaugaIn(p,atoi(optiune));
                    battle[size-6] = "Viata: "+to_string(this->rep.getByID(atoi(optiune)).getHealth())+"          Viata: "+to_string(Health);
                    for (int i=0;i<size;i++) cout<<battle[i]<<endl;
                    cout<<endl<<endl;
                    Sleep(1000);
                    ifstream g(enemyfile[0]);
                    i=0;
                    while(getline(g,dawg[i])) i++;
                    for (int i=0;i<size-9;i++) battle[i] = knight[i]+"          "+dawg[i];
                    yourTurn = true;
                    atacInamic = randomnumber(0,8)%3;
                    battle[size-2] = "Atacul urmator al inamicului: "+attacks[atacInamic];
                    battle[size-1] = "Tura ta";
                }
                else if (atacInamic==2)
                {
                    ifstream f(enemyfile[2]);
                    int i=0;
                    while(getline(f,dawg[i])) i++;
                    for (int i=0;i<size-9;i++) battle[i] = knight[i]+"        "+dawg[i];
                    system("cls");
                    int h;
                    if (playerDefend) h = this->rep.getByID(atoi(optiune)).getHealth() - max(0,AltAttack-Defense);
                    else h = this->rep.getByID(atoi(optiune)).getHealth() - max(0,AltAttack-Defense/2);
                    this->rep.getByID(atoi(optiune)).setHealth(h);
                    battle[size-6] = "Viata: "+to_string(this->rep.getByID(atoi(optiune)).getHealth())+"          Viata: "+to_string(Health);
                    for (int i=0;i<size;i++) cout<<battle[i]<<endl;
                    cout<<endl<<endl;
                    Sleep(1000);
                    yourTurn = true;
                    enemyDefend = true;
                    atacInamic = randomnumber(0,8)%3;
                    battle[size-2] = "Atacul urmator al inamicului: "+attacks[atacInamic];
                    battle[size-1] = "Tura ta";
                }
            }
        }
        else if (Health<=0)
            {
                if (GetAsyncKeyState(VK_ESCAPE))
                {
                    if (nr!=3)
                    {
                        string type = "Execution"+to_string(nr)+".txt";
                        system("cls");
                        ifstream f(type);
                        int i=0;
                        while(getline(f,battle[i])) i++;
                        size = i;
                        for (i=0;i<size;i++) cout<<battle[i]<<endl;
                        this->rep.addScore(nr*50000);
                        system("pause");
                        t=false;
                        PlaySound(0,0,0);
                        return -1;
                    }
                    else
                    {
                        string type = "Execution3_1.txt";
                        system("cls");
                        ifstream f(type);
                        int i=0;
                        while(getline(f,battle[i])) i++;
                        size = i;
                        for (i=0;i<size;i++) cout<<battle[i]<<endl;
                        this->rep.addScore(nr*50000);
                        QTE = true;
                        PlaySound(TEXT("RULESOFNATURE2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                        t=false;
                    }
                }
                Sleep(200);
                system("cls");
                for (int i=0;i<size;i++) cout<<battle[i]<<endl;
                cout<<endl<<endl;
                cout<<"Esc. Execution\n";
            }
        else
        {
            system("cls");
            cout<<"Ai murit!"<<endl;
            system("pause");
            t=false;
            PlaySound(0,0,0);
            return -1;
        }
    }
    Sleep(1500);
    PlaySound(TEXT("RULESOFNATURE3.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    while(QTE)
    {
        if (state==0) {cout<<"--Space--"; state=1;}
        if (state==1)
        {
            if (GetAsyncKeyState(VK_SPACE)) qte--;
            if (qte<=0)
            {
                string type = "Execution3_2.txt";
                system("cls");
                ifstream f(type);
                int i=0;
                while(getline(f,battle[i])) i++;
                size = i;
                for (i=0;i<size;i++) cout<<battle[i]<<endl;
                qte=20; state=2; cout<<endl<<endl<<endl<<"--Ctrl--";
            }
            Sleep(100);
        }
        if (state==2)
        {
            if (GetAsyncKeyState(VK_CONTROL)) qte--;
            if (qte<=0)
            {
                string type = "Execution3_3.txt";
                system("cls");
                ifstream f(type);
                int i=0;
                while(getline(f,battle[i])) i++;
                size = i;
                for (i=0;i<size;i++) cout<<battle[i]<<endl;
                state=3;
            }
            Sleep(100);
        }
        if (state==3)
        {
            Sleep(2000);
            if (qte<=0)
            {
                string type = "Execution3_4.txt";
                system("cls");
                ifstream f(type);
                int i=0;
                while(getline(f,battle[i])) i++;
                size = i;
                for (i=0;i<size;i++) cout<<battle[i]<<endl;
                state=4;
                QTE=false;
                system("pause");
                PlaySound(0,0,0);
            }
        }
    }
}

void Service::inventar()
{
    cout<<endl<<"-----INVENTAR-----\n"<<"BP ramase: "<<this->rep.getScore()<<endl;
    cout<<"Potiuni de viata ramase: "<<this->rep.getHP()<<endl;
}

void Service::adauga(Player &p)
{
    this->rep.adauga(p);
}

void Service::sterge(int n)
{
    this->rep.sterge(n);
}

void Service::clearPlayer()
{
    for (int i=0;i<this->rep.getSize();i++)
        if (this->rep.getByID(i+1).getHealth()<=0)
            {this->rep.sterge(i+1); i=0;}
}

Player Service::getByID(int n)
{
    return this->rep.getByID(n);
}

void Service::getAll()
{
    this->rep.getAll();
}

int Service::getSize()
{
    return this->rep.getSize();
}
