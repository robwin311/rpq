/*
 * DNode.h
 *
 *  Created on: 05.03.2018
 *      Author: robert
 */

#ifndef DNODE_H_
#define DNODE_H_

#include <iostream>
using namespace std;

template <typename T>
class DNode {
public:
	DNode();
	DNode(T Val, int Key, DNode<T>* Prev = NULL, DNode<T>* Next = NULL);
	virtual ~DNode();

	int GetKey()const;
	void SetKey(int Key);
	void SetVal(const T &Ptr);
	const T& GetVal()const;
	void SetNext(DNode<T>* Next);
	DNode<T>* GetNext()const;
	void SetPrev(DNode<T>* Prev);
	DNode<T>* GetPrev()const;
	void Display()const;      // Funkcja pomocnicza służšca sprawdzeniu implementacji.

private:
	DNode<T>* _Prev;
	T _Val;
	int _Key;
	DNode<T> *_Next;
};

/* ------------------------------------------------------------------------- */
/* ----------------------- Konstruktory/Destruktory ------------------------ */
/* ------------------------------------------------------------------------- */

template <typename T>
DNode<T>::DNode() :_Prev(NULL), _Val(0), _Key(0), _Next(NULL) {
	// Opis: Konstruktor bezparametryczny.
	// IN: Brak.
	// OUT: Pole _Prev i _Next zainicjalizowane wskanikiem na NULL
	// OUT: Pole _Key i _Val zainicjalizowane zerem.
}

template <typename T>
DNode<T>::DNode(T Val, int Key, DNode<T>* Prev, DNode<T>* Next) {
	// Opis: Konstruktor klasy Node.
	// IN: Val, Key, Prev, Next służš do inicjalizacji odpowiadajšcych pól klasy Node.
	// OUT: Pola _Val, _Key, _Prev, _Next zainicjalizowane odpowiadajšcymi wartociami
	//      przekazanymi w paramtetrach metody.
	_Prev = Prev;
	_Val = Val;
	_Key = Key;
	_Next = Next;
}

template <typename T>
DNode<T>::~DNode() {
	// Opis: Destruktor klasy Node.
	// IN: Brak.
	// OUT: Brak.
}

/* ------------------------------------------------------------------------- */
/* ----------------------------- Getery / Setery --------------------------- */
/* ------------------------------------------------------------------------- */

template <typename T>
void DNode<T>::SetKey(int Key) {
	// Opis: Seter pola Key.
	// IN: Key - wartoć dla pola _Key.
	// OUT: Pole _Key przyjmuje wartoć Key.
	_Key = Key;
}

template <typename T>
int DNode<T>::GetKey()const {
	// Opis: Geter pola Key.
	// IN: Brak.
	// RETURN: Wartoć pola _Key.
	return _Key;
}

template <typename T>
void DNode<T>::SetVal(const T& Val) {
	// Opis: Seter pola _Val.
	// IN: Val - wartoć dla pola _Val.
	// OUT: Pole _Val przyjmuje wartoć Val.
	_Val = Val;
}

template <typename T>
const T& DNode<T>::GetVal()const {
	// Opis: Geter pola _Val.
	// IN: Brak.
	// RETURN: Wartoć pola _Val.
	return _Val;
}

template <typename T>
void DNode<T>::SetNext(DNode<T>* Next) {
	// Opis: Seter pola Next.
	// IN: Next - wartoć dla pola _Next.
	// OUT: Pole _Next przyjmuje wartoć Next.
	_Next = Next;
}

template <typename T>
DNode<T>* DNode<T>::GetNext()const {
	// Opis: Geter pola Next.
	// IN: Brak.
	// RETURN: Wartoć pola _Next.
	return _Next;
}

template <typename T>
void DNode<T>::SetPrev(DNode<T>* Prev) {
	// Opis: Seter pola Prev.
	// IN: Prev - wartoć dla pola _Prev.
	// OUT: Pole _Prev przyjmuje wartoć Prev.
	_Prev = Prev;
}

template <typename T>
DNode<T>* DNode<T>::GetPrev()const {
	// Opis: Geter pola Prev.
	// IN: Brak.
	// RETURN: Wartoć pola Prev.
	return _Prev;
}

/* ------------------------------------------------------------------------- */
/* ------------------------------ Metody Node ------------------------------ */
/* ------------------------------------------------------------------------- */


template <typename T>
void DNode<T>::Display()const { // Funkcja pomocnicza wywietlajšca węzeł.
	cout << "[";
	if (_Prev != NULL) cout << "FULL";
	else cout << "NULL";
	cout << "|" << _Val << "|";
	if (_Next != NULL) cout << "FULL";
	else cout << "NULL";
	cout << "]";
}

#endif /* DNODE_H_ */
