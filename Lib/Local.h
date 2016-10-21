#ifndef LOCAL
#define LOCAL
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Planifiable.h"
#include "stdio.h"

class Local : public Planifiable
{
private:
	char *nom;
	int nbPlaces;
public:
	Local();
	Local(const char *,const int);
	Local(const Local&);
	~Local();
	
	const void Affiche();
	void Save(std::ofstream& ofs);
	void Load(std::ifstream& ifs);

	void setNom(const char*);
	void setNbPlaces(const int);

	char* getIdentifiant();
	const char* getNom() const;
	const int getNbPlaces() const;

	int operator<(const Local&);
	int operator>(const Local&);
	int operator==(const Local&);
	Local& operator=(const Local&);

	friend ostream& operator<<(ostream&, Local&);
	friend istream& operator>>(istream&, Local&);

};
#endif