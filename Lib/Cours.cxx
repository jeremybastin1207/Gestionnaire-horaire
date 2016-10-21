#include "Cours.h"

Cours::Cours() : Event()
{
	professeur = NULL;
	setProfesseur("");
}

Cours::Cours(const Cours& c) : Event(c)
{
	setProfesseur(c.getProfesseur());
	setGroupes(c.getGroupes());
}

Cours::~Cours()
{
	if(professeur) delete professeur;
}

void Cours::Save(ofstream& ofs)
{
	int length, i;
	char buffer[100];
	Iterateur<char*> itg(groupes);

	Event::Save(ofs);

	length = strlen(professeur) + 1;

	ofs.write((char*) &length, sizeof(int));
	ofs.write((char*) professeur, length);

	length = groupes.getNombreElements();

	ofs.write((char*) &length, sizeof(int));

	for (itg.reset() ; !itg.end() ; itg++)
	{
		strcpy(buffer, (char*) itg);
		length = strlen(buffer) + 1;

		ofs.write((char*) &length, sizeof(int));
		ofs.write(buffer, length);
	}
}

void Cours::Load(ifstream& ifs)
{
	int length, max, i, val;
	char buffer[100], *buffer2;

	Event::Load(ifs);

	ifs.read((char*) &length, sizeof(int));
	ifs.read((char*) buffer, length);

	setProfesseur(buffer);

	ifs.read((char*) &max, sizeof(int));
	
	for(i = 0 ; i < max ; i++)
	{
		ifs.read((char*) &length, sizeof(int));
		ifs.read(buffer, length);

		buffer2 = new char[strlen(buffer) + 1];

		strcpy(buffer2, buffer);

		insereGroupe(buffer2);
	}
}

void Cours::Affiche() const
{
	cout << "Code : " << getCode() << endl;;
	cout << "Intitule : " << getIntitule() << endl;
	cout << "Lieu : " << getLieu() << endl;
	cout << "Timing : " << endl << getTiming();
	cout << "Professeur : " << getProfesseur() << endl;
	cout << "Groupes : " << endl;
	getGroupes().Affiche();
}

void Cours::insereGroupe(char* g)
{
	groupes.insere(g);
}

void Cours::setProfesseur(const char* p)
{
	if(professeur) delete professeur;

	professeur = new char[strlen(p) + 1];

	strcpy(professeur, p);
}

void Cours::setGroupes(const ListeTriee<char*> &t)
{
	groupes = t;
}

char* Cours::getProfesseur() const
{
	return professeur;
}


const ListeTriee<char*>& Cours::getGroupes() const
{
	return groupes;
}

int Cours::operator<(const Cours& c)
{
	if(getTiming() < c.getTiming())
		return 1;

	return 0;
}

int Cours::operator>(const Cours& c)
{
	if(getTiming() > c.getTiming())
		return 1;

	return 0;
}

int Cours::operator==(const Cours& c)
{
	if(getTiming() == c.getTiming())
		return 1;

	return 0;
}

Cours& Cours::operator=(const Cours& c)
{
	Event::operator=(c);
	setProfesseur(c.getProfesseur());
	groupes.truncate();
	setGroupes(c.getGroupes());
	return *this;
}

istream& operator>>(istream& o, Cours& c)
{

}

ostream& operator<<(ostream& o, const Cours& c)
{
	o << "Code : " << c.getCode() << endl;;
	o << "Intitule : " << c.getIntitule() << endl;
	o << "Lieu : " << c.getLieu() << endl;
	o << "Timing : " << endl << c.getTiming();
	o << "Professeur : " << c.getProfesseur() << endl;
	o << "Groupes : " << endl;
	c.getGroupes().Affiche();

	return o;
}