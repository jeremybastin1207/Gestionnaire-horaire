#ifndef LISTE
#define LISTE

#include <stdlib.h>
#include <iostream>

using namespace std;
template <class type> class Iterateur;
template <class type> struct Cellule
{
	type val;
	Cellule<type> *pNext;
};

template <class type> class Liste
{
protected:
	Cellule<type> *pStart;

public:
	Liste();
	Liste(const Liste&);
	~Liste();

	void Affiche() const;
	bool estVide();
	bool existe(type&);
	void truncate();
	virtual type* insere(const type&) = 0;

	Cellule<type>* getStartElement() const;
	int getNombreElements() const;

	Liste<type>& operator=(const Liste<type>&);

	friend class Iterateur<type>;
};
#endif