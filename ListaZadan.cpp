/*
 * ListaZadan.cpp
 *
 *  Created on: 05.03.2018
 *      Author: robert
 */

#include <iostream>
#include <fstream>
#include <queue>
#include <stdint.h>
#include "ListaZadan.h"
#include "Pomocnicze.h"
#include "Kolejnosc.h"

using namespace std;

struct porMax{
	bool operator()(const Zadanie& a, const Zadanie& b){
		return (a.GetQ()) < (b.GetQ());
	}
};

struct porMin{
	bool operator()(const Zadanie& a, const Zadanie& b){
		return (a.GetR()) > (b.GetR());
	}
};

/* ------------------------------------------------------------------------- */
/* ----------------------- Konstruktory/Destruktory ------------------------ */
/* ------------------------------------------------------------------------- */

ListaZadan::ListaZadan(const char* sciezka){
	ifstream Plik;
	Plik.open(sciezka);
	if(Plik.good()){
		//cout << "Poprawnie wczytano dane." << endl;

		Plik >> _ilosc;
		_zadania = new Zadanie[_ilosc];

		for (int i = 0; i < _ilosc; ++i) {
			int tmp;
			_zadania[i].SetId(i + 1);
			Plik >> tmp;	_zadania[i].SetR(tmp);
			Plik >> tmp;	_zadania[i].SetP(tmp);
			Plik >> tmp;	_zadania[i].SetQ(tmp);
		}
	}
	else{
		//cout << "Blad wczytywania danych" << endl;
	}
}

ListaZadan::ListaZadan(const ListaZadan &lista){
	_ilosc = lista.GetIlosc();
	_zadania = new Zadanie[_ilosc];

	for(int i = 0; i < _ilosc; ++i){
		_zadania[i] = lista[i];
	}

	_kolejnosc.GetKolejnosc().Remove();
	const ListaZadan* lista_const_w = &lista;
	Kolejnosc* kolejnosc_w = &((const_cast<ListaZadan*>(lista_const_w))->GetKolejnosc());

	DNode<dane_zadania>* DNlista = kolejnosc_w->GetKolejnosc().GetFirst();
	while(DNlista != NULL){
		_kolejnosc.GetKolejnosc().AddBack(DNlista->GetVal());
		DNlista = DNlista->GetNext();
	}

}

ListaZadan::~ListaZadan(){
	delete[] _zadania;
}

/* ------------------------------------------------------------------------- */
/* ---------------------------- Getery/Setery ------------------------------ */
/* ------------------------------------------------------------------------- */

int ListaZadan::GetIlosc() const{
	return _ilosc;
}

Zadanie* ListaZadan::GetZadania() const{
	return _zadania;
}

Kolejnosc& ListaZadan::GetKolejnosc(){
	return _kolejnosc;
}

/* ------------------------------------------------------------------------- */
/* ------------------------ Przecišżenia operatorów ------------------------ */
/* ------------------------------------------------------------------------- */

Zadanie& ListaZadan::operator[](int index){
	return _zadania[index];
}

const Zadanie& ListaZadan::operator[](int index) const{
	return _zadania[index];
}

ListaZadan& ListaZadan::operator=(const ListaZadan &lista){
	delete[] _zadania;

	_ilosc = lista.GetIlosc();
	_zadania = new Zadanie[_ilosc];

	for(int i = 0; i < _ilosc; ++i){
		_zadania[i] = lista[i];
	}

	_kolejnosc.GetKolejnosc().Remove();
	const ListaZadan* lista_const_w = &lista;
	Kolejnosc* kolejnosc_w = &((const_cast<ListaZadan*>(lista_const_w))->GetKolejnosc());

	DNode<dane_zadania>* DNlista = kolejnosc_w->GetKolejnosc().GetFirst();
	while (DNlista != NULL) {
		_kolejnosc.GetKolejnosc().AddBack(DNlista->GetVal());
		DNlista = DNlista->GetNext();
	}

	return *this;
}

/* ------------------------------------------------------------------------- */
/* ------------------------- Metody publiczne ------------------------------ */
/* ------------------------------------------------------------------------- */

void ListaZadan::WyswietlListe() const{
	cout << "Id\tCzas oczekiwania\tCzas wykonania\t\tCzas stygniecia" << endl;
	for (int i = 0; i < _ilosc; ++i){
			cout << _zadania[i].GetId() << "\t" << _zadania[i].GetR() << "\t\t\t" << _zadania[i].GetP()
				<< "\t\t\t" << _zadania[i].GetQ() << endl;
	}
}

