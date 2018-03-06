/*
 * Zadanie.h
 *
 *  Created on: 05.03.2018
 *      Author: robert
 */

#ifndef ZADANIE_H_
#define ZADANIE_H_

class Zadanie {
public:
	Zadanie();
	virtual ~Zadanie();

	void SetR(const int r);
	int GetR() const;
	void SetP(const int p);
	int GetP() const;
	void SetQ(const int q);
	int GetQ() const;
	void SetId(const int id);
	int GetId() const;
private:
	int _id;
	int _r;
	int _p;
	int _q;
};


#endif /* ZADANIE_H_ */
