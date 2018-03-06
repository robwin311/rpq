/*
 * main.cpp
 *
 *  Created on: 05.03.2018
 *      Author: robert
 */

#include <iostream>
#include "ListaZadan.h"
#include "DList.h"

using namespace std;

int opt1 = 13862;
int opt2 = 20917;
int opt3 = 31343;
int opt4 = 33878;

int main(){

	ListaZadan Lista1("data1.txt");
	ListaZadan Lista2("data2.txt");
	ListaZadan Lista3("data3.txt");
	ListaZadan Lista4("data4.txt");

	Lista1.CarlierMod(opt1);
	cout << "Cmax: " << Lista1.GetKolejnosc().MaxCzas() << endl;
	Lista1.GetKolejnosc().WyswietlKolejnosc();
	Lista1.GetKolejnosc().WyswietlCzasy();
	cout << endl;

	Lista2.CarlierMod(opt2);
	cout << "Cmax: " << Lista2.GetKolejnosc().MaxCzas() << endl;
	Lista2.GetKolejnosc().WyswietlKolejnosc();
	Lista2.GetKolejnosc().WyswietlCzasy();
	cout << endl;

	Lista3.CarlierMod(opt3);
	cout << "Cmax: " << Lista3.GetKolejnosc().MaxCzas() << endl;
	Lista3.GetKolejnosc().WyswietlKolejnosc();
	Lista3.GetKolejnosc().WyswietlCzasy();
	cout << endl;

	Lista4.CarlierMod(opt4);
	cout << "Cmax: " << Lista4.GetKolejnosc().MaxCzas() << endl;
	Lista4.GetKolejnosc().WyswietlKolejnosc();
	Lista4.GetKolejnosc().WyswietlCzasy();
	cout << endl;

	cout << "Suma czasów: " << Lista1.GetKolejnosc().MaxCzas() + Lista2.GetKolejnosc().MaxCzas() + Lista3.GetKolejnosc().MaxCzas() + Lista4.GetKolejnosc().MaxCzas() << endl;

	return 0;
}


