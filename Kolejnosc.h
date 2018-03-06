/*
 * Kolejnosc.h
 *
 *  Created on: 05.03.2018
 *      Author: robert
 */

#ifndef KOLEJNOSC_H_
#define KOLEJNOSC_H_

#include "DList.h"

using namespace std;

typedef struct{
	int id;
	int czas_zak;
} dane_zadania;

class Kolejnosc{

public:
	Kolejnosc();
	~Kolejnosc();

	DList<dane_zadania>& GetKolejnosc();

	void WyswietlKolejnosc() const;
	void WyswietlCzasy() const;

	int MaxCzas() const;
	void Reset();
private:
	DList<dane_zadania> _kolejnosc;
};

#endif /* KOLEJNOSC_H_ */