int ListaZadan::Schrage(){
	_kolejnosc.Reset();
	priority_queue <Zadanie, vector<Zadanie>, porMin> Niegotowe;
	priority_queue <Zadanie, vector<Zadanie>, porMax> Gotowe;
	Zadanie j;

	int t = _zadania[0].GetR();
	for(int j = 0; j < _ilosc; ++j){
		Niegotowe.push(_zadania[j]);
		if(_zadania[j].GetR() < t) t = _zadania[j].GetR();
	}

	while(!Gotowe.empty() || !Niegotowe.empty()){
		while(!Niegotowe.empty() && (Niegotowe.top()).GetR() <= t){
			j = Niegotowe.top(); Niegotowe.pop();
			Gotowe.push(j);
		}
		if(Gotowe.empty()){
			t = (Niegotowe.top()).GetR();
		}
		else{
			j = Gotowe.top();
			Gotowe.pop();
			t += j.GetP();

			dane_zadania tmp;
			tmp.id = j.GetId();
			tmp.czas_zak = t + j.GetQ();
			_kolejnosc.GetKolejnosc().AddBack(tmp);

		}
	}
	return _kolejnosc.MaxCzas();
}

int ListaZadan::SchragePmt(){

	_kolejnosc.Reset();
	priority_queue <Zadanie, vector<Zadanie>, porMin> Niegotowe;
	priority_queue <Zadanie, vector<Zadanie>, porMax> Gotowe;

	int t = 0;
	int Cmax = 0;
	Zadanie j;
	int l = 0;
	int pomin = 0;

	for (int j = 0; j < _ilosc; ++j) {
		Niegotowe.push(_zadania[j]);
	}

	while (!Gotowe.empty() || !Niegotowe.empty()) {
		while (!Niegotowe.empty() && (Niegotowe.top()).GetR() <= t) {
			j = Niegotowe.top(); Niegotowe.pop();
			Gotowe.push(j);

			if(j.GetQ() > _zadania[l].GetQ() && pomin){
				_zadania[l].SetP(t - j.GetR());
				t = j.GetR();
				if (_zadania[l].GetP() > 0) {
					Gotowe.push(_zadania[l]);
				}
			}
		}
		pomin = 1;
		if(Gotowe.empty()){
			t = (Niegotowe.top()).GetR();
		}
		else{
			j = Gotowe.top(); Gotowe.pop();
			dane_zadania tmp;
			tmp.id = j.GetId();
			tmp.czas_zak = t + j.GetP() + j.GetQ();
			_kolejnosc.GetKolejnosc().AddBack(tmp);

			l = j.GetId() - 1;
			t += j.GetP();
			Cmax = max(Cmax, t + j.GetQ());
		}
	}
	return Cmax;
}

