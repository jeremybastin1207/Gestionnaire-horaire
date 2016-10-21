#ifndef PROFESSEUR
#define PROFESSEUR
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Planifiable.h"

class Professeur : public Planifiable
{
private:
	char *nom;
	char *prenom;
public:
	Professeur();
	Professeur(const char*, const char*);
	Professeur(const Professeur&);
	~Professeur();
	
	const void Affiche();
	void Save(std::ofstream& ofs);
	void Load(std::ifstream& ifs);

	void setNom(const char*);
	void setPrenom(const char*);
	
	char* getIdentifiant();
	char* getNom() const;
	char* getPrenom() const;

	int operator<(const Professeur&);
	int operator>(const Professeur&);
	int operator==(const Professeur&);
	Professeur& operator=(const Professeur&);
	
	friend ostream& operator<<(ostream&, Professeur&);
	friend istream& operator>>(istream&, Professeur&);
};
#endif