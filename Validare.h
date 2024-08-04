#ifndef VALIDARE_H_INCLUDED
#define VALIDARE_H_INCLUDED
#pragma once
using namespace std;

#endif

class Validare{
private:
	string message;
public:
	Validare(string m) : message(m){}
	string getMessage()
	{
		return message;
	}
};
