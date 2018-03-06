/*
 * DList.h
 *
 *  Created on: 05.03.2018
 *      Author: robert
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <iostream>
#include "DNode.h"

using namespace std;

class EmptyListException {
public:
	void Informacje()const {
		cerr << "Lista jest pusta!" << endl;
		cout << "Proszę najpierw wprowadzić co na listę" << endl;
	}
};

class NodeNotFoundListException {
public:
	void Informacje()const {
		cerr << "Nie znaleziono węzła na licie!" << endl;
		cout << "Proszę najpierw wprowadzić żšdanš wartoć na listę" << endl;
	}
};

template <typename T>
class DList {
public:
	DList();
	virtual ~DList();

	bool IsEmpty()const;
	const T& Front()const throw(EmptyListException);
	const T& Back()const throw(EmptyListException);
	void AddFront(const T& x);
	void AddBack(const T& x);
	void AddBefore(DNode<T>* n, const T& x) throw(NodeNotFoundListException);
	void AddAfter(DNode<T>* n, const T& x) throw(NodeNotFoundListException);
	void RemoveFront() throw(EmptyListException);
	void RemoveBack() throw(EmptyListException);
	void Remove();
	void RemoveNode(DNode<T>* x) throw(EmptyListException, NodeNotFoundListException);
	unsigned int Size()const;

	void DisplayFront()const;   // Metoda pomocnicza służšca sprawdzeniu implementacji.
	void DisplayBack()const;    // Metoda pomocnicza służšca sprawdzeniu implementacji.

	DNode<T>* GetFirst() const;
	DNode<T>* GetLast() const;
	void SetFirst(DNode<T>* x);
	void SetLast(DNode<T>* x);
private:
	DNode<T>* _First;
	DNode<T>* _Last;
};

/* ------------------------------------------------------------------------- */
/* ----------------------- Konstruktory/Destruktory ------------------------ */
/* ------------------------------------------------------------------------- */

template <typename T>
DList<T>::DList() :_First(NULL), _Last(NULL) {
	// Opis: Konstruktor bezparametryczny klasy DList.
	// IN: Brak.
	// OUT: Pola _First i _Last zainicjalizowane wskanikiem na NULL.
}

template <typename T>
DList<T>::~DList() {
	// Opis: Destruktor klasy DList.
	// IN: Brak.
	// OUT: Usuwa listę.
	if (!IsEmpty()) Remove();
}

/* ------------------------------------------------------------------------- */
/* ---------------------------- Getery/Setery ------------------------------ */
/* ------------------------------------------------------------------------- */

template <typename T>
DNode<T>* DList<T>::GetFirst() const {
	// Opis: Geter pola _First.
	// IN: Brak.
	// RETURN: Wartoć pol _First.
	return _First;
}

template <typename T>
void DList<T>::SetFirst(DNode<T>* x) {
	// Opis: Seter pola _First.
	// IN: First - wartoć dla pola _First.
	// OUT: Pole _First przyjmuje wartoć x.
	_First = x;
}

template <typename T>
DNode<T>* DList<T>::GetLast()const {
	// Opis: Geter pola _Last.
	// IN: Brak.
	// RETURN: Wartoć pola _Last.
	return _Last;
}

template <typename T>
void DList<T>::SetLast(DNode<T>* x) {
	// Opis: Seter pola _Last.
	// IN: x - wartoć dla pola _Last.
	// OUT: Pole _Last przyjmuje wartoć x.
	_Last = x;
}

/* ------------------------------------------------------------------------- */
/* -------------------------- Metody klasy DList --------------------------- */
/* ------------------------------------------------------------------------- */

template <typename T>
bool DList<T>::IsEmpty()const {
	// Opis: Metoda sprawdzajšca czy lista jest pusta.
	// IN: Brak.
	// RETURN: True jeżeli lista jest pusta / False jeżeli lista nie jest pusta.
	if (_First == NULL) return true;
	else return false;
}

template <typename T>
const T& DList<T>::Front()const throw(EmptyListException) {
	// Opis: Metoda zwracajšca referencję do pierwszego elementu listy.
	// IN: Brak.
	// RETURN: Referencja do pierwszego elementu listy.
	if (!IsEmpty()) return _First->GetVal();
	else throw EmptyListException();
}

template <typename T>
const T& DList<T>::Back()const throw(EmptyListException) {
	// Opis: Metoda zwracajšca referencję do ostatniego elementu listy.
	// IN: Brak.
	// RETURN: Referencja do ostatniego elementu listy.
	if (!IsEmpty()) return _Last->GetVal();
	else throw EmptyListException();
}

template <typename T>
void DList<T>::AddFront(const T& x) {
	// Opis: Metoda dodajšca element na poczštku listy.
	// IN: x - wartoć do dodania na poczštku listy.
	// OUT: Wartoć x dodana na poczštku listy.
	DNode<T>* tmp = new DNode<T>(x, NULL, NULL);
	if (!IsEmpty()) {
		tmp->SetNext(_First);
		_First->SetPrev(tmp);
	}
	else _Last = tmp;
	_First = tmp;
}

template <typename T>
void DList<T>::AddBack(const T& x) {
	// Opis: Metoda dodajšca element na konccu listy.
	// IN: x - wartoć do dodania na końccu listy.
	// OUT: Wartoć x dodana na konccu listy.
	DNode<T>* tmp = new DNode<T>(x, 0, NULL, NULL);
	if (!IsEmpty()) {
		tmp->SetPrev(_Last);
		_Last->SetNext(tmp);
	}
	else _First = tmp;
	_Last = tmp;
}