void ListaZadan::_Carlier(ListaZadan& Optymalna, int& _Cmax, int& UB){
	ListaZadan Kopia = *this;
	int indA;
	int indB;
	int indC;
	int _rK = INT32_MAX; int _qK = INT32_MAX;
	int _rC = INT32_MAX; int _qC = INT32_MAX;
	int _pK = 0; int _pC = 0;
	int rP, qP;
	int LB;
	int i;

	int U = Schrage();
	if(U < UB){
		UB = U;
		if(U < _Cmax){
			_Cmax = min(_Cmax, U);
			cout << _Cmax << endl;
			Optymalna = *this;
		}
	}
	indB = _WyznaczB();
	indA = _WyznaczA(indB);
	indC = _WyznaczC(indA, indB);

	if(indC == -1){
		return;
	}

	_pK = 0; _rK = INT32_MAX; _qK = INT32_MAX;
	DNode<dane_zadania>* ij = _kolejnosc.GetKolejnosc().GetFirst();
	while(ij->GetVal().id != _zadania[indC].GetId()){
		ij = ij->GetNext();
	}
	ij = ij->GetNext();
	while(ij->GetVal().id != _zadania[indB].GetId()){
		i = ij->GetVal().id - 1;
		_rK = min(_zadania[i].GetR(), _rK);
		_qK = min(_zadania[i].GetQ(), _qK);
		_pK += _zadania[i].GetP();
		ij = ij->GetNext();
	}
	i = ij->GetVal().id - 1;
	_rK = min(_zadania[i].GetR(), _rK);
	_qK = min(_zadania[i].GetQ(), _qK);
	_pK += _zadania[i].GetP();

	rP = GetZadania()[indC].GetR();
	GetZadania()[indC].SetR(max(rP, _rK + _pK));

	Kopia = *this;
	LB = SchragePmt();
	*this = Kopia;

	_pC = 0; _rC = INT32_MAX; _qC = INT32_MAX;
	ij = _kolejnosc.GetKolejnosc().GetFirst();
	while (ij->GetVal().id != _zadania[indC].GetId()) ij = ij->GetNext();
	while (ij->GetVal().id != _zadania[indB].GetId()){
		i = ij->GetVal().id - 1;
		_rC = min(_zadania[i].GetR(), _rC);
		_qC = min(_zadania[i].GetQ(), _qC);
		_pC += _zadania[i].GetP();
		ij = ij->GetNext();
	}
	i = ij->GetVal().id - 1;
	_rC = min(_zadania[i].GetR(), _rC);
	_qC = min(_zadania[i].GetQ(), _qC);
	_pC += _zadania[i].GetP();

	LB = max(_rK + _pK + _qK, max(_rC + _qC + _pC, LB));
	if(LB < UB){
		Kopia = *this;
		_Carlier(Optymalna, _Cmax, UB);
		*this = Kopia;
	}
	GetZadania()[indC].SetR(rP);

	qP = GetZadania()[indC].GetQ();
	GetZadania()[indC].SetQ(max(qP, _qK + _pK));
	Kopia = *this;
	LB = SchragePmt();
	*this = Kopia;

	_pC = 0; _rC = INT32_MAX; _qC = INT32_MAX;
	ij = _kolejnosc.GetKolejnosc().GetFirst();
	while (ij->GetVal().id != _zadania[indC].GetId()) ij = ij->GetNext();
	ij = ij->GetNext();
	while (ij->GetVal().id != _zadania[indB].GetId()){
		i = ij->GetVal().id - 1;
		_rC = min(_zadania[i].GetR(), _rC);
		_qC = min(_zadania[i].GetQ(), _qC);
		_pC += _zadania[i].GetP();
		ij = ij->GetNext();
	}
	i = ij->GetVal().id - 1;
	_rC = min(_zadania[i].GetR(), _rC);
	_qC = min(_zadania[i].GetQ(), _qC);
	_pC += _zadania[i].GetP();

	LB = max(_rK + _pK + _qK, max(_rC + _qC + _pC, LB));

	if(LB < UB){

		Kopia = *this;
		_Carlier(Optymalna, _Cmax, UB);
		*this = Kopia;
	}
	GetZadania()[indC].SetQ(qP);
}

int ListaZadan::Carlier(){
	ListaZadan Optymalna = *this;
	int Cmax = INT32_MAX;
	int UB = INT32_MAX;

	_Carlier(Optymalna, Cmax, UB);
	*this = Optymalna;
	return Optymalna.GetKolejnosc().MaxCzas();
}


