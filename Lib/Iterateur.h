#ifndef ITERATEUR_H
#define ITERATEUR_H

#include "ListeBase.h"
#include "Liste.h"
#include "ListeTriee.h"
#include <iostream>

template <class T>
class Iterateur
{
	protected:

	Liste<T>& liste;
	Cellule<T> *pPosition;
	Cellule<T> *pPrevious;

	public:

	Iterateur(Liste<T>& liste);

	void reset();
	T& get(int);
	bool end();
	T remove();

	void operator++(int);
	operator T() const;
	T* operator&();
};

#endif