#ifndef GROUPE
#define GROUPE
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Planifiable.h"
#include <stdio.h>

class Groupe : public Planifiable
{
private:
	char* categorie;
	int niveau;
	int numero;
public:
	Groupe();
	Groupe(char*, int, int);
	Groupe(const Groupe&);
	~Groupe();

	const void Affiche();
	void Save(std::ofstream& ofs);
	void Load(std::ifstream& ifs);

	void setCategorie(const char*);
	void setNiveau(int);
	void setNumero(int);

	char* getCategorie() const;
	int getNiveau() const;
	int getNumero() const;
	char* getIdentifiant();

	int operator<(const Groupe&);
	int operator>(const Groupe&);
	int operator==(const Groupe&);
	Groupe& operator=(const Groupe&);

	friend istream& operator>>(istream&, Groupe&);
	friend ostream& operator<<(ostream&, const Groupe&);
};
#endif