template <typename T>
void DList<T>::AddBefore(DNode<T>* n, const T& x) throw(NodeNotFoundListException) {
	// Opis: Metoda dodajšca wartoć na licie przed węzłem n.
	// IN: n - wskanik do węzła przed którym dodaje wartoć.
	// IN: x - wartoć do dodania przed węzłem n.
	// OUT: Wartoć x dodana przed węzłem n.
	if (!IsEmpty()) {
		DNode<T>* tmp = new DNode<T>(x, NULL, NULL);
		DNode<T>* i = _First;
		while (i != n) {
			i = i->GetNext();
			if (i == NULL) throw NodeNotFoundListException();
		}
		tmp->SetPrev(i->GetPrev());
		tmp->SetNext(i);
		if (i->GetPrev() != NULL) (i->GetPrev())->SetNext(tmp);
		else _First = tmp;
		i->SetPrev(tmp);
	}
	else throw NodeNotFoundListException();
}

template <typename T>
void DList<T>::AddAfter(DNode<T>* n, const T& x) throw(NodeNotFoundListException) {
	// Opis: Metoda dodajšca wartoć za węzłem n.
	// IN: n - wskanik do węzła za którym dodaje wartoć.
	// IN: x - wartoć do dodania za węzłem n.
	// OUT: Dodana wartoć x za wężłem n.
	if (!IsEmpty()) {
		DNode<T>* tmp = new DNode<T>(x, NULL, NULL);
		DNode<T>* i = _First;
		while (i != n) {
			i = i->GetNext();
			if (i == NULL) throw NodeNotFoundListException();
		}
		tmp->SetPrev(i);
		tmp->SetNext(i->GetNext());
		if (i->GetNext() != NULL) (i->GetNext())->SetPrev(tmp);
		else _Last = tmp;
		i->SetNext(tmp);
	}
	else throw NodeNotFoundListException();
}

template <typename T>
void DList<T>::RemoveFront() throw(EmptyListException) {
	// Opis: Metoda usuwajšca pierwszy element listy.
	// IN: Brak.
	// OUT: Usunięty pierwszy element listy.
	if (!IsEmpty()) {
		DNode<T>* tmp = _First;
		if (_First->GetNext() != NULL) {
			_First = _First->GetNext();
			_First->SetPrev(NULL);
		}
		else _First = NULL;
		delete tmp;
	}
	else throw EmptyListException();
}

template <typename T>
void DList<T>::RemoveBack() throw(EmptyListException) {
	// Opis: Metoda usuwajšca ostatni element listy.
	// IN: Brak.
	// OUT: Usunięty oststni element listy.
	if (!IsEmpty()) {
		DNode<T>* tmp = _Last;
		if (_Last->GetPrev() != NULL) {
			_Last = _Last->GetPrev();
			_Last->SetNext(NULL);
		}
		else _Last = NULL;
		delete tmp;
	}
	else throw EmptyListException();
}

template <typename T>
void DList<T>::Remove(){
	// Opis: Usuwa całš listę.
	// IN: Brak.
	// OUT: Usunięta cała lista. _First i _Last wskazujš na NULL.
	if(!IsEmpty()){
		DNode<T>* tmp = _First;
		DNode<T>* tmp2;
		while (tmp != NULL) {
			tmp2 = tmp;
			tmp = tmp->GetNext();
			delete tmp2;
		}
		_First = NULL;
		_Last = NULL;
	}
}

template <typename T>
void DList<T>::RemoveNode(DNode<T>* x) throw(EmptyListException, NodeNotFoundListException) {
	// Opis: Metoda usuwajšca węzeł x z listy.
	// IN: x - wskanik do węzła, który usuwa z listy.
	// OUT: Usunięty z listy węzeł x.
	if (!IsEmpty()) {
		DNode<T>* tmp = _First;
		while (tmp != x) {
			tmp = tmp->GetNext();
			if (tmp == NULL) throw NodeNotFoundListException();
		}
		if (tmp->GetNext() != NULL) (tmp->GetNext())->SetPrev(tmp->GetPrev());
		else _Last = tmp->GetPrev();
		if (tmp->GetPrev() != NULL) (tmp->GetPrev())->SetNext(tmp->GetNext());
		else _First = tmp->GetNext();
		delete tmp;
	}
	else throw EmptyListException();
}

template <typename T>
unsigned int DList<T>::Size()const {
	// Opis: Metoda wyywietlajšca iloć eementów w licie.
	// IN: Brak.
	// RETURN: Iloć elementów w licie.
	int i = 0;
	DNode<T>* tmp = _First;
	while (tmp != NULL) {
		++i;
		tmp = tmp->GetNext();
	}
	return i;
}

/* ------------------------------------------------------------------------- */
/* --------------------------- Metody pomocnicze --------------------------- */
/* ------------------------------------------------------------------------- */

template <typename T>
void DList<T>::DisplayFront()const {  // Wywietla liste od przodu
	if (IsEmpty()) cout << "LISTA PUSTA!" << endl;
	else {
		DNode<T>* tmp = _First;
		cout << "::FIRST::" << endl;
		unsigned int i = 1;
		while (tmp != NULL) {
			cout << i << ". \t";
			tmp->Display();
			cout << endl;
			tmp = tmp->GetNext();
			++i;
		}
		cout << "::LAST::" << endl;
	}
}

template <typename T>
void DList<T>::DisplayBack()const {  // Wywietla listę od tyłu
	if (IsEmpty()) cout << "LISTA PUSTA!" << endl;
	else {
		DNode<T>* tmp = _Last;
		cout << "::LAST::" << endl;
		unsigned int i = 1;
		while (tmp != NULL) {
			cout << i << ". \t";
			tmp->Display();
			cout << endl;
			tmp = tmp->GetPrev();
			++i;
		}
		cout << "::FIRST::" << endl;
	}
}




#endif /* DLIST_H_ */
