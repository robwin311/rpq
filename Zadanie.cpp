/*
 * Zadanie.cpp
 *
 *  Created on: 05.03.2018
 *      Author: robert
 */

#include "Zadanie.h"

/* ------------------------------------------------------------------------- */
/* ----------------------- Konstruktory/Destruktory ------------------------ */
/* ------------------------------------------------------------------------- */

Zadanie::Zadanie(){
}

Zadanie::~Zadanie() {
}

/* ------------------------------------------------------------------------- */
/* ---------------------------- Getery/Setery ------------------------------ */
/* ------------------------------------------------------------------------- */

void Zadanie::SetR(const int r) {
	_r = r;
}

int Zadanie::GetR() const {
	return _r;
}

void Zadanie::SetP(const int p) {
	_p = p;
}

int Zadanie::GetP() const {
	return _p;
}

void Zadanie::SetQ(const int q) {
	_q = q;
}

int Zadanie::GetQ() const {
	return _q;
}

void Zadanie::SetId(const int id) {
	_id = id;
}

int Zadanie::GetId() const {
	return _id;
}
