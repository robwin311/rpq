/*
 * Kolejnosc.cpp
 *
 *  Created on: 05.03.2018
 *      Author: robert
 */

#include "Kolejnosc.h"

#include "DList.h"
#include "DNode.h"
#include <iostream>
#include "Pomocnicze.h"

using namespace std;

/* ------------------------------------------------------------------------- */
/* ----------------------- Konstruktory/Destruktory ------------------------ */
/* ------------------------------------------------------------------------- */

Kolejnosc::Kolejnosc(){
}


Kolejnosc::~Kolejnosc(){
}

/* ------------------------------------------------------------------------- */
/* ---------------------------- Getery/Setery ------------------------------ */
/* ------------------------------------------------------------------------- */

DList<dane_zadania>& Kolejnosc::GetKolejnosc(){
	return _kolejnosc;
}

/* ------------------------------------------------------------------------- */
/* ----------------------------- Wyswietlanie ------------------------------ */
/* ------------------------------------------------------------------------- */

void Kolejnosc::WyswietlKolejnosc() const{
	cout << "Kolejnosc: " ;
	if(!_kolejnosc.IsEmpty()){
		DNode<dane_zadania>* tmp = _kolejnosc.GetFirst();
		while(tmp != NULL){
			cout << tmp->GetVal().id << " ";
			tmp = tmp->GetNext();
		}
		cout << endl;
	}
	else cout << "Najpierw uszereguj." << endl;
}

void Kolejnosc::WyswietlCzasy() const{
	cout << "Czasy: " ;
	if(!_kolejnosc.IsEmpty()){
		DNode<dane_zadania>* tmp = _kolejnosc.GetFirst();
		while(tmp != NULL){
			cout << tmp->GetVal().czas_zak << " ";
			tmp = tmp->GetNext();
		}
		cout << endl;
	}
	else cout << "Najpierw uszereguj" << endl;
}

int Kolejnosc::MaxCzas() const{
	int czas_max = 0;
	if(!_kolejnosc.IsEmpty()){
		DNode<dane_zadania>* tmp = _kolejnosc.GetFirst();
		while(tmp != NULL){
			czas_max = max(czas_max, tmp->GetVal().czas_zak);
			tmp = tmp->GetNext();
		}
		return czas_max;

	}
	else return 0;
}

void Kolejnosc::Reset(){
	_kolejnosc.Remove();
}
