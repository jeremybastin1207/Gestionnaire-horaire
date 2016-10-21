#ifndef COURS
#define COURS
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Event.h"
#include "Professeur.h"
#include "Local.h"
#include "Groupe.h"
#include "ListeTriee.h"
#include "Iterateur.h"

using namespace std;

class Cours : public Event
{
private:
	char* professeur;
	ListeTriee<char*> groupes;
public:
	Cours();
	Cours(const Cours& c);
	~Cours();

	void Save(std::ofstream& ofs);
	void Load(std::ifstream& ifs);

	void Affiche() const;
	void insereGroupe(char*);
	void setProfesseur(const char*);
	void setGroupes(const ListeTriee<char*>&);

	char* getProfesseur() const;
	const ListeTriee<char*>& getGroupes() const;

	int operator<(const Cours&);
	int operator>(const Cours&);
	int operator==(const Cours&);
	Cours& operator=(const Cours&);
	
	friend istream& operator>>(istream&, Cours&);
	friend ostream& operator<<(ostream&, const Cours&);
};



#endif