void ListaZadan::_CarlierMod(ListaZadan& Optymalna, int& _Cmax, int& UB, int& opt_czas){
	if(_Cmax == opt_czas){
		cout << "mam" << endl;
		return;
	}
	ListaZadan Kopia = *this;
	int indA;
	int indB;
	int indC;
	int _rK = INT32_MAX; int _qK = INT32_MAX;
	int _rC = INT32_MAX; int _qC = INT32_MAX;
	int _pK = 0; int _pC = 0;
	int rP, qP;
	int LB;
	int i;

	int U = Schrage();
	if(U < UB){
		UB = U;
		if(U < _Cmax){
			_Cmax = min(_Cmax, U);
			Optymalna = *this;
			if(_Cmax == opt_czas) return;
		}
	}
	indB = _WyznaczB();
	indA = _WyznaczA(indB);
	indC = _WyznaczC(indA, indB);

	if(indC == -1){
		return;
	}

	_pK = 0; _rK = INT32_MAX; _qK = INT32_MAX;
	DNode<dane_zadania>* ij = _kolejnosc.GetKolejnosc().GetFirst();
	while(ij->GetVal().id != _zadania[indC].GetId()){
		ij = ij->GetNext();
	}
	ij = ij->GetNext();
	while(ij->GetVal().id != _zadania[indB].GetId()){
		i = ij->GetVal().id - 1;
		_rK = min(_zadania[i].GetR(), _rK);
		_qK = min(_zadania[i].GetQ(), _qK);
		_pK += _zadania[i].GetP();
		ij = ij->GetNext();
	}
	i = ij->GetVal().id - 1;
	_rK = min(_zadania[i].GetR(), _rK);
	_qK = min(_zadania[i].GetQ(), _qK);
	_pK += _zadania[i].GetP();

	rP = GetZadania()[indC].GetR();
	GetZadania()[indC].SetR(max(rP, _rK + _pK));

	Kopia = *this;
	LB = SchragePmt();
	*this = Kopia;

	_pC = 0; _rC = INT32_MAX; _qC = INT32_MAX;
	ij = _kolejnosc.GetKolejnosc().GetFirst();
	while (ij->GetVal().id != _zadania[indC].GetId()) ij = ij->GetNext();
	while (ij->GetVal().id != _zadania[indB].GetId()){
		i = ij->GetVal().id - 1;
		_rC = min(_zadania[i].GetR(), _rC);
		_qC = min(_zadania[i].GetQ(), _qC);
		_pC += _zadania[i].GetP();
		ij = ij->GetNext();
	}
	i = ij->GetVal().id - 1;
	_rC = min(_zadania[i].GetR(), _rC);
	_qC = min(_zadania[i].GetQ(), _qC);
	_pC += _zadania[i].GetP();

	LB = max(_rK + _pK + _qK, max(_rC + _qC + _pC, LB));
	if(LB < UB){
		Kopia = *this;
		_CarlierMod(Optymalna, _Cmax, UB, opt_czas);
		if(_Cmax == opt_czas) return;
		*this = Kopia;
	}
	GetZadania()[indC].SetR(rP);

	qP = GetZadania()[indC].GetQ();
	GetZadania()[indC].SetQ(max(qP, _qK + _pK));
	Kopia = *this;
	LB = SchragePmt();
	*this = Kopia;

	_pC = 0; _rC = INT32_MAX; _qC = INT32_MAX;
	ij = _kolejnosc.GetKolejnosc().GetFirst();
	while (ij->GetVal().id != _zadania[indC].GetId()) ij = ij->GetNext();
	ij = ij->GetNext();
	while (ij->GetVal().id != _zadania[indB].GetId()){
		i = ij->GetVal().id - 1;
		_rC = min(_zadania[i].GetR(), _rC);
		_qC = min(_zadania[i].GetQ(), _qC);
		_pC += _zadania[i].GetP();
		ij = ij->GetNext();
	}
	i = ij->GetVal().id - 1;
	_rC = min(_zadania[i].GetR(), _rC);
	_qC = min(_zadania[i].GetQ(), _qC);
	_pC += _zadania[i].GetP();

	LB = max(_rK + _pK + _qK, max(_rC + _qC + _pC, LB));

	if(LB < UB){

		Kopia = *this;
		_CarlierMod(Optymalna, _Cmax, UB, opt_czas);
		if(_Cmax == opt_czas) return;
		*this = Kopia;
	}
	GetZadania()[indC].SetQ(qP);
}

int ListaZadan::CarlierMod(int& opt_czas) {
	ListaZadan Optymalna = *this;
	int Cmax = INT32_MAX;
	int UB = INT32_MAX;

	_CarlierMod(Optymalna, Cmax, UB, opt_czas);
	*this = Optymalna;
	return Optymalna.GetKolejnosc().MaxCzas();
}


int ListaZadan::_WyznaczA(int b){
	int rj, ps, qb;
	qb = _zadania[b].GetQ();
	int Cmax = _kolejnosc.MaxCzas();
	int suma;
	int j; int s;
	DNode<dane_zadania>* ij = _kolejnosc.GetKolejnosc().GetFirst();
	while(ij != NULL){
		j = ij->GetVal().id - 1;
		rj = _zadania[j].GetR();
		ps = 0;
		DNode<dane_zadania>* is = ij;
		while (is->GetVal().id - 1 != b){
			s = is->GetVal().id - 1;
			ps += _zadania[s].GetP();
			is = is->GetNext();
		}
		s = is->GetVal().id - 1;
		ps += _zadania[s].GetP();
		ij = ij->GetNext();
		suma = rj + ps + qb;
		if (Cmax == suma) {
			return j;
		}
	}
	return -1;
}

int ListaZadan::_WyznaczB(){
	int Cmax = _kolejnosc.MaxCzas();
	DNode<dane_zadania>* tmp = _kolejnosc.GetKolejnosc().GetLast();
	while(tmp->GetPrev() != NULL){
		if (Cmax == tmp->GetVal().czas_zak){
			return tmp->GetVal().id - 1;
		}
		tmp = tmp->GetPrev();
	}
	return -1;
}

int ListaZadan::_WyznaczC(int a, int b){
	int c = -1;
	int i;
	DNode<dane_zadania>* ij = _kolejnosc.GetKolejnosc().GetFirst();
	while(ij->GetVal().id != _zadania[a].GetId()) ij = ij->GetNext();
	while(ij->GetVal().id != _zadania[b].GetId()){
		i = ij->GetVal().id - 1;
		if(_zadania[i].GetQ() < _zadania[b].GetQ()){
			c = i;
		}
		ij = ij->GetNext();
	}
	i = ij->GetVal().id - 1;
	if(_zadania[i].GetQ() < _zadania[b].GetQ()){
		c = i;
	}
	return c;

}

