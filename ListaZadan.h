/*
 * ListaZadan.h
 *
 *  Created on: 05.03.2018
 *      Author: robert
 */

#ifndef LISTAZADAN_H_
#define LISTAZADAN_H_

#include "Zadanie.h"
#include "Kolejnosc.h"


using namespace std;

class ListaZadan{
public:
	ListaZadan(const char* sciezka);
	ListaZadan(const ListaZadan &lista);
	~ListaZadan();

	int GetIlosc() const;
	Zadanie* GetZadania() const;
	Kolejnosc& GetKolejnosc();

	Zadanie& operator[](int index);
	const Zadanie& operator[](int index) const;
	ListaZadan& operator=(const ListaZadan &lista);

	void WyswietlListe() const;
	int Schrage();
	int SchragePmt();
	int Carlier();
	int CarlierMod(int& opt_czas);

private:
	int _ilosc;
	Zadanie* _zadania;
	Kolejnosc _kolejnosc;
	int _WyznaczA(int b);
	int _WyznaczB();
	int _WyznaczC(int a, int b);
	void _Carlier(ListaZadan& Optymalna, int& _Cmax, int& UB);
	void _CarlierMod(ListaZadan& Optymalna, int& _Cmax, int& UB, int& opt_czas);
};

#endif /* LISTAZADAN_H_ */
