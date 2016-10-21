#ifndef PLANIFIABLE
#define PLANIFIABLE

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "ListeTriee.h"
#include "SmartPointer.h"

class Cours;

using namespace std;

class Planifiable
{

protected:
	char type;
	ListeTriee<SmartPointer<Cours> > cours;

public:	
	Planifiable();
	Planifiable(const Planifiable&);
	~Planifiable();

	const void Affiche();
	virtual char* getIdentifiant() = 0;

	bool PossedeCours();
	void AjouterCours(Cours*);
	void SupprimerCours(Cours*);

	const ListeTriee<SmartPointer<Cours> >& getCours() const;
	char getType() const;
	void setType(const char);

	Planifiable& operator=(const Planifiable&);
};

#endif